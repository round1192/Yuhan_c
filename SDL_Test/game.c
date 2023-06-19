#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define NOTE_SPEED 1.25f
#define JUDGE_PERFECT 0.1f
#define JUDGE_GOOD 0.2f
#define JUDGE_MISS 0.5f


typedef struct {
    float time;
    float lane;
    int type;
    bool processed;
} NoteData;

NoteData noteData[] = {
    { 0.0f, 0.5f, 0 }, { 0.2f, 1.6f, 0 }, { 0.27f, 1.0f, 0 }, { 0.4f, 2.0f, 0 },
    { 1.01f, 1.5f, 0 }, { 1.05f, 1.7f, 0 }, { 1.26f, 1.2f, 1 }, { 1.7f, 1.8f, 0 },
    { 2.2f, 1.1f, 0 }, { 2.7f, 1.8f, 0 }, { 2.83f, 1.2f, 0 }, { 2.94f, 1.7f, 0 },
    { 3.3f, 2.2f, 1 }, { 3.7f, 1.5f, 0 }, { 4.3f, 2.3f, 0 }, { 4.72f, 2.0f, 0 },
    { 5.06f, 2.5f, 0 }, { 5.54f, 0.9f, 0 }, { 5.72f, 1.4f, 0 }, { 5.81f, 1.7f, 0 },
    { 6.0f, 1.5f, 0 }, { 6.7f, 0.6f, 0 }, { 6.76f, 0.8f, 0 }, { 6.82f, 0.5f, 0 },
    { 7.41f, 1.1f, 0 }, { 7.7f, 1.3f, 0 }, { 7.92f, 1.5f, 0 }, { 8.22f, 1.3f, 0 },
    { 8.43f, 1.2f, 0 }, { 8.56f, 1.35f, 0 }, { 8.81f, 1.5f, 1 }, { 9.61f, 1.1f, 1 },
    { 10.4f, 2.3f, 0 }, { 10.4f, 2.5f, 0 }, { 10.5f, 1.8f, 0 }, { 10.5f, 2.0f, 0 },
    { 10.62f, 1.4f, 0 }, { 10.62f, 1.2f, 0 }, { 10.72f, 1.0f, 0 }, { 10.72f, 0.8f, 0 },
    { 11.2f, 0.5f, 1 }, { 11.1f, 1.5f, 0 }, { 11.45f, 0.5f, 1 }, { 11.35f, 2.0f, 0 },
    { 11.7f, 0.5f, 1 }, { 11.6f, 1.5f, 0 }, { 11.95f, 0.5f, 1 }, { 11.85f, 2.0f, 0 },
    { 12.2f, 0.5f, 1 }, { 12.1f, 1.5f, 0 }, { 12.5f, 1.1f, 0 }, { 12.5f, 1.5f, 0 },
    { 12.65f, 1.7f, 0 }, { 12.65f, 2.1f, 0 }, { 12.8f, 0.5f, 0 }, { 12.9f, 1.5f, 0 },
    { 13.0f, 1.0f, 0 }, { 13.1f, 2.0f, 0 }, { 13.2f, 1.5f, 0 }, { 13.3f, 2.5f, 0 },
    { 13.4f, 1.7f, 0 }, { 13.5f, 2.2f, 0 }, { 13.6f, 1.4f, 0 }, { 13.7f, 2.0f, 0 },
    { 13.8f, 1.2f, 0 }, { 14.1f, 2.5f, 1 }, { 14.0f, 0.5f, 0 }, { 14.35f, 2.5f, 1 },
    { 14.25f, 1.0f, 0 }, { 14.55f, 2.5f, 1 }, { 14.45f, 0.5f, 0 },

    // Additional note data can be added here.
};

const int numNotes = sizeof(noteData) / sizeof(NoteData);
const int noteSize = 30;

// 추가된 변수
bool isNotePressed = false;           // 플레이어의 노트 입력 여부를 저장하는 변수
float notePressTime = 0.0f;           // 노트 입력 시간을 저장하는 변수
float timingWindow = 0.0f;            // 노트 입력 허용 범위 (초 단위)
const float releaseThreshold = 0.1f;  // 키를 뗀 후 노트 입력을 중단하는 임계값 (초 단위)

void drawNote(SDL_Renderer* renderer, float lane, float position, int type) {
    int noteX = (int)((lane - 0.5f) * SCREEN_WIDTH / 3 + SCREEN_WIDTH / 6 - noteSize / 2);
    int noteY = (int)position;

    SDL_Rect noteRect = { noteX, noteY, noteSize, noteSize };

    if (type == 0) {
        // Draw a regular note.
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White
        SDL_Rect noteRect = { noteX - noteSize / 10, noteY, noteSize + noteSize / 1, noteSize };  // Increase the width
        SDL_RenderFillRect(renderer, &noteRect);
    }
    else if (type == 1) {
        // Draw a long note.
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green
        SDL_Rect longNoteRect = { noteX, noteY, noteSize * 2, noteSize * 4 };  // Double the height
        SDL_RenderFillRect(renderer, &longNoteRect);
    }
}

void drawJudgeLine(SDL_Renderer* renderer) {
    int judgeLineY = SCREEN_HEIGHT * 4 / 5;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 0, judgeLineY, SCREEN_WIDTH, judgeLineY);
}

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width = surface->w;
    int height = surface->h;

    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Rhythm Line", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "Unable to create SDL window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Unable to create SDL renderer: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Unable to initialize SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }

    Mix_Music* music = Mix_LoadMUS("C:\\c_language_hive\\c_sdl\\SDL_Test\\Temporal_Shifting.wav");
    if (!music) {
        fprintf(stderr, "Unable to load music: %s\n", Mix_GetError());
        return 1;
    }

    if (TTF_Init() != 0) {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 20);
    if (!font) {
        fprintf(stderr, "Unable to load font: %s\n", TTF_GetError());
        return 1;
    }

    bool quit = false;
    float currentTime = 0.0f;
    float firstNoteTime = noteData[0].time;

    int combo = 0;
    int score = 0;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
                else {
                    // 키를 눌렀을 때
                    if (!isNotePressed) {
                        isNotePressed = true;
                        notePressTime = currentTime;

                        // 노트 입력 검사
                        for (int i = 0; i < numNotes; i++) {
                            float notePosition = (currentTime - noteData[i].time) * NOTE_SPEED * SCREEN_HEIGHT;
                            if (notePosition >= SCREEN_HEIGHT)
                                continue;


                            float judgeLineY = SCREEN_HEIGHT * 4 / 5;
                            if (notePosition >= judgeLineY - noteSize && notePosition <= judgeLineY + noteSize) {
                                // 노트가 판정선에 닿았을 때
                                // 점수와 콤보를 증가시키고 노트를 사라지게 함
                                score += 100;
                                combo++;
                                noteData[i].time = -1.0f; // 노트의 시간을 음수로 설정하여 "사라진" 것으로 표시
                                break;
                            }
                        }
                    }
                }
            }
            else if (event.type == SDL_KEYUP) {
                if (isNotePressed) {
                    isNotePressed = false;
                }
            }
        }

        // 화면 지우기
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // 검은색
        SDL_RenderClear(renderer);
        drawJudgeLine(renderer);

        // 노트 그리기
        for (int i = 0; i < numNotes; i++) {
            if (noteData[i].time < 0.0f)
                continue;

            float notePosition = (currentTime - noteData[i].time) * NOTE_SPEED * SCREEN_HEIGHT;
            if (notePosition >= SCREEN_HEIGHT)
                continue;

            drawNote(renderer, noteData[i].lane, notePosition, noteData[i].type);
        }



        // 콤보와 점수 표시
        char comboText[20];
        snprintf(comboText, sizeof(comboText), "combo: %d", combo);
        drawText(renderer, font, comboText, 10, 10);

        char scoreText[20];
        snprintf(scoreText, sizeof(scoreText), "score: %d", score);
        drawText(renderer, font, scoreText, SCREEN_WIDTH - 150, 10);

        // 음악 재생
        if (currentTime >= firstNoteTime && Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(music, -1);
        }

        // 화면 업데이트
        SDL_RenderPresent(renderer);

        // 시간 업데이트
        currentTime += 0.01f;
        SDL_Delay(10);
    }

    TTF_CloseFont(font);
    TTF_Quit();

    Mix_FreeMusic(music);
    Mix_CloseAudio();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


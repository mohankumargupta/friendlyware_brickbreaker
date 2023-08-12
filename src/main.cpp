#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL_Init failed (%s)", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
    // Error handling code
    std::cout << "ERROR:" << TTF_GetError() << "\n";
    }


    if (Mix_Init(MIX_INIT_MP3) < 0) {
      SDL_Log("Mix_Init failed (%s)", Mix_GetError());
    }
    //
    SDL_AudioSpec spec;
    spec.channels = 1;
    spec.format = SDL_AUDIO_F32;
    spec.freq = 48000;

    if (Mix_OpenAudio(0, &spec) < 0) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init failed (%s)", Mix_GetError());
    }
    
    
    Mix_Music *music =  Mix_LoadMUS("test.mp3");
    Mix_PlayMusic(music, 0);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) < 0) {
        SDL_Log("SDL_CreateWindowAndRenderer failed (%s)", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_SetWindowTitle(window, "SDL issue");

    while (1) {
        int finished = 0;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                finished = 1;
                break;
            }
        }
        if (finished) {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

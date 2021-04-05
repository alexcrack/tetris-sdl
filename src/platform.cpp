#include "platform.h"
#include <iostream>


Platform::Platform()
{

}

Platform::~Platform()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int Platform::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Initialization error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cout << "Fonts initialization error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        std::cout << "Couldn't initialize SDL Mixer: " << SDL_GetError() << std::endl;
        return 1;
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);

    return 0;
}

int Platform::loadFonts()
{
    font = TTF_OpenFont(FONT_PATH, 24);

    if (font == nullptr) {
        std::cout << "Font loading error: " << TTF_GetError() << std::endl;
        return 1;
    }

    return 0;
}

int Platform::createWindow()
{
    window = SDL_CreateWindow("Tetris", 100, 100, 480, 640, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Window creating error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    return 0;
}

int Platform::createRenderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        std::cout << "Renderer initialization error: " << SDL_GetError() << std::endl;
        return 1;
    }

    return 0;
}

int Platform::initSounds()
{
    if (music != nullptr) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = nullptr;
    }

    music = Mix_LoadMUS(MUSIC_PATH);

    return 0;
}

void Platform::delay(int time)
{
    SDL_Delay(time);
}

void Platform::prepare()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Platform::render()
{
    SDL_RenderPresent(renderer);
}

void Platform::doInput(Control &control, Actor *actor)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_KEYDOWN:
                doKeyDown(&event.key, control, actor);
                break;

            case SDL_KEYUP:
                doKeyUp(&event.key, control);
                break;

            default:
                break;
        }
    }
}

void Platform::doKeyDown(SDL_KeyboardEvent *event, Control &control, Actor *actor)
{
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            actor->up();
            control.up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            actor->down();
            control.down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
            actor->left();
            control.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            actor->right();
            control.right = 1;
        }
    }
}

void Platform::doKeyUp(SDL_KeyboardEvent *event, Control &control)
{
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            control.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            control.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
            control.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            control.right = 0;
        }
    }
}

void Platform::drawVoxel(int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect { x, y, VOXEL_SIZE, VOXEL_SIZE };
    SDL_RenderDrawRect(renderer, &rect);

    rect.x += 3;
    rect.y += 3;
    rect.h -= 6;
    rect.w -= 6;
    SDL_RenderFillRect(renderer, &rect);
}

void Platform::drawRect(int x, int y, int w, int h, int lineWeight)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect { x, y, w, h };

    SDL_RenderDrawRect(renderer, &rect);
}

void Platform::drawText(int x, int y, std::string text)
{
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };
    SDL_Color textBackgroundColor = { 0x00, 0x00, 0x00, 0xFF };
    SDL_Surface *textSurface = TTF_RenderText_Shaded(font, text.data(), textColor, textBackgroundColor);
    SDL_Texture *texture = NULL;
    SDL_Rect textRect;

    if (!textSurface) {
        std::cout << "Unable to render text surface!\nSDL2_ttf Error: %s\n" << TTF_GetError() << std::endl;
    } else {
        // Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if(!texture) {
            std::cout << "Unable to create texture from rendered text!\nSDL2 Error: %s\n" << SDL_GetError() << std::endl;
        }

        // Get text dimensions
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;
        textRect.x = x;
        textRect.y = y;

        SDL_FreeSurface(textSurface);

        // Draw text
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
    }
}

void Platform::playMusic()
{
    Mix_PlayMusic(music, -1);
}

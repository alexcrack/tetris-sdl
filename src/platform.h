#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "consts.h"
#include "actor.h"

typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
} Control;

class Platform
{
public:
    Platform();
    ~Platform();

    enum Input {
        NO_EVENT,
        EXIT,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    int init();
    int loadFonts();
    int createWindow();
    int createRenderer();
    int initSounds();
    void delay(int time);
    void prepare();
    void render();
    void doInput(Control &control, Actor *actor);
    void drawText(int x, int y, std::string text);
    void drawRect(int x, int y, int w, int h, int lineWeight);
    void drawVoxel(int x, int y);
    void playMusic();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    Mix_Music *music;

    void doKeyDown(SDL_KeyboardEvent *event, Control &control, Actor *actor);
    void doKeyUp(SDL_KeyboardEvent *event, Control &control);
};


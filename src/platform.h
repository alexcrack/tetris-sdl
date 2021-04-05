#pragma once
#include <string>
#include <unordered_map>
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

    enum Sound {
        SILENCE,
        GAME_OVER,
        CLEAR_ROW,
        BLOCK_STOP,
        BLOCK_MOVE
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
    void playSound(Sound sound);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    Mix_Music *music;
    std::unordered_map<Sound, Mix_Chunk*> sounds;

    void doKeyDown(SDL_KeyboardEvent *event, Control &control, Actor *actor);
    void doKeyUp(SDL_KeyboardEvent *event, Control &control);
};


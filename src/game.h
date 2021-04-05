#pragma once
#include "platform.h"
#include "engine.h"
#include "tetramino.h"
#include <vector>
#include <cstdint>
#include "actor.h"

class Game : public Actor
{
public:
    enum State {
        PAUSED,
        FALLING
    };

    Game(Platform *platform);

    void run();

    void up() override;
    void down() override;
    void left() override;
    void right() override;

protected:
    void prepareScene();
    void presentScene();
    void doInput();

    void moveTetramino();
    void checkField();
    int removeLines();
    void updateTimer();

private:
    int ticks = 0;

    Platform *platform;
    Engine *engine;

    int score = 0;
    int level = 1;

    Matrix field;

    Tetramino *currentFigure;

    Control control { false, false, false, false };
};

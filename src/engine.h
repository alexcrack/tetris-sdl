#pragma once
#include "platform.h"
#include "tetramino.h"

class Engine
{
public:
    Engine(Platform *platform);
    ~Engine();

    void showLevel(int level);
    void showScore(int score);
    void drawBorder();
    void drawTetramino(Tetramino &tetramino);
    void drawField(std::vector<std::vector<uint8_t>> *field);


private:
    Platform *platform;
};

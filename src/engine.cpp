#include "engine.h"
#include <fmt/format.h>

Engine::Engine(Platform *platform)
    : platform(platform)
{

}

Engine::~Engine()
{

}

void Engine::showLevel(int level)
{
    platform->drawText(PADDING, PADDING, fmt::format("LEVEL {:0>3}", level));
}

void Engine::showScore(int score)
{
    platform->drawText(250, PADDING, fmt::format("SCORE {:0>6}", score));
}

void Engine::drawBorder()
{
    platform->drawRect(PADDING, 42, FIELD_WIDTH, FIELD_HEIGHT, 1);
}

void Engine::drawTetramino(Tetramino &tetramino)
{
    auto figure = tetramino.getFigure();

    for (size_t i = 0; i < figure->size(); i++)
        for (size_t j = 0; j < figure->at(i).size(); j++) {
            if (figure->at(i).at(j)
                    && (j + tetramino.getPosX()) >= 0 && (j + tetramino.getPosX()) < FIELD_COLS
                    && (i + tetramino.getPosY()) >= 0 && (i + tetramino.getPosY()) < FIELD_ROWS
            ) {
                platform->drawVoxel(j * VOXEL_SIZE + tetramino.getPosX() * VOXEL_SIZE + 6, i * VOXEL_SIZE + tetramino.getPosY() * VOXEL_SIZE + 44);
            }
        }
}

void Engine::drawField(std::vector<std::vector<uint8_t> > *field)
{
    for (size_t i = 0; i < field->size(); i++)
        for (size_t j = 0; j < field->at(i).size(); j++) {
            if (field->at(i).at(j)) {
                platform->drawVoxel(j * VOXEL_SIZE + PADDING + FIELD_PADDING, i * VOXEL_SIZE + 42 + FIELD_PADDING);
            }
        }
}


#include <fmt/format.h>
#include "game.h"
#include "consts.h"
#include <iostream>

Game::Game(Platform *platform)
    : platform(platform),
      engine(new Engine(platform)),
      field(FIELD_ROWS, std::vector<uint8_t>(FIELD_COLS, 0))
{

}

void Game::run()
{
    currentFigure = new Tetramino(&field, FIELD_COLS / 2, -TETRAMINO_SIZE);

    platform->playMusic();

    while (1) {
        // Do input
        doInput();

        // Prepare scene
        prepareScene();

        // Present scene
        presentScene();

        updateTimer();

        // Delay
        platform->delay(DELAY);
    }
}

void Game::prepareScene()
{   
    platform->prepare();

    moveTetramino();
    checkField();

    engine->showLevel(level);
    engine->showScore(score);
    engine->drawBorder();
    engine->drawField(&field);
    engine->drawTetramino(*currentFigure);
}

void Game::presentScene()
{
    platform->render();
}

void Game::doInput()
{
    platform->doInput(control, this);
}

void Game::up()
{
    if (currentFigure->canRotate()) { currentFigure->rotate(); }
}

void Game::down()
{}

void Game::left()
{
    if (currentFigure->canMoveLeft()) { currentFigure->moveLeft(); }
}

void Game::right()
{
    if (currentFigure->canMoveRight()) { currentFigure->moveRight(); }
}

void Game::moveTetramino()
{
    if (control.down && currentFigure->canMoveDown()) { currentFigure->moveDown(); }

    if (ticks % 32 == 0) {
        currentFigure->moveDown();
    }
}

void Game::checkField()
{
    if (!currentFigure->canMoveDown()) {
        currentFigure->transferToField(&field);
        delete currentFigure;

        auto points = removeLines();
        score += points * 10;

        currentFigure = new Tetramino(&field, FIELD_COLS / 2, -TETRAMINO_SIZE);
    }
}

void Game::updateTimer()
{
    ++ticks;

    if (ticks == 0xFFFF) {
        ticks = 0;
    }
}

int Game::removeLines()
{
    int cols = 0;

    for (auto row = field.begin(); row != field.end(); row++) {
        if (std::all_of(row->begin(), row->end(), [](uint8_t cell){ return cell > 0; })) {
            field.erase(row);
            field.insert(field.begin(), std::vector<uint8_t>(FIELD_COLS, 0));
            cols += 1;
        }
    }

    return cols;
}

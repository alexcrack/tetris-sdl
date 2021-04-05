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

        // Delay
        platform->delay(DELAY);
    }
}

void Game::prepareScene()
{   
    platform->prepare();

    moveTetramino();

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
    std::cout << "Button" << std::endl;
    if (currentFigure->canRotate()) { currentFigure->rotate(); }
}

void Game::down()
{
    if (currentFigure->canMoveDown()) { currentFigure->moveDown(); }
}

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
    ++ticks;

    if (!currentFigure->canMoveDown()) {
        currentFigure->transferToField(&field);
        delete currentFigure;

        auto points = removeLines();
        score += points * 10;

        currentFigure = new Tetramino(&field, FIELD_COLS / 2, -TETRAMINO_SIZE);
    } else {
        if (ticks == 32) {
            ticks = 0;
            currentFigure->moveDown();
        }
    }
}

int Game::getDelay()
{
    return 500 / level;
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

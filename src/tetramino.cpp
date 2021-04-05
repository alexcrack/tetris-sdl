#include "tetramino.h"
#include "util.h"

Tetramino::Tetramino(Matrix* field, int posX, int posY)
    : figure(TETRAMINO_SIZE, std::vector<uint8_t>(TETRAMINO_SIZE, 0)),
      field(field),
      posX(posX), posY(posY)
{
    Util::initRandomizer();
    reset(posX, posY);
}

void Tetramino::reset(int newPosX, int newPosY)
{
    posX = newPosX;
    posY = newPosY;

    auto figureNum = Util::getRandomNumber(0, std::size(tetraminos) - 1);

    // Create array for figure
    for (int i = 0; i < 4; i++) {
        int cell = tetraminos[figureNum][i];

        figure.at(cell / 2).at(cell % 2 ? 2 : 1) = 1;
    }

    for (int i = 0, rotations = Util::getRandomNumber(0, 4); i < rotations; i++) {
        rotateLeft(figure);
    }
}

Matrix* Tetramino::getFigure()
{
    return &figure;
}

void Tetramino::rotateLeft(Matrix &matrix) const
{
    // Consider all squares one by one
    for (int x = 0; x < TETRAMINO_SIZE / 2; x++) {
        // Consider elements in group
        // of 4 in current square
        for (int y = x; y < TETRAMINO_SIZE - x - 1; y++) {
            // Store current cell in
            // temp variable
            int temp = matrix[x][y];

            // Move values from right to top
            matrix[x][y] = matrix[y][TETRAMINO_SIZE - 1 - x];

            // Move values from bottom to right
            matrix[y][TETRAMINO_SIZE - 1 - x] = matrix[TETRAMINO_SIZE - 1 - x][TETRAMINO_SIZE - 1 - y];

            // Move values from left to bottom
            matrix[TETRAMINO_SIZE - 1 - x][TETRAMINO_SIZE - 1 - y] = matrix[TETRAMINO_SIZE - 1 - y][x];

            // Assign temp to left
            matrix[TETRAMINO_SIZE - 1 - y][x] = temp;
        }
    }
}

int Tetramino::getPosX() const
{
    return posX;
}

int Tetramino::getPosY() const
{
    return posY;
}

bool Tetramino::canMoveLeft() const
{
    for (int col = 0; col < TETRAMINO_SIZE; col++)
        for (int row = 0; row < TETRAMINO_SIZE; row++) {
            if (!figure[row][col] || (row + posY) < 0) { continue; }

            if ((posX + col - 1) < 0 || field->at(posY + row).at(posX + col - 1)) { return false; }
        }

    return true;
}

void Tetramino::moveLeft()
{
    posX -= 1;
}

bool Tetramino::canMoveRight() const
{
    for (int col = TETRAMINO_SIZE - 1; col > 0; col--)
        for (int row = 0; row < TETRAMINO_SIZE; row++) {
            if (!figure[row][col] || (row + posY) < 0) { continue; }

            if ((posX + col + 1) > FIELD_COLS - 1 || field->at(posY + row).at(posX + col + 1)) { return false; }
        }

    return true;
}

void Tetramino::moveRight()
{
    posX += 1;
}

bool Tetramino::canMoveDown() const
{
    for (int row = TETRAMINO_SIZE - 1; row > 0; row--)
        for (int col = 0; col < TETRAMINO_SIZE; col++) {
            if (!figure[row][col] || (row + posY) < 0) { continue; }

            if ((posY + row + 1) > FIELD_ROWS - 1 || field->at(posY + row + 1).at(posX + col)) { return false; }
        }

    return true;
}

void Tetramino::moveDown()
{
    posY += 1;
}

bool Tetramino::canRotate() const
{
    auto tempFigure(figure);

    rotateLeft(tempFigure);

    for (int col = 0; col < TETRAMINO_SIZE; col++)
        for (int row = 0; row < TETRAMINO_SIZE; row++) {
            if (!tempFigure[row][col] || (row + posY) < 0) { continue; }

            if ((posX + col) < 0 || (posX + col + 1) > FIELD_COLS - 1
                || (posY + row) > FIELD_ROWS - 1
                || field->at(posY + row).at(posX + col)
            ) { return false; }
        }

    return true;
}

void Tetramino::rotate()
{
    rotateLeft(figure);
}

void Tetramino::transferToField(Matrix *field)
{
    for (int col = 0; col < TETRAMINO_SIZE; col++)
        for (int row = 0; row < TETRAMINO_SIZE; row++) {
            if (!figure[row][col]) { continue; }

            field->at(posY + row).at(posX + col) = figure.at(row).at(col);
        }
}


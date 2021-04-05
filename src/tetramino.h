#pragma once
#include "consts.h"
#include <vector>
#include <cstdint>
#include <array>

/**
 * Figure voxels numbers
 * 0 1
 * 2 3
 * 4 5
 * 6 7
 */
constexpr int tetraminos[7][TETRAMINO_SIZE] = {
    { 1, 3, 5, 7 }, // I
    { 2, 4, 5, 7 }, // S
    { 3, 5, 4, 6 }, // Z
    { 3, 4, 5, 7 }, // T
    { 2, 4, 6, 7 }, // L
    { 3, 5, 7, 6 }, // J
    { 2, 3, 4, 5 } // O
};

class Tetramino
{
public:
    Tetramino(Matrix* field, int posX, int posY);

    void reset(int newPosX, int newPosY);

    void rotateLeft(Matrix &matrix) const;

    int getPosX() const;
    int getPosY() const;

    bool canMoveLeft() const;
    void moveLeft();
    bool canMoveRight() const;
    void moveRight();
    bool canMoveDown() const;
    void moveDown();
    bool canRotate() const;
    void rotate();

    void transferToField(Matrix *field);

    Matrix* getFigure();

private:
    Matrix figure;
    Matrix* field;
    int posX;
    int posY;
};

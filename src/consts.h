#pragma once
#include <vector>
#include <stdint.h>

#define FONT_PATH "res/Orbitron-Bold.ttf"
#define MUSIC_PATH "res/Tetris.mp3"
#define MAX_SND_CHANNELS 8

#define PADDING 4
#define FIELD_COLS 10
#define FIELD_ROWS 20
#define VOXEL_SIZE 28
#define FIELD_PADDING 2
#define FIELD_WIDTH FIELD_COLS * VOXEL_SIZE + FIELD_PADDING * 2
#define FIELD_HEIGHT FIELD_ROWS * VOXEL_SIZE + FIELD_PADDING * 2

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 600

#define TETRAMINO_SIZE 4

#define DELAY 16

typedef std::vector<std::vector<uint8_t>> Matrix;

#include <iostream>

#include "platform.h"
#include "game.h"

using namespace std;

int main()
{
    auto *platform = new Platform();

    if (platform->init() != 0) { exit(1); };
    if (platform->loadFonts() != 0) { exit(1); };
    if (platform->createWindow() != 0) { exit(1); };
    if (platform->createRenderer() != 0) { exit(1); };
    if (platform->initSounds() != 0) { exit(1); }

    auto *game = new Game(platform);

    game->run();

    delete game;
    delete platform;

    return 0;
}

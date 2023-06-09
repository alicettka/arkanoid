#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <cstddef>

namespace console {

    void resize(std::size_t x, std::size_t y);

    void putCursorToStartOfConsole();

    void clearScreen();

    bool keyWasPressed();

    char getKey();

    bool leftKeyHoldDown();
    bool rightKeyHoldDown();
    bool spaceKeyHoldDown();
    bool escKeyHoldDown();
    bool rKeyHoldDown();

    bool isKeyDown(int key_code);

}  // namespace console
#endif
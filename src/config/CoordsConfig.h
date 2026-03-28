#pragma once
#include "ScreenConfig.h"

constexpr float POSITION_Y_PLAYER = 194;
constexpr int SCORE_POSITION_X = SCREEN_WIDTH;
constexpr int SCORE_POSITION_Y = SCREEN_HEIGHT - NUMBER_0_HEIGHT;
constexpr int TIME_POSITION_X = 0;

namespace MAIN_MENU_COORDS
{
    constexpr int TITLE_X = SCREEN_WIDTH/2;
    constexpr int TITLE_Y = 70;

    constexpr int SELECTOR_START_X = 0.2 * SCREEN_WIDTH;
    constexpr int SELECTOR_START_Y = 205;

    constexpr int START_X = SELECTOR_START_X;
    constexpr int START_Y = 153;

    constexpr int SELECTOR_EXIT_X = 0.8 * SCREEN_WIDTH;
    constexpr int SELECTOR_EXIT_Y = SELECTOR_START_Y;

    constexpr float EXIT_GAME_X = SELECTOR_EXIT_X;
    constexpr float EXIT_GAME_Y = START_Y;
};
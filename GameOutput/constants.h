#pragma once

namespace constants {
    constexpr int WINDOW_WIDTH = 640;
    constexpr int WINDOW_HEIGHT = 640;
    constexpr int TILE_WIDTH = WINDOW_WIDTH / 8;
    constexpr int TILE_HEIGHT = WINDOW_HEIGHT / 8;

    const sf::Color black(100, 47, 8);
    const sf::Color white(225, 204, 153);
    const sf::Color selected(70, 70, 0);
}
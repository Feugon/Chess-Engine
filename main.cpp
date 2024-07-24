#include "BoardRepresentation.h"
#include "GameOutput/gameClass.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> board = boardMatrix("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    printBoard(board);

    sf::RenderWindow window(sf::VideoMode(640, 640), "Chess Board");

    chessGame game;

    // The game loop should be based on events for this scenario
    while (window.isOpen()) {
        sf::Event event;
        bool shouldUpdate = false; // Flag to track if the game state needs to be updated

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                game.selectedSetter(event.mouseButton.x, event.mouseButton.y);
                shouldUpdate = true; // Set flag to true when a relevant event occurs
            }
        }

        if (shouldUpdate) {
            // Clear the window
            window.clear();

            // Call the function to draw the chessboard
            game.drawBoard(window);
            game.drawSelected(window);
            game.drawPieces(window, board);

            // Display everything that was drawn
            window.display();

            shouldUpdate = false; // Reset the flag after updating
        }
    }


    return 0;
}

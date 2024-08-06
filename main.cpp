#include "GameOutput/gameClass.h"
#include "Engine/moveSearch.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>




int main() {
    sf::RenderWindow window(sf::VideoMode(640, 640), "Chess Board");
    window.setFramerateLimit(60);

    //starting position: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
    chessGame game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");


    auto start = std::chrono::high_resolution_clock::now();
    std::cout << perft(game, 4) << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken by function: " << duration.count() << " seconds" << std::endl;

    // initial draw
    window.clear();
    game.drawPosition(window);
    game.drawPossibleMoves(window);
    window.display();

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
            game.drawPosition(window);
            game.drawPossibleMoves(window);


            // Display everything that was drawn
            window.display();

            shouldUpdate = false;
        }


        // prevents cpu from bottlenecking
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }


    return 0;
}

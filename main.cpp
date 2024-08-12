#include "GameOutput/gameClass.h"
#include "Engine/moveSearch.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

#include "constants.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT), "Chess Board");
    window.setFramerateLimit(60);

    //starting position: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
    chessGame game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    // initial draw
    window.clear();
    game.drawPosition(window);
    game.drawPossibleMoves(window);
    window.display();

    // event based game loop
    while (window.isOpen()) {
        sf::Event event;
        bool shouldUpdate = false;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                game.selectedSetter(event.mouseButton.x, event.mouseButton.y);
                shouldUpdate = true;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) { // this is for debugging purposes only
                    /*
                    Move bestMove;
                    int bestScore = minimax(game,3,false,bestMove);
                    std::cout << bestMove.from << "->" << bestMove.to << ": " << bestScore << std::endl;
                    game.makeMove(bestMove);
                    shouldUpdate = true;
                    */
                }
            }
        }

        if (shouldUpdate) {
            window.clear();
            game.drawPosition(window);
            game.drawPossibleMoves(window);
            window.display();

            shouldUpdate = false;

            // the engine component

            if(!game.getWhiteToMove()) {
                Move bestMove;
                int bestScore = minimax(game,3,false,bestMove, -1e9, 1e9);
                game.makeMove(bestMove);
                window.clear();
                game.drawPosition(window);
                game.drawPossibleMoves(window);
                window.display();
            }

        }


        // prevents cpu from bottlenecking
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }


    return 0;
}

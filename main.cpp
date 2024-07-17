#include <SFML/Graphics.hpp>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Box Example");

    // Define a rectangle shape
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 150.f));
    rectangle.setPosition(300.f, 200.f); // Position of the top-left corner
    rectangle.setFillColor(sf::Color::Blue); // Fill color of the rectangle
    rectangle.setOutlineThickness(2.f); // Optional: Outline thickness
    rectangle.setOutlineColor(sf::Color::Red); // Optional: Outline color

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window (to remove previous drawings)
        window.clear();

        // Draw the rectangle shape
        window.draw(rectangle);

        // Display the window contents
        window.display();
    }

    return 0;
}

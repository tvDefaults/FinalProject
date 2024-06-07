#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
class Player{

};
class Enemy
{

};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Body Invasion");

    sf::Texture playerTexture, antibodyTexture, backgroundTexture, virusTexture, bacteriaTexture, mAbsTexture, heartTexture;
    if (!playerTexture.loadFromFile("B_Cell.png") ||
        !antibodyTexture.loadFromFile("antiBody.png") || // NEED TO REMODEL THE PIXEL ART
        //!backgroundTexture.loadFromFile("backGround.png") || //Failed to load image "backGround.png". Reason: Unable to open file
        !virusTexture.loadFromFile("virus.png") ||
        !bacteriaTexture.loadFromFile("bacteria.png") ||
        !mAbsTexture.loadFromFile("mAbs.png") ||
        !heartTexture.loadFromFile("heart.png")) {
        return -1;
    }

    Player player(playerTexture, antibodyTexture, heartTexture);
    std::vector<Enemy*> enemies;
    int maxEnemies = 3;  // Max number of enemies allowed on the screen
    int mAbsCount = 0;   // Number of mAbs on screen
    sf::Sprite playerSprite(player);
    playerSprite.setPosition(400, 500);  // Starting position

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerSprite.move(-5.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerSprite.move(5.f, 0.f);
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Draw the player
        window.draw(playerSprite);

        // Display everything on the window
        window.display();
    }

    return 0;
}

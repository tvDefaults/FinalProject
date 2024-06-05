#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

class Antibody {
public:
    sf::Sprite sprite;

    Antibody(const sf::Texture& texture, float x, float y) {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    void update() {
        sprite.move(0, -10);
    }
};

/*class Player {
public:
    sf::Sprite sprite;
    std::vector<Antibody> antibodies;
    sf::Texture antibodyTexture;

    Player(const sf::Texture& texture, const sf::Texture& antibodyTex) {
        sprite.setTexture(texture);
        antibodyTexture = antibodyTex;
        sprite.setPosition(400, 500);
    }

    void move(sf::Vector2f direction) {
        sprite.move(direction);
    }

    void shoot() {
        Antibody newAntibody(antibodyTexture, sprite.getPosition().x + sprite.getGlobalBounds().width / 2, sprite.getPosition().y);
        antibodies.push_back(newAntibody);
    }

    void update() {
        for (auto& antibody : antibodies) {
            antibody.update();
        }
        // Remove off-screen antibodies
        antibodies.erase(std::remove_if(antibodies.begin(), antibodies.end(), [](const Antibody& a) { return a.sprite.getPosition().y < 0; }), antibodies.end());
    }
};
*/


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game V1.1");

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("b_cell.png")) {
        return -1;
    }
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setPosition(400, 500);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerSprite.move(-5.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerSprite.move(5.f, 0.f);
        }

        window.clear(sf::Color::Black);

        window.draw(playerSprite);

        window.display();
    }

    return 0;
}

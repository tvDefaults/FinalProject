#include <SFML/Graphics.hpp>
#include <SFMl/Graphics.hpp>
#include <vector>
#include <cstdlib>
//#include <ctime>

class Antibody {
public:
    sf::Sprite sprite;
    clock_t lastMove;
    int speed;

    Antibody(const sf::Texture& texture, float x, float y, int v) {
        sprite.setTexture(texture);
        sprite.setScale(0.1f,0.1f);
        sprite.setPosition(x, y);
        lastMove = clock();
        speed=v;
    }

    void update() {
        if(lastMove+speed<clock())
        {
            sprite.move(0, -0.1);
        }
        if(sprite.getPosition().y <10)
        {
            sprite.setPosition(sprite.getPosition().x,10);
            sprite.setScale(0.05f,0.05f);
        }
    }
};

class Player {
public:
    sf::Sprite sprite;
    std::vector<Antibody> antibodies;
    sf::Texture antibodyTexture;
    float min_x;
    float max_x;
    clock_t lastShot;

    Player(const sf::Texture& texture, const sf::Texture& antibodyTex,float range_x) {
        sprite.setTexture(texture);
        antibodyTexture = antibodyTex;
        sprite.setScale(0.3f,0.3f);
        sprite.setPosition(200, 600);
        min_x =0;
        lastShot =clock();
        max_x=range_x;
    }
    void move(sf::Vector2f direction)
    {
        sprite.move(direction);

        if (sprite.getPosition().x <min_x){
            sprite.setPosition(0,600);
        }
        if (sprite.getPosition().x>max_x)
        {
            sprite.setPosition(max_x,600);
        }
    }
    void fire(int speed)
    {
        if(lastShot+200<clock()){
        Antibody antibody(antibodyTexture, sprite.getPosition().x + sprite.getGlobalBounds().width / 2, sprite.getPosition().y,speed);
        antibodies.push_back(antibody);
        lastShot= clock();
        }
    }

    void update() {
        for (auto& antibody : antibodies) {
            antibody.update();
        }
        // Remove off-screen antibodies
       // antibodies.erase(std::remove_if(antibodies.begin(), antibodies.end(), [](const Antibody& a) { return a.sprite.getPosition().y < 0; }), antibodies.end());
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Game V1.1");

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("C:/Users/jojo/OneDrive/Documents/FinalProject/new_Game/B_Cell.png")) {
        return -1;
    }
    Player player(playerTexture, playerTexture,600);

    //sf::Sprite playerSprite(playerTexture);
    //playerSprite.setPosition(200, 200);
    //player.setScale(0.3f,0.3f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
           // playerSprite.move(-0.5f, 0.f);
            player.move(sf::Vector2f(-0.5f,0.f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            //playerSprite.move(0.5f, 0.f);
            player.move(sf::Vector2f(0.5f,0.f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.fire(5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player.fire(50);
        }

       window.clear(sf::Color::Black);

       window.draw(player.sprite);
       for(int i=0; i < player.antibodies.size(); i++){
           window.draw(player.antibodies[i].sprite);
       }
       player.update();

       window.display();
    }

    return 0;
}

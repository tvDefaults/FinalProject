#include <SFML/Graphics.hpp>
#include <SFMl/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string.h>

class Pathogen {
public:
    sf::Sprite sprite;
    clock_t lastMove;
    int speed;
    float delta_y;

    Pathogen(const sf::Texture& texture, float x, float y, int v) {
        sprite.setTexture(texture);
        sprite.setScale(0.2f,0.2f);
        sprite.setPosition(x, y);
        lastMove = clock();
        speed=v;
        delta_y = 0.1;
    }

    void update() {
        if(lastMove+speed<clock())
        {
            sprite.move(0, delta_y);
        }
        if(sprite.getPosition().y >800)
        {
            sprite.setPosition(sprite.getPosition().x,800);
            sprite.setScale(0.1f,0.1f);
        }
    }
};

class RBC {
public:
    sf::Sprite sprite;
    float scale =0.15;

    RBC(const sf::Texture& texture, float x, float y) {
        sprite.setTexture(texture);
        sprite.setScale(scale,scale);
        sprite.setPosition(x, y);
    }

    bool checkCollision(Pathogen &p)
    {
        bool result = false;
        sf::FloatRect p_bound = p.sprite.getGlobalBounds();
        sf::FloatRect a_bound = sprite.getGlobalBounds();
        if (a_bound.intersects(p_bound))
        {
            result = true;
        }
        //std::cout << a_bound.left <<std::endl;
        return result;
    }
};

class Antibody {
public:
    sf::Sprite sprite;
    clock_t lastMove;
    int speed;
    float delta_y;
    float scale =0.3;

    Antibody(const sf::Texture& texture, float x, float y, int v) {
        sprite.setTexture(texture);
        sprite.setScale(scale,scale);
        sprite.setPosition(x, y);
        lastMove = clock();
        speed=v;
        delta_y = -0.1;
    }

    bool update() {
        bool result = false;
        if(lastMove+speed<clock())
        {
            sprite.move(0, delta_y);
        }
        if(sprite.getPosition().y <10)
        {
            result =true;
        }
        return result;
    }
    bool checkCollision(Pathogen &p)
    {
        bool result = false;
        sf::FloatRect p_bound = p.sprite.getGlobalBounds();
        sf::FloatRect a_bound = sprite.getGlobalBounds();
        if (a_bound.intersects(p_bound))
        {
            delta_y =0;
            p.delta_y=0;
            result = true;
        }
        //std::cout << a_bound.left <<std::endl;
        return result;
    }
};

class Player {
public:
    sf::Text gameMessage;
    int lives;
    sf::Sprite sprite;
    sf::Sprite gameOver;
    std::vector<Antibody> antibodies;
    std::vector<RBC> redbloodcells;
    sf::Texture antibodyTexture;
    float min_x;
    float max_x;
    clock_t lastShot;
    float scale = 0.3;

    Player(const sf::Texture& texture, const sf::Texture& antibodyTex,const sf::Texture& bloodTex,sf::Texture& message,float range_x) {
        sprite.setTexture(texture);
        gameOver.setTexture(message);
        gameOver.setPosition(300,300);
        gameOver.setScale(0.5,0.5);
        antibodyTexture = antibodyTex;
        sprite.setScale(scale,scale);
        sprite.setPosition(200, 600);
        min_x =0;
        lastShot =clock();
        max_x=range_x;
        lives= 3;
        for (int i=0; i<lives; i++)
        {
            RBC redblood(bloodTex,i*250+50,700);
            redbloodcells.push_back(redblood);
        }
    }
    void move(sf::Vector2f direction)
    {
        if(lives>0)
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
    }
    void fire(int speed)
    {
        if(lastShot+500<clock()&& lives>0){
        Antibody antibody(antibodyTexture, sprite.getPosition().x + sprite.getGlobalBounds().width*scale / 2, sprite.getPosition().y,speed);
        antibodies.push_back(antibody);
        lastShot= clock();
        }
    }

    void update() {
        std::vector<int> list;
        int idx = 0;
        list.clear();
        for (auto& antibody : antibodies) {
            if(antibody.update())
            {
                antibodies.erase(antibodies.begin() + idx);
            }
            idx++;
        }
    }

    bool checkCollision(Pathogen& p)
    {
        bool result = false;
        std::vector<int> list;
        list.clear();
        for(int i=0; i < antibodies.size(); i++)
        {
            if (antibodies[i].checkCollision(p))
            {
                list.push_back(i);
                std::cout << "shot" <<std::endl;
                std::cout << lives <<std::endl;
                result = true;
            }
        }
        for(auto & idx:list )
        {
          antibodies.erase( antibodies.begin() + idx );
        }
        //------------------------------------
        list.clear();
        for(int i=0; i < redbloodcells.size(); i++)
        {
            if (redbloodcells[i].checkCollision(p))
            {
                list.push_back(i);
                result = true;
            }
        }
        for(auto & idx:list )
        {
            redbloodcells.erase( redbloodcells.begin() + idx );
        }
        lives = redbloodcells.size();
        if(lives==0)
        {
            sprite.rotate(0.1);
            sprite.setPosition(300, 300);
        }
        return result;
        //std::cout << antibodies.size() <<std::endl;
    }
};



class Infection {
public:
    std::vector<Pathogen> pathogens;
    sf::Texture pathoTexture;
    float min_x;
    float max_x;
    clock_t lastInfection;

    int infection_x =0;

    Infection(const sf::Texture& texture,float range_x) {

        pathoTexture = texture;
        min_x =0;
        lastInfection =clock();
        max_x=range_x;
    }

    void attack(int speed)
    {
        if(lastInfection+2000<clock()){
            Pathogen pathogen(pathoTexture,infection_x, 10,speed);
            pathogens.push_back(pathogen);
            lastInfection= clock();
            infection_x = infection_x + 90;
            if(infection_x>max_x)
            {
                infection_x = 100;
            }
        }
    }

    void update() {
        for (auto& p : pathogens) {
            p.update();
        }
    }
};

int main() {
    std::vector<int> list;
    char path[]= "C:/Users/jojo/OneDrive/Documents/FinalProject/new_Game/";
    char buffer[1000];

    sf::RenderWindow window(sf::VideoMode(800, 900), "Body Invasion");

    sprintf(buffer,"%s%s",path,"B_Cell.png");
    sf::Texture playerTexture;
    //if (!playerTexture.loadFromFile("C:/Users/jojo/OneDrive/Documents/FinalProject/new_Game/B_Cell.png")) {
    if (!playerTexture.loadFromFile(buffer))
    {
        return -1;
    }
    sprintf(buffer,"%s%s",path,"antiBody.png");
    sf::Texture antibodyTexture;
   // if (!antibodyTexture.loadFromFile("C:/Users/jojo/OneDrive/Documents/FinalProject/new_Game/antiBody.png"))
    if (!antibodyTexture.loadFromFile(buffer))
    {
        return -1;
    }
    sprintf(buffer,"%s%s",path,"bacteria.png");
    sf::Texture bacteriaTexture;
   // if (!bacteriaTexture.loadFromFile("C:/Users/jojo/OneDrive/Documents/FinalProject/new_Game/bacteria.png"))
    if (!bacteriaTexture.loadFromFile(buffer)){
        return -1;
    }
    sprintf(buffer,"%s%s",path,"backGround.jpg");
    sf::Texture redBloodTexture;
    //if (!redBloodTexture.loadFromFile("C:/Users/jojo/OneDrive/Documents/FinalProject/new_Game/backGround.jpg"))
    if (!redBloodTexture.loadFromFile(buffer)){
        return -1;
    }
    sprintf(buffer,"%s%s",path,"game_over.png");
    sf::Texture gameOverTexture;
    //if (!gameOverTexture.loadFromFile("C:/Users/jojo/OneDrive/Documents/FinalProject/new_Game/game_over.png")) {
    if (!gameOverTexture.loadFromFile(buffer)){
        return -1;
    }
    Player player(playerTexture, antibodyTexture,redBloodTexture,gameOverTexture,600);
    Infection infection(bacteriaTexture,500);

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
        list.clear();
        for(int i=0; i < infection.pathogens.size(); i++){

           if(player.checkCollision(infection.pathogens[i])){
               list.push_back(i);
            }
           window.draw(infection.pathogens[i].sprite);
        }
        for(auto& idx :list )
        {
            infection.pathogens.erase( infection.pathogens.begin() + idx );
        }
        infection.attack(100);
        infection.update();

       for(int i=0; i < player.antibodies.size(); i++){
           window.draw(player.antibodies[i].sprite);
       }
       for (auto& RBC:player.redbloodcells)
       {
           window.draw(RBC.sprite);
       }
       player.update();
       window.draw(player.sprite);
       if(player.lives<=0)
       {
       window.draw(player.gameOver);
       }
       window.display();
    }

    return 0;

}

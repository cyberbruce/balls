#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>
#include <iostream>

constexpr int game_width = 2048;
constexpr int game_height = 2048;
 

class Box
{
    sf::Sprite shape;
    sf::Texture texture;
    float velocity = 1.0f;
    bool isDropping = false;
    bool drop_completed = false;

public:
    Box(sf::Vector2f position, sf::Texture & texture)
    {
        texture.setSmooth(true);

        shape = sf::Sprite(texture);
        shape.setOrigin(25.0f, 25.0f);
        shape.setPosition(position);

        float LO = 0.8f;
        float HI = 4.0f;
        velocity = LO + static_cast<float>(rand()) /( static_cast<float>(RAND_MAX/(HI-LO)));
        
        Drop();
    }

    
    void Drop()
    {
        isDropping = true;
    }

    bool DropCompleted() { return drop_completed; }

    void Update(float deltatime)
    {
        if (isDropping)
            handleDrop(deltatime);
    }

    void handleDrop(float deltatime)
    {
        auto pos = shape.getPosition();

        pos.y += 10.0f * velocity;

        velocity += velocity * (981.0f / abs(pos.y-game_height)) * deltatime;

        if (pos.y > game_height)
        {
            drop_completed = true;
            isDropping = false;
        }

        shape.setPosition(pos);
    }

    void Draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};

bool creating = false;

int main()
{

    using namespace std;

    sf::Texture texture;
    if (!texture.loadFromFile("../ball.png"))
    {
        throw "cannot load file";
    }


    sf::RenderWindow window(sf::VideoMode(game_width, game_height), "Playing");
    window.setVerticalSyncEnabled(true);

    std::list<Box *> boxes;

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltatime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
        {
            creating = true;
            auto mousePosition = sf::Mouse::getPosition(window);
            boxes.push_back(new Box(sf::Vector2f(mousePosition.x, mousePosition.y), texture));
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
        {
            creating = false;             
        }
         
        std::list<Box *> boxes_to_delete;

        for (auto &box : boxes)
        {
            box->Update(deltatime);
            if (box->DropCompleted())
            {
                boxes_to_delete.push_back(box);
            }
        }

        for (auto &remove_box : boxes_to_delete)
        {
            boxes.remove(remove_box);
            delete remove_box;
        }

        window.clear();

        for (auto &box : boxes)
        {
            box->Draw(window);
        }

        window.display();
    }
}
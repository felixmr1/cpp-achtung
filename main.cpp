#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

using namespace sf;

struct tail
{
    Vector2f tailPos;
    CircleShape tailShape = CircleShape(10.f);
    int index;
};

struct Player
{
    float speed_x = 5;
    float speed_y = 5;
    CircleShape shape = CircleShape(5.f);
    std::vector<tail> playerTail;
};

void movePlayer(Player *p)
{
    // Move in the direction we're facing
    p->speed_x = 2 * cos(p->shape.getRotation());
    p->speed_y = 2 * -sin(p->shape.getRotation());
    p->shape.move(p->speed_x, p->speed_y);

}

void edgeDetection(Player *p, VideoMode size)
{
    if (p->shape.getPosition().x > size.width) {
        p->shape.setPosition(0, p->shape.getPosition().y);
    }
    else if (p->shape.getPosition().x < 0) {
        p->shape.setPosition(size.width, p->shape.getPosition().y);
    }
    else if (p->shape.getPosition().y > size.height) {
        p->shape.setPosition(p->shape.getPosition().x, 0);
    }
    else if (p->shape.getPosition().y < 0) {
        p->shape.setPosition(p->shape.getPosition().x, size.height);
    }
}

void collisionDetection(Player *p1, Player *p2)
{
    std::cout<< p1->shape.getTextureRect().top <<std::endl;
    std::cout<< "" <<std::endl;
    for (unsigned i = 1; i < p1->playerTail.size(); i++) {
        if (p1->shape.getTextureRect().intersects(
            p1->playerTail.at(i).tailShape.getTextureRect()))
        {
            std::cout<<"hit itself"<<std::endl;
        }
    }
    for (auto &p : p2->playerTail) {
        if (p1->shape.getTextureRect().intersects(p.tailShape.getTextureRect())){
            std::cout<<"hit other"<<std::endl;
        }
    }
}

int main()
{
    VideoMode size(900, 900);
    RenderWindow window(size, "ACHTUNG DIE KURVE");

    Player p1;
    p1.shape.setFillColor(Color::Red);
    p1.shape.setPosition(600,600);
    p1.shape.setRotation(45.f);

    Player p2;
    p2.shape.setFillColor(Color::Green);
    p2.shape.setPosition(200,200);
    p2.shape.setRotation(45.f);

    window.setFramerateLimit(60);
    int i = 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if      (Keyboard::isKeyPressed(Keyboard::A)) {p1.shape.rotate( M_PI/30);}
                    else if (Keyboard::isKeyPressed(Keyboard::S)) {p1.shape.rotate(-M_PI/30);}
                    if      (Keyboard::isKeyPressed(Keyboard::K)) {p2.shape.rotate( M_PI/30);}
                    else if (Keyboard::isKeyPressed(Keyboard::L)) {p2.shape.rotate(-M_PI/30);}
                    break;
                default:
                    break;
            }
        }
        movePlayer(&p1);
        movePlayer(&p2);

        edgeDetection(&p1, size);
        edgeDetection(&p2, size);

        collisionDetection(&p1, &p2);

        i++;
        p1.playerTail.push_back(tail{p1.shape.getPosition(), p1.shape, i});
        p2.playerTail.push_back(tail{p2.shape.getPosition(), p2.shape, i});

        window.clear();
        for (auto &p : p1.playerTail) {
            p.tailShape.setPosition(p.tailPos);
            window.draw(p.tailShape);
        }
        for (auto &p : p2.playerTail) {
            p.tailShape.setPosition(p.tailPos);
            window.draw(p.tailShape);
        }
        window.draw(p1.shape);
        window.draw(p2.shape);
        window.display();
    }
    return 0;
}



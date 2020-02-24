#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>



enum Direction
{
    Droite=0, Gauche, Haut, Bas
};

class point
{
    public:

    point(int,int); // position

    point();
    ~point(){}

    sf::RectangleShape getRect();

    void setColor(sf::Color);

    protected:

    sf::RectangleShape _rect;

    private:

    

};

class joueur : public point
{
    public:

    joueur(Direction,int,int);
    ~joueur(){}

    void actu();

    void setDirection(Direction);

    Direction getDirection() const;


    private:

    Direction _direction;

};
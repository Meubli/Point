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

enum typeBonus 
{
    Score =0, Lent, Flash, Hulk, Armageddon, Normal, Reset
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

    typeBonus bonus() const;

    void setBonus(typeBonus);


    private:

    Direction _direction;

    typeBonus _bonus;

};



class bonus : public point 
{
    public:

    bonus(int,int);
    bonus();
    ~bonus(){}

    typeBonus getType() const;

    void setDrawable(bool);
    bool isDrawable() const;

    void setRandomType();

    void setPosition(int,int);

    private:

    typeBonus _type;

    bool _drawable;

};

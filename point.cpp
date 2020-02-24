#include "point.h"




point::point()
{
    _rect.setSize(sf::Vector2f(20,20));

    
}
point::point(int x, int y)
{
    _rect.setSize(sf::Vector2f(20,20));
    _rect.setPosition(x,y);
    
}
sf::RectangleShape point::getRect() { return _rect; }

void point::setColor(sf::Color c)
{
    _rect.setFillColor(c);
}


joueur::joueur(Direction dir,int x,int y): point(x,y),_direction(dir)
{
    _rect.setFillColor(sf::Color(100,250,50));
}

void joueur::setDirection(Direction d)
{
    if( d != _direction)
        _direction = d;
}

Direction joueur::getDirection() const
{
    return _direction;
}

void joueur::actu()
{
    if( _direction == Droite)
    {
        _rect.move(20,0);
        
        
    }
    else if( _direction == Haut)
    {
        _rect.move(0,-20);
        
        
    }
    else if( _direction == Bas)
    {
        _rect.move(0,20);
        
        
    }
    else if( _direction == Gauche)
    {
        _rect.move(-20,0);
        
        
    }

    //std::cout<<_rect.getPosition().x<< "  "<<_rect.getPosition().y<<std::endl;  
}
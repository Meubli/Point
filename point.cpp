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
    _rect.setFillColor(sf::Color(254,254,254));
    _bonus = Normal;
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

void joueur::setBonus(typeBonus t)
{
    _bonus = t;
}

typeBonus joueur::bonus() const{
    return _bonus;
}

bonus::bonus()
{
    this->setColor(sf::Color(0,0,250));
    _drawable = false;
}

bonus::bonus(int x, int y): point(x,y)
{
    

    this->setColor(sf::Color(0,0,250));

    _drawable = false;
}

void bonus::setRandomType()
{
    int t=std::rand()%100;   // on assigne aléatoirement un type de bonus

    if(t<10)
        _type = Armageddon; // 10%
    else if( 10<=t && t<30)
        _type=Hulk;         // 20%
    else if( 30<=t && t<60)
        _type=Flash;        // 30%
    
    else if( 60<=t && t<80)
        _type=Score;        // 20%
    else if( 80<=t && t<99)
        _type=Lent;
    else if( t==99)
        _type=Reset;
}



typeBonus bonus::getType() const{return _type;}

void bonus::setPosition(int x,int y)
{
    _rect.setPosition(x,y);
}

bool bonus::isDrawable() const {return _drawable;}

void bonus::setDrawable(bool d) { _drawable = d;}
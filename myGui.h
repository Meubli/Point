#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>



class Menu
{
    public:

    Menu(float x,float y);
    ~Menu(){}

    void draw(sf::RenderWindow &window);

    void moveUp(sf::RenderWindow &window);
    void moveDown(sf::RenderWindow &window);

    int getItemSelected() const;



    private:

    sf::Font _font;
    int _selectedItemIndex;

    std::vector <sf::Text> _menuText;

    sf::Time _speedHover;
};
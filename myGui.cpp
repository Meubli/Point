#include "myGui.h"



Menu::Menu(float largeur,float hauteur)
{
    if(!_font.loadFromFile("Tusj.ttf"))
    {
        std::cout<<"Erreur du chargeur de la police"<<std::endl;   
    }

    sf::Text text;

    text.setFont(_font);

    text.setFillColor(sf::Color::Red);

    text.setString("JOUER");

    text.setPosition(sf::Vector2f( largeur*9/20,hauteur/3));

    text.setCharacterSize(40);

    text.setStyle(sf::Text::Bold);

    _menuText.push_back(text);

    text.setString("QUITTER");

    text.setFillColor(sf::Color::White);

    text.setPosition(sf::Vector2f( largeur*9/20,hauteur/3*2));

    text.setCharacterSize(30);

    _menuText.push_back(text);

    _selectedItemIndex = 0;

    _speedHover = sf::milliseconds(200);


}

void Menu::draw(sf::RenderWindow &window)
{
    for(int i =0;i<_menuText.size();i++)
    {
        window.draw(_menuText[i]);
    }
}

void Menu::moveDown(sf::RenderWindow &window)
{
    for(int i =0; i<_menuText.size()-1;i++)
    {
        if(i == _selectedItemIndex )
        {
            _menuText[i].setCharacterSize(30);
            _menuText[i].setFillColor(sf::Color::White);

            
            _menuText[i+1].setFillColor(sf::Color::Red);

            

            sf::Clock tickHover;

            while(tickHover.getElapsedTime().asMilliseconds() <= _speedHover.asMilliseconds())
            {
                
                for(int j=1;j<=10;j++)
                {
                    if((float)tickHover.getElapsedTime().asMilliseconds()<(float)j/10*_speedHover.asMilliseconds())
                    {
                        _menuText[i+1].setCharacterSize(30+j);

                        window.clear();
                        window.draw(_menuText[i+1]);
                        this->draw(window);
                        window.display();
                        

                    }
                }
            }



            i++;
            _selectedItemIndex++;
        }
    }

}

void Menu::moveUp(sf::RenderWindow &window)
{
    for(int i =1; i<_menuText.size();i++)
    {
        if(i == _selectedItemIndex )
        {
            _menuText[i].setCharacterSize(30);
            _menuText[i].setFillColor(sf::Color::White);

            
            _menuText[i-1].setFillColor(sf::Color::Red);

            sf::Clock tickHover;

            while(tickHover.getElapsedTime().asMilliseconds() <= _speedHover.asMilliseconds())
            {
                
                for(int j=1;j<=10;j++)
                {
                    if((float)tickHover.getElapsedTime().asMilliseconds()<(float)j/10*_speedHover.asMilliseconds())
                    {
                        _menuText[i-1].setCharacterSize(30+j);

                        window.clear();
                        window.draw(_menuText[i-1]);
                        this->draw(window);
                        window.display();
                        

                    }
                }
            }


            i++;
            _selectedItemIndex--;
        }
    }

}

int Menu::getItemSelected() const
{

    return _selectedItemIndex;
}

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>


class Menu
{
    public:

    Menu(sf::RenderWindow &window);
    ~Menu(){}

    void draw();

    void moveUp();
    void moveDown();

    int getItemSelected() const;

    void hover(int Mx, int);
    bool click(int Mx, int);
    void setHover(int);

    void addText(sf::Text);


    private:

    sf::Font _font;
    int _selectedItemIndex;

    sf::RenderWindow &_window;

    std::vector <sf::Text> _menuText;

    sf::Time _speedHover;
};


class Bouton
{
    public:

        Bouton(int x, int y, std::string text, int size);
        void draw(sf::RenderWindow &window);
        sf::Text getSFText();


    private:

        int _x;
        int _y;
        std::string _string;
        int _size;

        sf::Text* _text;

};

void afficherGO(sf::RenderWindow &window, sf::Font t, sf::Vector2i ecran);

void afficherScores(sf::RenderWindow &window, int, int);

void afficherMenu(sf::RenderWindow &window,int,int);

void enregistrer(std::string, int score, int occupation, int nBonus);

char chiffrer(char);

char dechiffrer(char);

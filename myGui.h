#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <assert.h>


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

std::string encryptDecrypt(std::string toEncrypt); 

void XORscore();

void getData(std::vector<std::string> *, std::vector<int> *,  std::vector<int> *, std::vector<int> * tBonus);

void epurer(std::vector<std::string> *, std::vector<int> *,  std::vector<int> *, std::vector<int> * tBonus);

void trierNom(std::vector<std::string> *, std::vector<int> *,  std::vector<int> *, std::vector<int> * tBonus, int ordre=1);

void trierScore(std::vector<std::string> *, std::vector<int> *,  std::vector<int> *, std::vector<int> * tBonus, int ordre=1);
void trierTaux(std::vector<std::string> *, std::vector<int> *,  std::vector<int> *, std::vector<int> * tBonus, int ordre=1);
void trierBonus(std::vector<std::string> *, std::vector<int> *,  std::vector<int> *, std::vector<int> * tBonus, int ordre=1);

bool stringLessThan(std::string a, std::string b);

void permuter2lignes(std::vector<std::string> *, std::vector<int> *,  std::vector<int> *, std::vector<int> * tBonus, int a, int b);

void actualiserTableau(std::vector<std::string> *, std::vector<int> *,  std::vector<int> *, std::vector<int> * tBonus, std::vector<std::vector<sf::Text>>*);


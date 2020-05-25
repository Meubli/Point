#include "myGui.h"



Menu::Menu(sf::RenderWindow &window): _window(window)
{

    _selectedItemIndex = 0;

    _speedHover = sf::milliseconds(150);



}

void Menu::draw()
{
    for(int i =0;i<_menuText.size();i++)
    {
        _window.draw(_menuText[i]);
    }
}

void Menu::moveDown()
{
    if(_selectedItemIndex<_menuText.size()-1)
        setHover(_selectedItemIndex+1);

}

void Menu::moveUp()
{
    if(_selectedItemIndex>0)
    {
        setHover(_selectedItemIndex-1);
    }

}

int Menu::getItemSelected() const
{

    return _selectedItemIndex;
}
void Menu::setHover(int n)
{

    if(_selectedItemIndex>=0)
    {
        _menuText[_selectedItemIndex].setCharacterSize(30);
        _menuText[_selectedItemIndex].setFillColor(sf::Color::White);
    }

    _menuText[n].setFillColor(sf::Color::Red);

    sf::Clock tickHover;

    while(tickHover.getElapsedTime().asMilliseconds() <= _speedHover.asMilliseconds())
    {

        float transition=90;

        for(int j=0;j<=transition;j++)
        {
            if((float)tickHover.getElapsedTime().asMilliseconds()<(float)j/transition*_speedHover.asMilliseconds())
            {
                _menuText[n].setCharacterSize(30+j/transition*10);




                _window.clear();
                _window.draw(_menuText[n]);
                this->draw();
                _window.display();


            }
        }
    }
    _selectedItemIndex=n;
   
}
void Menu::hover(int x, int y)
{
    for(int i=0;i<_menuText.size();i++)
    {
        sf::Text text = _menuText[i];
        sf::FloatRect rect = text.getGlobalBounds();
        if ( rect.contains(x,y) && i!=_selectedItemIndex)
        {
            setHover(i);
            return;
        }

        
    }

}
bool Menu::click(int x, int y)
{
    for(int i=0;i<_menuText.size();i++)
    {
        sf::Text text = _menuText[i];
        sf::FloatRect rect = text.getGlobalBounds();
        if ( rect.contains(x,y) )
        {
            return true;
        }
    }
    return false;
}

void Menu::addText(sf::Text t)
{
    _menuText.push_back(t);
}

Bouton::Bouton(int x, int y, std::string text, int size)
{
    _x=x;
    _y=y;
    _string=text;
    _size=size;
    
    sf::Font Tusj;
    Tusj.loadFromFile("Tusj.ttf");

    sf::Text *t;

    t = new sf::Text;


    t->setFont(Tusj);

    t->setPosition(sf::Vector2f(x,y));

    t->setString(sf::String(text));

    t->setCharacterSize(size);

    t->setFillColor(sf::Color::White);


    _text = new sf::Text;

    _text=t;

    delete t;
}

void Bouton::draw(sf::RenderWindow &window)
{
    window.draw(*_text);
}

sf::Text Bouton::getSFText()
{
    return *_text;
}

void afficherGO(sf::RenderWindow &window, sf::Font f,sf::Vector2i ecran)
{
    sf::Text GO;
    GO.setFont(f);
    GO.setString("-----   GAME OVER   -----");
    GO.setPosition(ecran.x/100*40,ecran.y/100*98);
    GO.setCharacterSize(35);

    window.draw(GO);

}

void afficherMenu(sf::RenderWindow &window, int largeur, int hauteur)
{
    Menu menu(window);

    sf::Font font;
    font.loadFromFile("Tusj.ttf");

    
    sf::Text text;

    text.setFont(font);

    text.setFillColor(sf::Color::Red);

    text.setString("JOUER");

    text.setPosition(sf::Vector2f( largeur*9/20,hauteur/4));

    text.setCharacterSize(40);

    text.setStyle(sf::Text::Bold);

    menu.addText(text);
    
    text.setString("SCORES");

    text.setPosition(sf::Vector2f( largeur*9/20, hauteur/4*2));

    text.setFillColor(sf::Color::White);

    text.setCharacterSize(30);

    menu.addText(text);


    text.setString("QUITTER");

    text.setFillColor(sf::Color::White);

    text.setPosition(sf::Vector2f( largeur*9/20,hauteur/4*3));

    text.setCharacterSize(30);

    menu.addText(text);

    bool menuOuvert=true;



    while( menuOuvert)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) 
                window.close() ;
            
            if(event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                    case sf::Keyboard::S:
                        menu.moveDown();
                        break;
                    case sf::Keyboard::Down:
                        menu.moveDown();
                        break;
                    case sf::Keyboard::Up:
                        menu.moveUp();
                        break;
                    case sf::Keyboard::Z:
                        menu.moveUp();
                        break;
                    case sf::Keyboard::Enter:
                        if(menu.getItemSelected()==0)
                            menuOuvert=false;
                        else if(menu.getItemSelected()==1)
                        {
                            afficherScores(window,largeur, hauteur);
                        }
                        else if(menu.getItemSelected()==2)
                            window.close();
                        break;
                    default:
                        break;
                }
            if(event.type == sf::Event::MouseMoved)
                menu.hover(event.mouseMove.x,event.mouseMove.y);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(menu.click(event.mouseButton.x,event.mouseButton.y))
                    {
                        
                        if(menu.getItemSelected()==0)
                            menuOuvert=false;
                        else if(menu.getItemSelected()==1)
                        {
                            afficherScores(window,largeur, hauteur);
                        }
                        else if(menu.getItemSelected()==2)
                            window.close();
                    }
                }
            }
        }
        menu.draw();

        window.display();
        window.clear();
    }
}

void afficherScores(sf::RenderWindow &window, int largeur, int hauteur)
{

    // on crée les 4 boutons titres
    window.clear();
    window.display();
    
    Menu menu(window);


    sf::Font font;
    font.loadFromFile("Tusj.ttf");

    sf::Text text;

    text.setFont(font);

    text.setString("Nom");
    text.setFillColor(sf::Color::Red);
    text.setPosition(sf::Vector2f(largeur/6, hauteur/15));
    text.setCharacterSize(40);
    
    menu.addText(text);


    text.setString("Score");
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(largeur*2/6, hauteur/15));
    text.setCharacterSize(30);

    menu.addText(text);

    text.setString("Taux");
    text.setPosition(sf::Vector2f(largeur*3/6, hauteur/15));

    menu.addText(text);

    text.setString("Bonus");
    text.setPosition(sf::Vector2f(largeur*4/6, hauteur/15));

    menu.addText(text);

    text.setString("Retour");
    text.setPosition(sf::Vector2f(largeur*5/6, hauteur/15));

    menu.addText(text);

    bool ouvert=true;

    while(ouvert){

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) 
                window.close() ;
            
            if(event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                    case sf::Keyboard::Right:
                        menu.moveDown();
                        break;
                    case sf::Keyboard::Left:
                        menu.moveUp();
                        break;
                    case sf::Keyboard::Enter:
                        if(menu.getItemSelected()==4)
                            ouvert=false;
                    default:
                        break;
                }
            if(event.type == sf::Event::MouseMoved)
                menu.hover(event.mouseMove.x,event.mouseMove.y);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(menu.click(event.mouseButton.x,event.mouseButton.y))
                    {
                        
                        if(menu.getItemSelected()==4)
                            ouvert=false;
                    }
                }
            }
        }

        menu.draw();

        window.display();
        window.clear();
    }

}

void enregistrer(std::string nom, int score, int occupation, int nBonus)
{

    std::ofstream monFlux("score.txt", std::ios::app);

    if(monFlux)
    {
        std::string save;
        save=nom+" "+std::to_string(score)+" "+std::to_string(occupation);
        save+=" "+std::to_string(nBonus)+"\n";


        for(int i=0; i<save.size();i++)
        {
            save[i]=chiffrer(save[i]);
        }


        monFlux<<save;

        
    }
    else
    {
        std::cout<<"Probleme avec le fichier score.txt"<<std::endl; 
    }
}

char chiffrer(char a)
{
   if(a<26)
   {
        a+=102;
   }
   else
   {
       a-=26;
   }
   return a;
}

char dechiffrer(char a)
{
    if(a>101)
    {
        a-=102;
    }
    else
    {
        a+=26;
    }
    return a;
}

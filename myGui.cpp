#include "myGui.h"

using namespace std;


Menu::Menu(sf::RenderWindow &window): _window(window)
{

    _selectedItemIndex = 0;

    _speedHover = sf::milliseconds(150);



}

void Menu::draw()
{
    for(int i =0;i<(int)_menuText.size();i++)
    {
        _window.draw(_menuText[i]);
    }
}

void Menu::moveDown()
{
    if(_selectedItemIndex<(int)_menuText.size()-1)
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
        _menuText[_selectedItemIndex].setCharacterSize(50);
        _menuText[_selectedItemIndex].setFillColor(sf::Color::White);
    }

    _menuText[n].setFillColor(sf::Color::Red);

    sf::Clock tickHover;

    while(tickHover.getElapsedTime().asMilliseconds() <= _speedHover.asMilliseconds())
    {

        float transition=90;

        for(int j=0;j<=(int)transition;j++)
        {
            if((float)tickHover.getElapsedTime().asMilliseconds()<(float)j/transition*_speedHover.asMilliseconds())
            {
                _menuText[n].setCharacterSize(50+j/transition*10);




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
    for(int i=0;i<(int)_menuText.size();i++)
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
    for(int i=0;i<(int)_menuText.size();i++)
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

    text.setCharacterSize(60);

    text.setStyle(sf::Text::Bold);

    menu.addText(text);
    
    text.setString("SCORES");

    text.setPosition(sf::Vector2f( largeur*9/20, hauteur/4*2));

    text.setFillColor(sf::Color::White);

    text.setCharacterSize(50);

    menu.addText(text);


    text.setString("QUITTER");

    text.setFillColor(sf::Color::White);

    text.setPosition(sf::Vector2f( largeur*9/20,hauteur/4*3));

    text.setCharacterSize(50);

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
    text.setCharacterSize(60);
    
    menu.addText(text);


    text.setString("Score");
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(largeur*2/6, hauteur/15));
    text.setCharacterSize(50);

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

    vector<string> tNom;
    vector<int> tScore;
    vector<int> tBonus;
    vector<int> tTaux;

    getData(&tNom, &tScore, &tTaux, &tBonus);


    epurer(&tNom, &tScore, &tTaux, &tBonus);


    trierNom(&tNom, &tScore, &tTaux, &tBonus);
    

    
    vector<vector<sf::Text>> tabText;

    sf::Vector2f origineTab(largeur/6, hauteur/6);

    for(int i=0;i<(int)tNom.size() && i<28;i++)
    {

        vector<sf::Text> ligneText;

        sf::Text nom;
        nom.setFont(font);
        nom.setFillColor(sf::Color::White);
        nom.setCharacterSize(25);
        nom.setPosition(sf::Vector2f(origineTab.x, origineTab.y + i*(hauteur-origineTab.y)/30));
        nom.setString(tNom[i]);

        ligneText.push_back(nom);

        sf::Text score;
        score.setFont(font);
        score.setFillColor(sf::Color::White);
        score.setCharacterSize(25);
        score.setPosition(sf::Vector2f(largeur*2/6, origineTab.y + i*(hauteur-origineTab.y)/30));
        score.setString(to_string(tScore[i]));


        ligneText.push_back(score);



        sf::Text taux;
        taux.setFont(font);
        taux.setFillColor(sf::Color::White);
        taux.setCharacterSize(25);
        taux.setPosition(sf::Vector2f(largeur*3/6, origineTab.y + i*(hauteur-origineTab.y)/30));
        taux.setString(to_string(tTaux[i])+" %");


        ligneText.push_back(taux);


        sf::Text bonus;
        bonus.setFont(font);
        bonus.setFillColor(sf::Color::White);
        bonus.setCharacterSize(25);
        bonus.setPosition(sf::Vector2f(largeur*4/6, origineTab.y + i*(hauteur-origineTab.y)/30));
        bonus.setString(to_string(tBonus[i]));


        ligneText.push_back(bonus);
        tabText.push_back(ligneText);

    }

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
                        break;
                    case sf::Keyboard::Escape:
                        ouvert=false;
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
                        if(menu.getItemSelected()==4)
                            ouvert=false;
                    }
                }
            }
        }

        if(menu.getItemSelected()==0)
        {

            trierNom(&tNom, &tScore, &tTaux, &tBonus);
        }
        else if( menu.getItemSelected()==1)
        {
            trierScore(&tNom, &tScore, &tTaux, &tBonus);

        }
        else if(menu.getItemSelected()==2)
        {
            
            trierTaux(&tNom, &tScore, &tTaux, &tBonus);
        }
        else if(menu.getItemSelected()==3)
        {

            trierBonus(&tNom, &tScore, &tTaux, &tBonus);
        }

        actualiserTableau(&tNom, &tScore, &tTaux, &tBonus, &tabText);

        menu.draw();

        for(int i=0;i<(int)tabText.size();i++)
        {
            for(int j=0;j<(int)tabText[i].size();j++)
            {

                window.draw(tabText[i][j]);
            }
        }

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

        for(int i=0;i<(int)nom.size();i++)
        {
            if(nom[i]==32)
            {
                nom[i]=95;
            }
        }

        save=nom+" "+std::to_string(score)+" "+std::to_string(occupation);
        save+=" "+std::to_string(nBonus)+"\n";


        for(int i=0; i<(int)save.size();i++)
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

void actualiserTableau(std::vector<std::string> * tNom, std::vector<int> * tScore,  std::vector<int> * tTaux, std::vector<int> * tBonus, vector<vector<sf::Text>> * tabText)
{

    for(int i=0; i<(int)tabText->size();i++)
    {
        (*tabText)[i][0].setString((*tNom)[i]);
        (*tabText)[i][1].setString(to_string((*tScore)[i]));
        (*tabText)[i][2].setString(to_string((*tTaux)[i])+" %");
        (*tabText)[i][3].setString(to_string((*tBonus)[i]));
    }
}

void getData(std::vector<std::string> * tNom, std::vector<int> * tScore,  std::vector<int> * tTaux, std::vector<int> * tBonus)
{
    ifstream fichier("score.txt");

    string ligne;
    char a;

    if(fichier)
    {
        while(fichier.get(a))
        {
            ligne.push_back(a);
        }
    }
    else
        cout<<"Probleme avec le fichier score.txt"<<endl;

    
    for(int i=0;i<(int)ligne.size();i++)
    {
        ligne[i]=dechiffrer(ligne[i]);
    }

    string nom;

    string score;
    string taux, bonus;
    int colonne=0;


    for( int i=0;i<(int)ligne.size();i++)
    {

        if(ligne[i]=='\n')
        {
            colonne=0;

            tNom->push_back(nom);
            tScore->push_back(std::atoi(score.c_str()));
            tTaux->push_back(std::atoi(taux.c_str()));
            tBonus->push_back(std::atoi(bonus.c_str()));

            nom.clear();
            score.clear();
            taux.clear();
            bonus.clear();
        }
        else if(ligne[i]==32)
            colonne++;
        else if(colonne == 0)
        {
            if(ligne[i]>96)
                ligne[i]-=32;
            else if( ligne[i]==95)
                ligne[i]=32;

            nom.push_back(ligne[i]);
        }

        else if( colonne == 1)
        {
            score.push_back(ligne[i]);
        }
        else if( colonne == 2)
        {
            taux.push_back(ligne[i]);
        }
        else if( colonne == 3)
        {
            bonus.push_back(ligne[i]);
        }
    }



}


bool stringLessThan(std::string a, std::string b)
{
    int s=a.size();

    if(a.size()>b.size())
    {
        s=b.size();
    }

    for(int i=0;i<(int)s;i++)
    {
        if(a[i]<b[i])
        {
            return true;
        }
        else if(a[i]>b[i])
        {
            return false;
        }
    }

    if(a.size()<b.size())
        return true;

    return false;
}


void permuter2lignes(std::vector<std::string> * tNom, std::vector<int> * tScore,  std::vector<int> * tTaux, std::vector<int> * tBonus,int indice, int indice2)
{

    string sTemp=(*tNom)[indice];
    (*tNom)[indice]=(*tNom)[indice2];
    (*tNom)[indice2]=sTemp;

    int iTemp= (*tScore)[indice];
    (*tScore)[indice]=(*tScore)[indice2];
    (*tScore)[indice2]=iTemp;

    iTemp= (*tTaux)[indice];
    (*tTaux)[indice]=(*tTaux)[indice2];
    (*tTaux)[indice2]=iTemp;


    iTemp= (*tBonus)[indice];
    (*tBonus)[indice]=(*tBonus)[indice2];
    (*tBonus)[indice2]=iTemp;

}


void trierBonus(std::vector<std::string> * tNom, std::vector<int> * tScore,  std::vector<int> * tTaux, std::vector<int> * tBonus,int ordre)
{
    for(int i=0;i<(int)tBonus->size()-1;i++)
    {
        for(int j=0;j<(int)tBonus->size()-1;j++)
        {
            if( ordre>0 && (*tBonus)[j]<(*tBonus)[j+1])
            {
                permuter2lignes(tNom, tScore, tTaux, tBonus, j, j+1);
            }
            else if( ordre<0 && (*tBonus)[j]>(*tBonus)[j+1])
            {
                permuter2lignes(tNom, tScore, tTaux, tBonus, j, j+1);
            }
        }
    }
}
void trierTaux(std::vector<std::string> * tNom, std::vector<int> * tScore,  std::vector<int> * tTaux, std::vector<int> * tBonus,int ordre)
{
    for(int i=0;i<(int)tTaux->size()-1;i++)
    {
        for(int j=0;j<(int)tTaux->size()-1;j++)
        {
            if( ordre>0 && (*tTaux)[j]<(*tTaux)[j+1])
            {
                permuter2lignes(tNom, tScore, tTaux, tBonus, j, j+1);
            }
            else if( ordre<0 && (*tTaux)[j]>(*tTaux)[j+1])
            {
                permuter2lignes(tNom, tScore, tTaux, tBonus, j, j+1);
            }
        }
    }
}

void trierScore(std::vector<std::string> * tNom, std::vector<int> * tScore,  std::vector<int> * tTaux, std::vector<int> * tBonus,int ordre)
{
    for(int i=0;i<(int)tScore->size()-1;i++)
    {
        for(int j=0;j<(int)tScore->size()-1;j++)
        {
            if( ordre>0 && (*tScore)[j]<(*tScore)[j+1])
            {
                permuter2lignes(tNom, tScore, tTaux, tBonus, j, j+1);
            }
            else if( ordre<0 && (*tScore)[j]>(*tScore)[j+1])
            {
                permuter2lignes(tNom, tScore, tTaux, tBonus, j, j+1);
            }
        }
    }
}

void trierNom(std::vector<std::string> * tNom, std::vector<int> * tScore,  std::vector<int> * tTaux, std::vector<int> * tBonus,int ordre)
{

    for(int i=0;i<(int)tNom->size()-1;i++)
    {
        for(int j=0;j<(int)tNom->size()-1  ;j++)
        {
            if(ordre >0 &&  !stringLessThan((*tNom)[j], (*tNom)[j+1]))
            {
                permuter2lignes(tNom, tScore, tTaux, tBonus, j, j+1);
            }
            else if( ordre<0 && stringLessThan((*tNom)[j], (*tNom)[j+1]))
            {
                permuter2lignes(tNom, tScore, tTaux, tBonus, j, j+1);
            }

        }
    }

}

void epurer(std::vector<std::string> * tNom, std::vector<int> * tScore,  std::vector<int> * tTaux, std::vector<int> * tBonus)
{

    for( int j=0;j<(int)tNom->size();j++)
    {
        for(int i=0;i<(int)tNom->size();i++)
        {
            if( tNom->at(i)==tNom->at(j) && tScore->at(i)<tScore->at(j))
            {
                tNom->erase(tNom->begin()+i);
                tScore->erase(tScore->begin()+i);
                tTaux->erase(tTaux->begin()+i);
                tBonus->erase(tBonus->begin()+i);

                i--;
                j--;
            }
        }

    }

}

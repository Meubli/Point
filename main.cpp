#include "point.h"
#include "myGui.h"

int wLargeur=40;
int wHauteur=40;



#define VITESSESCORE 500
#define VITESSEJOUEUR 300
sf::Vector2i ecran = sf::Vector2i(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height);

void ajoutBordure(std::vector<point> *tab,int x,int y)
{
    for(int i=-1;i<=wLargeur;i++)
    {
        for(int j=-1;j<=wHauteur;j++)
        {
            if( i==-1 || i==wLargeur || j==wHauteur || j==-1 )
            {
                point p(x+i*20, y+j*20);
                p.setColor(sf::Color(250,50,50));
                tab->push_back(p);
            }
        }
    }
}


int main(int argc, const char** argv) {

    sf::Time vitessePoints= sf::milliseconds(1000);  //allure de pop des points

    bool gameOver=false;

    sf::Font Tusj;
    Tusj.loadFromFile("Tusj.ttf");

    sf::Font Roboto;
    Roboto.loadFromFile("Avdira_J.otf");


    sf::String playerInput;

//                                     Le text Score
    sf::Text tScore;

    tScore.setFont(Tusj);

    tScore.setFillColor(sf::Color::White);

    tScore.setString(std::to_string(0));

    tScore.setPosition(sf::Vector2f(ecran.x/2-35, 50));

    tScore.setCharacterSize(30);


    //                                  Le texte pour "Votre nom"
    
    sf::Text nameLabel;
    nameLabel.setFont(Tusj);
    nameLabel.setCharacterSize(30);
    nameLabel.setPosition(ecran.x/100*80, ecran.y/100*30);
    nameLabel.setString("Entrez votre nom : ");

//                                      Le text pour le nom du joeur au Game Over
    sf::Text playerText;

    playerText.setFont(Tusj);

    playerText.setCharacterSize(30);

    playerText.setPosition(ecran.x/100*80, ecran.y/100*45);





    //                                   L'occupation des briques rouges

    sf::Text occupationText;
    occupationText.setFont(Tusj);
    occupationText.setCharacterSize(60);
    occupationText.setPosition(ecran.x/100*15, ecran.y/100*50);
    occupationText.setString("0");




//                                       Le text Bonus

    sf::Text tBonus;
    tBonus.setFont(Roboto);
    tBonus.setFillColor(sf::Color::White);
    tBonus.setString("Aucun Bonus Pour Le Moment");
    tBonus.setPosition(sf::Vector2f(ecran.x/4*3, ecran.y/4));
    tBonus.setCharacterSize(30);


    sf::Time vitesseScore = sf::milliseconds(VITESSESCORE);
    sf::Time speed = sf::milliseconds(VITESSEJOUEUR);

    sf::RenderWindow window;

    window.create(sf::VideoMode(),"JEUX DU POINT", sf::Style::Fullscreen);
    window.setFramerateLimit(40);

    sf::Vector2i origine=sf::Vector2i(sf::VideoMode::getDesktopMode().width/2-10*wLargeur,sf::VideoMode::getDesktopMode().height/2-10*wHauteur);


    joueur player(Droite,origine.x+20*wLargeur/2,origine.y+20*wHauteur/2);

    Direction dirPlayer = Droite;

    std::vector <point> tabPoints;
    ajoutBordure(&tabPoints, origine.x, origine.y);

    int score = 0;
    int nBonus=0;
    int delta=5;
    int taux=0;


    bonus pointBonus;

    int hulkIndex=-1;

    srand (time(NULL));

    afficherMenu(window, ecran.x, ecran.y);

    sf::Clock tickPlayer,tempsPoints,entre2Bonus,compteurBonus,clockScore;

    while(window.isOpen() )
    {   
        if(!gameOver) //si on a pas perdu
        {
            sf::Event event;

            
           

            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed) 
                    window.close() ;

                

                if(event.type == sf::Event::KeyPressed)  // on change la direction 
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Down:
                        if(player.getDirection()!=Haut)
                            player.setDirection(Bas);
                        break;
                    case sf::Keyboard::Up:
                        if(player.getDirection()!=Bas)
                            player.setDirection(Haut);
                        break;
                    case sf::Keyboard::Z:
                        if(player.getDirection()!=Bas)
                            player.setDirection(Haut);
                        break;
                    
                    case sf::Keyboard::S:
                        if((player.getDirection()!=Haut))
                            player.setDirection(Bas);
                        break;
                   
                    case sf::Keyboard::Right:
                        if(player.getDirection()!=Gauche)
                           player.setDirection(Droite);
                        break;
                    case sf::Keyboard::D:
                        if(player.getDirection()!=Gauche)
                            player.setDirection(Droite);
                        break;
                    
                    case sf::Keyboard::Left:
                        if(player.getDirection()!=Droite)
                            player.setDirection(Gauche);
                        break;
                    case sf::Keyboard::Q:
                        if(player.getDirection()!=Droite)
                            player.setDirection(Gauche);
                        break;

                    default:
                        break;
                    }
                    
                }
            }

            sf::Time temps1 = tickPlayer.getElapsedTime();
            
            if( temps1>speed) // on actualise la position du joueur
            {
                player.actu();

                if(player.bonus()==Normal)
                {
                    player.setColor(sf::Color(254,254,254));

                    tBonus.setString("Aucun Bonus Pour Le Moment");
                }


                int x=player.getRect().getPosition().x;
                int y=player.getRect().getPosition().y;

                if(x>=800+origine.x || x<0+origine.x || y>=800+origine.y || y<0+origine.y)
                    gameOver=true;

                tickPlayer.restart();
            }

            //gestion du Score


            delta=5+(float)taux/3*2;

            sf::Time tempsScore = clockScore.getElapsedTime();
            if( tempsScore>vitesseScore)
            {
                score+=delta;
                tScore.setString(std::to_string(score));
                clockScore.restart();
            }


            sf::Time temps2 = tempsPoints.getElapsedTime();

            if( temps2>vitessePoints) // on ajoute de nouveau points
            {
                bool test=false;
                int xRand ;
                int yRand;

                int xP=player.getRect().getPosition().x;
                int yP=player.getRect().getPosition().y;

                while(!test)
                {
                    test=true;

                    xRand = std::rand()%wLargeur*20+origine.x;
                    yRand = std::rand()%wHauteur*20+origine.y;

                    if(xRand==player.getRect().getPosition().x  &&  yRand==player.getRect().getPosition().y)
                        test=false;


                        // le nouveau point rouge ne pop pas sur un bonus
                    if(pointBonus.isDrawable() && xRand==pointBonus.getRect().getPosition().x && yRand==pointBonus.getRect().getPosition().y )
                        test=false;

                    for(int i=0;i<tabPoints.size();i++)  // les les points ne se superposent pas 
                    {
                        if(xRand==tabPoints[i].getRect().getPosition().x && yRand==tabPoints[i].getRect().getPosition().y)
                            test=false;
                    }

                    if((xRand==xP+20 && yRand==yP+20) || ( xRand==xP+20 && yRand==yP) || ( xRand==xP && yRand==yP+20))
                        test=false;
                    
                    if((xRand==xP-20 && yRand==yP-20) || ( xRand==xP-20 && yRand==yP) || ( xRand==xP && yRand==yP-20))
                        test=false;

                    if( (xRand==xP+20 && yRand==yP-20) || (xRand==xP-20 && yRand==yP+20))
                        test=false;

                }

                


                point p(xRand,yRand);
                p.setColor(sf::Color(250,0,0));

                tabPoints.push_back(p);

                tempsPoints.restart();

            }


            sf::Time tempsEntre2Bonus = entre2Bonus.getElapsedTime();

            if( tempsEntre2Bonus.asSeconds() > 10 && !pointBonus.isDrawable()) // fin du bonus
            {
                speed = sf::milliseconds(VITESSEJOUEUR);

                player.setBonus(Normal);

                hulkIndex = -1;

                vitesseScore = sf::milliseconds(VITESSESCORE);

                pointBonus.setRandomType();

                int xRand,yRand;

                bool test=false;

                int t=1;

                while(!test) // le bonus ne pop pas sur le joueur ou sur un point rouge
                {
                    xRand = std::rand()%wLargeur*20+origine.x;
                    yRand = std::rand()%wHauteur*20+origine.y;


                    test=true;

                    for(int i=0;i<tabPoints.size();i++)
                    {
                        int xPoint = tabPoints[i].getRect().getPosition().x;
                        int yPoint = tabPoints[i].getRect().getPosition().y;

                        if(xRand==xPoint && yRand==yPoint)
                            test=false;
                    }

                    if(xRand==player.getRect().getPosition().x && yRand==player.getRect().getPosition().y)
                        test=false;


                }

                pointBonus.setPosition(xRand,yRand);

                pointBonus.setDrawable(true);

                compteurBonus.restart();  // on remet le compteurBonus à 0 pour afficher le Bonus 20sec
            }
            else if( tempsEntre2Bonus.asSeconds() > 9 && !pointBonus.isDrawable() && player.bonus()==Hulk)
                player.setColor(sf::Color(143,203,153));


            sf::Time tempsPopBonus = compteurBonus.getElapsedTime();
            if( pointBonus.isDrawable() && tempsPopBonus.asSeconds()>20) // si le temps de pop du bonus est dépassé
            {
                pointBonus.setDrawable(false);
                entre2Bonus.restart();
            }

            else if(pointBonus.isDrawable() && tempsPopBonus.asSeconds()>18 && player.bonus()==Hulk)
            {
            }

            if(pointBonus.isDrawable())
                window.draw(pointBonus.getRect());


            int x=player.getRect().getPosition().x;
            int y=player.getRect().getPosition().y;

            int xB=pointBonus.getRect().getPosition().x;
            int yB=pointBonus.getRect().getPosition().y;

            if( x==xB && y==yB && pointBonus.isDrawable()) // si le joueur touche le bonus
            {

                nBonus++;

                if(pointBonus.getType() == Flash)
                {
                    vitesseScore = sf::milliseconds(VITESSESCORE/10);
                    speed = speed/(float)2;
                    player.setBonus(Flash);
                    player.setColor(sf::Color(250,250,0));
                    tBonus.setString(L"     FLASH\n\n\n\nVotre vitesse est doublée\n\nVotre gain est multiplié par 10");
                }

                if(pointBonus.getType() == Lent)
                {
                    vitesseScore = sf::milliseconds(VITESSESCORE/3);
                    player.setBonus(Lent);
                    speed = speed*(float)2;
                    player.setColor(sf::Color(0,250,250));
                    tBonus.setString(L"     RALENTISSEMENT\n\n\n\nVotre vitesse est divisé par 2\n\nVotre gain est triplé");
                } 
                if( pointBonus.getType() == Hulk)
                {
                    player.setBonus(Hulk);
                    player.setColor(sf::Color(30,150,50));
                    tBonus.setString(L"     HULK\n\n\n\nVous détruisez les briques\n\nUne brique détruite vous\nrapporte 100 points");
                }

                if( pointBonus.getType() == Reset)
                {
                    player.setBonus(Reset);
                    tabPoints.clear();
                    ajoutBordure(&tabPoints, origine.x, origine.y);
                    score*=2;
                    tBonus.setString(L"     RESET\n\n\n\nUltime bonus, toute les briques sont effacées,\n vos points sont doublés");
                }
                if (pointBonus.getType() == Score)
                {
                    vitesseScore = sf::milliseconds(VITESSESCORE/6);
                    player.setBonus(Score);
                    player.setColor(sf::Color(169,169,169));
                    tBonus.setString(L"     BOOST\n\n\n\nVotre gain est multiplié par 6");
                }
                    


                pointBonus.setDrawable(false);
                entre2Bonus.restart();
            }


            window.draw(player.getRect());

            for(int i=0;i<tabPoints.size();i++) //on verifie que le joueur ne touche pas un point rouge et on déssine les points
            {
                int xPoint = tabPoints[i].getRect().getPosition().x;
                int yPoint = tabPoints[i].getRect().getPosition().y;


                if(x==xPoint && y==yPoint)
                {
                    if(player.bonus()==Hulk)
                        hulkIndex=i;
                    else
                        gameOver=true;
                }

                if(i!=hulkIndex)
                    window.draw(tabPoints[i].getRect());
            }

            if(hulkIndex!=-1)
            {
                tabPoints.erase( tabPoints.begin()+ hulkIndex );

                score+=100+taux*10;
                hulkIndex=-1;
            }


            //                      on affiche le taux d'occupation
            taux=(int)(((float)tabPoints.size()-164)/1600*100);

            occupationText.setString(std::to_string(taux)+" %");
            window.draw(occupationText);
            
            window.draw(tScore);
            window.draw(tBonus);
            window.display();
            window.clear();

        }
        else //si c'est perdu
        {

            sf::Event event;

            


                while(window.pollEvent(event))
                {
                    if(event.type == sf::Event::Closed) 
                        window.close() ;


                    if (event.type == sf::Event::TextEntered )
                    {
                        if( event.text.unicode==8 && playerInput.getSize()!=0)
                        {
                            std::string tString = std::string(playerInput);
                            tString.pop_back();

                            playerInput= sf::String(tString);


                            playerText.setString(playerInput);
                        }
                        else if( event.text.unicode < 128)
                        {

                            playerInput +=event.text.unicode;
                            playerText.setString(playerInput);
                        }
                    }

                    if(event.type == sf::Event::KeyPressed)
                    {
                        switch (event.key.code)
                        {
                            case sf::Keyboard::Return:

                                if(playerText.getString().getSize()!=0)
                                {
                                    int taux=(int)(((float)tabPoints.size()-164)/1600*100);
                                    enregistrer(std::string(playerText.getString()), score, taux, nBonus);
                                }

                                afficherMenu(window, ecran.x, ecran.y);
                                gameOver=false;
                                score=0;
                                nBonus=0;
                                speed = sf::milliseconds(300); //vitesse joueur
                                tabPoints.clear();
                                ajoutBordure(&tabPoints, origine.x, origine.y);

                                tickPlayer.restart();
                                clockScore.restart();
                                tempsPoints.restart();
                                entre2Bonus.restart();
                                compteurBonus.restart();  // on remet le compteurBonus à 0 pour afficher le Bonus 20sec

                                player = joueur(Droite,origine.x+20*wLargeur/2,origine.y+20*wHauteur/2);
                                break;
                            default:
                                break;
                        }

                    }
                }

                for(int i=0;i<tabPoints.size();i++)
                {
                    window.draw(tabPoints[i].getRect());
                }

                afficherGO(window, Tusj, ecran);





                window.draw(playerText);
                window.draw(occupationText);
                window.draw(tScore);
                window.draw(nameLabel);
                window.display();
                window.clear();
        }
    }


    return 0;
}

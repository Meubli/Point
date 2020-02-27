#include "point.h"
#include "myGui.h"

int wLargeur=40;
int wHauteur=40;
sf::Time speed = sf::milliseconds(300); //vitesse joueur

sf::Time vitessePoints= sf::milliseconds(1000);  //allure de pop des points


#define VITESSESCORE 500
#define VITESSEJOUEUR 300




int main(int argc, const char** argv) {

    bool gameOver=false;

    sf::Time vitesseScore = sf::milliseconds(VITESSESCORE);
    sf::Time speed = sf::milliseconds(VITESSEJOUEUR);

    sf::RenderWindow window;

    window.create(sf::VideoMode(20*wLargeur,20*wHauteur),"JEUX DU POINT");

    window.setFramerateLimit(240);

    Menu menu(window.getSize().x,window.getSize().y);

    joueur player(Droite,20*wLargeur/2,20*wHauteur/2);

    Direction dirPlayer = Droite;

    std::vector <point> tabPoints;

    int score = 0;

    sf::Clock tickPlayer,tempsPoints,entre2Bonus,compteurBonus,clockScore;

    bonus pointBonus;

    int hulkIndex=-1;

    bool wMenu=true;

    while(window.isOpen())
    {   
        if(wMenu)       //dans le menu
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
                        case sf::Keyboard::Z:
                            menu.moveUp(window);

                            break;
                        case sf::Keyboard::Up:
                            menu.moveUp(window);
                            
                            break;


                        case sf::Keyboard::S:
                            menu.moveDown(window);
                            
                            break;
                        case sf::Keyboard::Down:
                            menu.moveDown(window);
                            
                            break;

                        case sf::Keyboard::Return:
                            if(menu.getItemSelected()==0)
                                wMenu=false;
                            else if(menu.getItemSelected()==1)
                                window.close();
                    }
                }
            }
            


            menu.draw(window);
            window.display();
            window.clear();
        }
        else
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
                        case sf::Keyboard::Z:
                            if(player.getDirection()!=Bas)
                                player.setDirection(Haut);
                            break;
                        case sf::Keyboard::Up:
                            if(player.getDirection()!=Bas)
                                player.setDirection(Haut);
                            break;
                        
                        case sf::Keyboard::S:
                            if((player.getDirection()!=Haut))
                                player.setDirection(Bas);
                            break;
                        case sf::Keyboard::Down:
                            if((player.getDirection()!=Haut))
                                player.setDirection(Bas);
                            break;
                        
                        case sf::Keyboard::D:
                            if(player.getDirection()!=Gauche)
                                player.setDirection(Droite);
                            break;
                        case sf::Keyboard::Right:
                            if(player.getDirection()!=Gauche)
                                player.setDirection(Droite);
                            break;

                        case sf::Keyboard::Q:
                            if(player.getDirection()!=Droite)
                                player.setDirection(Gauche);
                            break;
                        case sf::Keyboard::Left:
                            if(player.getDirection()!=Droite)
                                player.setDirection(Gauche);
                            break;
                        
                        //case sf::Keyboard::A:
                        //   tabPoints.clear();

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
                        player.setColor(sf::Color(254,254,254));


                    int x=player.getRect().getPosition().x;
                    int y=player.getRect().getPosition().y;

                    if(x>=800 || x<0 || y>=800 || y<0)
                        gameOver=true;

                    tickPlayer.restart();
                }

                

                sf::Time tempsScore = clockScore.getElapsedTime();   //gestion du Score
                if( tempsScore>vitesseScore)
                {
                    score+=5;

                    system("clear");
                    std::cout<<"******* Jeux du Point ********"<<std::endl<<std::endl;
                    std::cout<<"    Vert -> Hulk   Gris -> Halte   Jaune -> Flash   "<< std::endl<<"    Bleu ciel -> Lent   Violet -> Score    "<<std::endl<<std::endl;
                    std::cout<<"Votre score: "<<score<<std::endl;

                    clockScore.restart();
                }


                sf::Time temps2 = tempsPoints.getElapsedTime();

                if( temps2>vitessePoints  && player.bonus()!=Halte) // on ajoute de nouveau points  si il n'y a pas de bonus Halte en cours
                {
                    bool test=false;
                    int xRand ;
                    int yRand;

                    while(!test)
                    {
                        test=true;

                        xRand = std::rand()%wLargeur*20;
                        yRand = std::rand()%wHauteur*20;

                        if(xRand==player.getRect().getPosition().x  &&  yRand==player.getRect().getPosition().y)
                            test=false;


                            // le nouveau point rouge ne pop pas sur un bonus
                        if(pointBonus.isDrawable() && xRand==pointBonus.getRect().getPosition().x && yRand==pointBonus.getRect().getPosition().y )
                            test=false;
                    }

                    

                    while(xRand==player.getRect().getPosition().x  &&  yRand==player.getRect().getPosition().y)
                    {
                        xRand = std::rand()%wLargeur*20;
                        yRand = std::rand()%wHauteur*20;
                    }

                    point p(xRand,yRand);
                    p.setColor(sf::Color(250,0,0));

                    tabPoints.push_back(p);

                    tempsPoints.restart();

                }


                sf::Time tempsEntre2Bonus = entre2Bonus.getElapsedTime();

                if( tempsEntre2Bonus.asSeconds() > 9 && tempsEntre2Bonus.asSeconds() < 10 && player.bonus()== Hulk)
                {
                    player.setColor(sf::Color(51,255,51));
                }

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
                        xRand = std::rand()%wLargeur*20;
                        yRand = std::rand()%wHauteur*20;


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


                sf::Time tempsPopBonus = compteurBonus.getElapsedTime();
                if( pointBonus.isDrawable() && tempsPopBonus.asSeconds()>15) // si le temps de pop du bonus est dépassé
                {
                    pointBonus.setDrawable(false);
                    entre2Bonus.restart();
                }

                if(pointBonus.isDrawable())
                    window.draw(pointBonus.getRect());


                int x=player.getRect().getPosition().x;
                int y=player.getRect().getPosition().y;

                int xB=pointBonus.getRect().getPosition().x;
                int yB=pointBonus.getRect().getPosition().y;

                if( x==xB && y==yB && pointBonus.isDrawable()) // si le joueur touche le bonus
                {
                    if(pointBonus.getType() == Flash)
                    {
                        vitesseScore = sf::milliseconds(VITESSESCORE/2);
                        speed = speed/(float)2;
                        player.setBonus(Flash);
                        player.setColor(sf::Color(250,250,0));  //jaune
                    }

                    else if(pointBonus.getType() == Lent)
                    {
                        player.setBonus(Lent);
                        speed = speed*(float)2;
                        player.setColor(sf::Color(0,250,250));  //bleu ciel

                        
                    } 
                    else if( pointBonus.getType() == Hulk)
                    {
                        player.setBonus(Hulk);
                        player.setColor(sf::Color(30,150,50));  //vert
                    }

                    else if( pointBonus.getType() == Reset)  
                    {
                        player.setBonus(Reset);
                        tabPoints.clear();
                    }
                    else if( pointBonus.getType() == Halte)
                    {
                        player.setBonus(Halte);
                        player.setColor(sf::Color(160,160,160)); // gris
                    }
                    else if(pointBonus.getType() == Score)
                    {
                        player.setBonus(Score);
                        vitesseScore/=(float)4;
                        player.setColor(sf::Color(204,0,204));  //violet

                        
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

                    score+=10;
                    hulkIndex=-1;
                }


                

                window.display();
                window.clear();

            }
            else //si c'est perdu
            {
                window.close();
                std::cout<<"GAME OVER !!!!!!  "<<std::endl;
            }
        }
    }


    return 0;
}

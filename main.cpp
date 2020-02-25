#include "point.h"

int wLargeur=40;
int wHauteur=40;
sf::Time speed = sf::milliseconds(300); //vitesse joueur

sf::Time vitessePoints= sf::milliseconds(1000);  //allure de pop des points



void displayScore(int score)
{
    system("clear");
    std::cout<<"******* Jeux du Point ********"<<std::endl<<std::endl;
    std::cout<<"Votre score: "<<score<<std::endl;
}


int main(int argc, const char** argv) {

    bool gameOver=false;

   

    sf::RenderWindow window;

    window.create(sf::VideoMode(20*wLargeur,20*wHauteur),"JEUX DU POINT");

    window.setFramerateLimit(240);

    joueur player(Droite,20*wLargeur/2,20*wHauteur/2);

    Direction dirPlayer = Droite;

    std::vector <point> tabPoints;

    int score = 0;

    sf::Clock tickPlayer,tempsPoints;

    while(window.isOpen())
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
                    
                    case sf::Keyboard::S:
                        if((player.getDirection()!=Haut))
                            player.setDirection(Bas);
                        break;
                    
                    case sf::Keyboard::D:
                        if(player.getDirection()!=Gauche)
                            player.setDirection(Droite);
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


                int x=player.getRect().getPosition().x;
                int y=player.getRect().getPosition().y;

                if(x>=800 || x<0 || y>=800 || y<0)
                    gameOver=true;

                score+=1;

                displayScore(score);

                tickPlayer.restart();
            }


            sf::Time temps2 = tempsPoints.getElapsedTime();

            if( temps2>vitessePoints) // on ajoute de nouveau points
            {
                int xRand = std::rand()%wLargeur*20;
                int yRand = std::rand()%wHauteur*20;

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

            int x=player.getRect().getPosition().x;
            int y=player.getRect().getPosition().y;


            window.draw(player.getRect());

            for(int i=0;i<tabPoints.size();i++) //on verifie que le joueur ne touche pas un point rouge et on déssine les points
            {
                int xPoint = tabPoints[i].getRect().getPosition().x;
                int yPoint = tabPoints[i].getRect().getPosition().y;


                if(x==xPoint && y==yPoint)
                    gameOver=true;
                window.draw(tabPoints[i].getRect());
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


    return 0;
}

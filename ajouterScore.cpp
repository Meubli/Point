#include "myGui.h"

using namespace std;

int main()
{
    ifstream fScore("score.txt");

    string ligne;
    char a;

    if(fScore)
    {
        while(fScore.get(a))
        {
            ligne.push_back(a);
        }
    }
    else
        cout<<"Probleme avec le fScore score.txt"<<endl;

    
    for(int i=0;i<(int)ligne.size();i++)
    {
        ligne[i]=dechiffrer(ligne[i]);
        
    }

    vector<string>* tNom;
    tNom = new vector<string>;

    vector<int>* tScore;
    tScore= new vector<int>;

    vector<int>* tTaux;
    tTaux= new vector<int>;

    vector<int>* tBonus;
    tBonus= new vector<int>;

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


    for(int i=0;i<(int)tNom->size();i++)
    {
        cout<<i<<" "<<(*tNom)[i]<<" "<<(*tScore)[i]<<endl;
        
    }

    int score2, taux2, bonus2;
    std::string nom2;


    cout<<endl<<endl<<"Nom: ";
    cin>>nom2;

    cout<<"Score: ";
    cin>>score2;

    cout<<"Taux: ";
    cin>>taux2;

    cout<<"Bonus: ";
    cin>>bonus2;

    tNom->push_back(nom2);
    tScore->push_back(score2);
    tBonus->push_back(bonus2);
    tTaux->push_back(taux2);
    
    ofstream fichier("score.txt");

    if(fichier)
    {
        for(int i=0;i<(int)tNom->size();i++)
        {
                std::string save;
                save=(*tNom)[i]+" "+std::to_string((*tScore)[i])+" "+std::to_string((*tTaux)[i]);
                save+=" "+std::to_string((*tBonus)[i])+"\n";


                for(int j=0; j<(int)save.size();j++)
                {
                    save[j]=chiffrer(save[j]);
                }


                fichier<<save;
        }

        
    }
    else
    {
        std::cout<<"Probleme avec le fichier score.txt"<<std::endl; 
    }

    
}

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string encryptDecrypt(string toEncrypt) {
    char key = 'K'; //Any char will work
    string output = toEncrypt;
    
    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;
    
    return output;
}

int main()
{
    ifstream fichier("score.txt");

    string text;
    char a;

    if(fichier)
    {
        while(fichier.get(a))
        {


            text.push_back(a);
        }
    }

    fichier.close();

    text=encryptDecrypt(text);

    ofstream nFichier("score.txt");

    if(nFichier)
    {
        nFichier<<text;
    }

    return 0;

}

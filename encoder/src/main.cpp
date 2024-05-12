#include <iostream>
#include <fstream>
#include <string>

#include "encoder.h"



void copyScriptToOutput(std::ifstream& inputFile,
                        std::string& outText )
{
    std::string line;
    while (std::getline(inputFile, line))
    {
        
#if _DEBUG
        std::cout << line << std::endl;
        std::cout << encoder::encrypt(line) << std::endl;
#endif
        

        outText += "\tscriptLine = ";
        outText += '\"';//debut de ligne
        outText += encoder::encrypt(line);
        outText += '\"';//fin de ligne
        outText += ';';//fermeture de la ligne
        outText += '\n';//retour a la ligne

        outText += "\tfileContent += ";//lier au modele: on le passera en parametre si necessaire
        outText += "decrypt(scriptLine) + \"\\n\"";//la commande de decrypt pour l'autre programme
        outText += ';';//fermeture de la ligne
        outText += '\n';//retour a la ligne
    }
}


int main(int argc, char* argv[])
{

    //argc: nombre d'argument
    //argv[]: la liste d'argument
    //exemple: ./convertfile.exe -f:text0.txt
    

    //fichier d'entrée: script
    std::ifstream inputFile;
    //std::ifstream inputFile("./script/text.txt");
    
    bool is_argument = false;
    if (argc)
    {
        for (int i = 1; i < argc; i++) {
            if (argv[0] == NULL) {
                continue;
            }

            //cherche le '-' pour debut argument
            if (argv[i][0] == '-')
            {
                std::string argText = &argv[i][0];
                std::cout << "Argument: " << argText << std::endl;

                // est que le "-f:" exist?
                if (argText.find("-f:") != std::string::npos)
                {// "-f:" pour filename
                    //on va dans le dossier /script pour chercher le fichier de l'argument
                    std::string scriptFilename;
                    scriptFilename = "../script/";
                    scriptFilename += &argv[i][3];//recupere le filename sans "-f:"

                    std::cout << "Path: " << scriptFilename << std::endl;

                    inputFile = std::ifstream(scriptFilename);

                    //set flag, on a un argument pour le fichier script
                    is_argument = true;
                }                
            }    
        }            
    }

    if (is_argument==false)
    {
#if _DEBUG
        inputFile = std::ifstream("./script/text0.txt");
#else
        //fichier par defaut pour tester
        inputFile = std::ifstream("../script/text0.txt");
#endif

        
    }

    //verifie le fichier d'entrée
    if(inputFile.is_open() == false)
    {
        std::cout << "error: open inputFile failed" << std::endl;
        exit(0);
    }


    
#if _DEBUG
    std::ifstream inputModeleFile("./modele/hidefile.cpp");
#else
    //fichier modele
    std::ifstream inputModeleFile("../modele/hidefile.cpp");
#endif
    

    if(inputModeleFile.is_open() == false)
    {
        std::cout << "error: open inputModeleFile failed" << std::endl;
        exit(0);
    }


#if _DEBUG
    std::ofstream outputFile("./output/hidefile.cpp");
#else
    //fichier de sortie
    std::ofstream outputFile("../output/hidefile.cpp");
#endif
    
    if(outputFile.is_open() == false)
    {
        std::cout << "error: open outputFile failed" << std::endl;
        exit(0);
    }
     
    //1. lire le modele et copier vers la sortie jusqu'au flag DEBUT_COPY
    //2. lire le fichier script et copier tout le contenu vers la sortie
    //3. lire la fin du contenu du fichier modele et copier vers la sortie
    //!note: la sortie = fichier de sortie /output/hidefile.cpp

    std::string outText;
    std::string line;
    while (std::getline(inputModeleFile, line))
    {
        //std::cout << line << std::endl;

        outText += line;
        outText += "\n"; 

        if( line.find("DEBUT_COPY") != std::string::npos)
        {
            //on a trouvé le point d'entrée pour copier le script
            copyScriptToOutput(inputFile, outText);
        }
    }
    
    
    outputFile << outText << std::endl;
    outputFile.close();

    return 0;
}

/*EOF*/


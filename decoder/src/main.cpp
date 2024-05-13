// fait ce que le fichier .ps1 fait et l'execute
//https://stackoverflow.com/questions/55037943/how-should-c-execute-the-powershell-command

#include <iostream>
//#include <process.h>
#include <fstream>

#include "hidefile.h"


int main(void)
{
    //create temporary file to save script
    std::ofstream file;
    file.open("tempfile.ps1");

    //create the script
    std::string outputText = HideFile::retrieve();

    //put the script into file
    file << outputText << std::endl;
    file.close();

#if defined(_WIN32) || defined(WIN32)
    system("powershell -ExecutionPolicy Bypass -F tempfile.ps1"); //run the script on windows
    //DEBUG system("type tempfile.ps1");//show content
	remove("tempfile.ps1");//delete the temporary file
#else
    system("bash tempfile.sh");    //run the script on linux
	remove("tempfile.sh");//delete the temporary file
#endif

    
    

    return 0;
}




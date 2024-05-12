/* !MODELE */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>


#include "hidefile.h"
#include "ascii.h"

static std::string decrypt(const std::string line)
{
    std::string result;

    if (line.empty() == true)
    {
        return "";
    }

    //1.delete les caracteres '{' et '}'
    //2.split le string pour récupérer chaque valeur
    //3.reconstruction du string originel

    result = line;
    result.erase(0, 1);                 //remove first character '{'
    result.erase(result.size() - 1);    //remove last character '}'


    //array pour stocker les valeurs
    std::vector<uint8_t> byteArray;

    //formate string en stringstream
    std::stringstream input_stringstream(result);

    for (std::string parsed; std::getline(input_stringstream, parsed, ','); )
    {
        int nums = std::stoi(parsed);

        //cast en uint8_t
        byteArray.push_back(static_cast<uint8_t>(nums));
    }

    result = "";
    for (uint8_t value : byteArray)
    {
        uint8_t decodedValue = 0;

        for (int i = 0; i < DefAsciiTableSize; i++)
        {
            if ((uint8_t)ascii_rand_table[i][1] == value)
            {
                decodedValue = (uint8_t)ascii_rand_table[i][0];
                break;
            }
        }

        char c = static_cast<uint8_t>(decodedValue);
        result += c;
    }

    return result;
}



std::string HideFile::retrieve(void)
{
    std::string scriptLine;
    std::string fileContent;


    fileContent = "";

    /*DEBUT_COPY*/
	scriptLine = "{33,198,240,33,198,147,228,48,147,222,227,41,52,110,198,164}";
	fileContent += decrypt(scriptLine) + "\n";
	scriptLine = "{33,239,215,41}";
	fileContent += decrypt(scriptLine) + "\n";
	scriptLine = "{29,164,198,198,108}";
	fileContent += decrypt(scriptLine) + "\n";
	scriptLine = "{48,239,48,211}";
	fileContent += decrypt(scriptLine) + "\n";

	/*FIN_COPY*/

    return fileContent;
}





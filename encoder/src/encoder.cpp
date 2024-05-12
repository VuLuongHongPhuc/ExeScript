
#include <iostream>
#include <string>
#include <vector>
//#include <iomanip>
#include <sstream>
#include <cstdint>

#include "encoder.h"
#include "ascii.h"

//using namespace std;

/*

void addBackSlashOnEscapeSequence(std::string& line, char c)
{
    int pos = 0;
    do{
        //std::cout << line << std::endl;

        pos = line.find(c, pos);
        if(pos != -1)
        {
            line.insert(pos, 1, '\\');
            pos+=2;
        }

        //std::cout << line << std::endl;
    }while(pos != -1);
}

std::string formatLine(std::string line)
{
    // l'ordre est important
    addBackSlashOnEscapeSequence(line, '\\');
    addBackSlashOnEscapeSequence(line, '\"');

    return line;
}
*/

/*
static string decimalStr( const uint8_t data)
{
	stringstream ss;
	ss << std::dec;
    
	ss << data;

	return ss.str();
}

static std::string hexStr(const uint8_t data)
{
	stringstream ss;
    ss << std::hex;

	ss << std::setw(2) << std::setfill('0') << static_cast<uint8_t>(data);

	return ss.str();
}
*/

std::string encoder::encrypt(const std::string line)
{
	std::string result;

	std::vector<uint8_t> byteArray;

	// Iterate over each character in the string
	for (char c : line) {
		// Convert the character to its ASCII value and append it to the byte array
		byteArray.push_back(static_cast<uint8_t>(c));
	}


	result = "{";

	for (uint8_t value : byteArray)
	{
		int encodedValue = ascii_rand_table[value][1];
		//std::cout << encodedValue << std::endl;
		result += std::to_string(encodedValue);
		result += ",";
	}

	//replace the last caractere ',' to '}'
	std::size_t lastCarPos = result.length();
	//std::cout << result.at(lastCarPos-1);
	result.replace(lastCarPos - 1, 1, "}");

	return result;
}


std::string encoder::decrypt(const std::string line)
{
    std::string result;

    if (line.empty() == true)
    {
        return "";
    }

    //1.delete les caracteres '{' et '}'
    //2.split le string pour r�cup�rer chaque valeur
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

/*EOF*/


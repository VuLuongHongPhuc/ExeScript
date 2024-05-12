#pragma once


class encoder
{
   
public:

    static void test() { std::cout << "reussit" << std::endl; };

    static std::string encrypt(const std::string line);
    static std::string decrypt(const std::string line);
};


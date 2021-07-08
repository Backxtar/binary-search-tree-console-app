//
// Created by joerg on 06.07.2021.
//

#ifndef P5_CLION_UTIL_H
#define P5_CLION_UTIL_H
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>

class Util
{
public:
    static std::vector<int> initData(int amount)
    {
        std::vector<int> database;
        srand(time(nullptr));

        for (int i = 0; i < amount; i++)
            database.push_back(rand() % 100 + 1);

        return database;
    }

    static bool isBin(const long key)
    {
        std::string keyStr = std::to_string(key);
        for (const char &c : keyStr)
        {
            if (isdigit(c) == false || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
                return false;
        }
        return true;
    }

    inline int getChoice()
    {
        std::string str;

        while (std::getline(std::cin, str))
        {
            if (str.empty())
            {
                std::cout << "Error in getChoice(): There was no input. Try again." << std::endl;
                continue;
            }
            size_t const flag = str.find_first_not_of("-0123456789");

            if (flag != std::string::npos)
            {
                std::cout << "Error in getChoice(): Wrong input. Try again." << std::endl;
                continue;
            }
            return std::stoi(str);
        }
    }

    static bool isDigit(const std::string& input)
    {
        for (const char &c : input)
        {
            if(isdigit(c) == false)
                return false;
        }
        return true;
    }

    static bool getInput(const std::string& input)
    {
        if (!isDigit(input))
            return false;
        return std::stoi(input) < 1 || std::stoi(input) > 13;
    }
};

#endif //P5_CLION_UTIL_H

#include <iostream>
#include "AuxiliaryFunctions.h"
#include <algorithm>
#include <sstream>
#include <vector>

/**
 * @brief Checks if a string represents a number
 * @param str
 * @return bool, true if it's a number, false if it's not
 */
bool isAllDigits(const std::string &str) {
    // Iterates each character in a std::string and checks if it's an integer or not
    if(str.empty()) return false;

    for(char c: str){
        if (!isdigit(c)){
            return false;
        }
    }

    return true;
}

/**
 * @brief Check if a number in the correct interval (0 to a) is inputted
 * @param a
 * @param text
 * @return bool
 */
bool parseInput(int a, const std::string& text){
    std::vector<int> values;

    for(int i = 0; i <= a; i++){
        values.push_back(i);
    }

    auto it = values.begin();

    if (isAllDigits(text)) {
        it = std::find(values.begin(), values.end(), stoi(text));
        if (it != values.end()) {
            return true;
        } else {
            std::cerr << std::endl << "Input invalido!" << std::endl << std::endl;
        }
    } else {
        std::cerr << std::endl << "Input invalido!" << std::endl << std::endl;
    }

    return false;
}

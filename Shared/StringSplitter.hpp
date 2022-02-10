/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Created by Leo Fabre
*/
#ifndef STRINGSPLITTER_HPP
#define STRINGSPLITTER_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

class StringSplitter {
public:
    ///@return returns a vector of std::strings containing str splitted on delims characters.
    ///@param str the string to split
    ///@param delims characters to split str on.
    static std::vector<std::string> split(
        const std::string &str, const std::string &delims
    )
    {
        std::vector<std::string> cont;
        std::size_t current, previous = 0;
        current = str.find_first_of(delims);
        while (current != std::string::npos) {
            cont.push_back(str.substr(previous, current - previous));
            previous = current + 1;
            current = str.find_first_of(delims, previous);
        }
        cont.push_back(str.substr(previous, current - previous));
        return cont;
    }


    ///@return returns a vector of std::strings containing str splitted on delims characters.
    ///@param str the string to split
    ///@param c single character to split str on.
    static std::vector<std::string> split(
        const std::string &str, const char &c
        ) {
        std::vector<std::string> cont;
        std::size_t current, previous = 0;
        current = str.find_first_of(c);
        while (current != std::string::npos) {
            cont.push_back(str.substr(previous, current - previous));
            previous = current + 1;
            current = str.find_first_of(c, previous);
        }
        cont.push_back(str.substr(previous, current - previous));
        return cont;
    }


    ///@return returns a vector of std::strings containing str splitted on 'space' and 'tab' characters (whitespaces).
    ///@param str the string to split
    static std::vector<std::string> split_ws(const std::string &str)
    {
        return split(str, " \t");
    }

    ///@return returns a vector of std::strings containing str splitted on 'newline' characters.
    ///@param str the string to split
    static std::vector<std::string> split_lines(const std::string &str)
    {
        return split(str, "\n");
    }

    StringSplitter() = delete;
};

#endif //STRINGSPLITTER_HPP
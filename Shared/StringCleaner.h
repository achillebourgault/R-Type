/*
** EPITECH PROJECT, 2024
** StringCleaner.h
** File description:
** Created by Leo Fabre
*/
#ifndef STRINGCLEANER_H
#define STRINGCLEANER_H

#include <iostream>
#include <string>

class StringCleaner {
public:

    /// @return returns str without leading and trailing whitespace characters
    /// @param str the string to trim
    /// @param whitespace characters that count as whitespace (default " \\t")
    static std::string trim(
        const std::string &str,
        const std::string &whitespace = " \t"
    )
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
            return "";
        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;
        return str.substr(strBegin, strRange);
    }

    /// @return returns trim(str, whitespace) and replaces inner whitespace chars with "replace_with"
    /// @param str the string to trim
    /// @param replace_with characters to replace inner whitespaces with
    /// @param whitespace characters that count as whitespace
    static std::string reduce(
        const std::string &str,
        const std::string &replace_with = " ",
        const std::string &whitespace = " \t"
    )
    {
        // trim first
        auto result = trim(str, whitespace);

        // replace sub ranges
        auto beginSpace = result.find_first_of(whitespace);
        while (beginSpace != std::string::npos) {
            const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
            const auto range = endSpace - beginSpace;
            result.replace(beginSpace, range, replace_with);
            const auto newStart = beginSpace + replace_with.length();
            beginSpace = result.find_first_of(whitespace, newStart);
        }

        return result;
    }

    static std::string getFileName(std::string path)
    {
        const size_t last_slash_idx = path.find_last_of("\\/");
        if (std::string::npos != last_slash_idx) {
            path.erase(0, last_slash_idx + 1);
        }
        const size_t period_idx = path.rfind('.');
        if (std::string::npos != period_idx) {
            path.erase(period_idx);
        }
        return path;
    }

    StringCleaner() = delete;
};



#endif //STRINGCLEANER_H
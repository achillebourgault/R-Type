/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Created by Achille Bourgault
*/
#ifndef R_TYPE_TRADUCTIONS_HPP
#define R_TYPE_TRADUCTIONS_HPP

#include <string>

#define EN 0
#define FR 1

class Traductions {


    public:

    enum labels {
        playBtnLabel,
        optionsBtnLabel,
        leaveBtnLabel,
        backBtnLabel,
        optionFieldLanguage,
        highscoresLabel,
        serversLabel,
        scoresNotFound,
        serversNotFound
    };

    Traductions(int language = EN);
    ~Traductions();
    void setLanguage(int lang);
    int getLanguage();
    std::string get(labels e);

    private:
    int currentLanguage;
};



#endif
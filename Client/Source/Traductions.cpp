/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Created by Achille Bourgault
*/
#include <Traductions.hpp>

Traductions::Traductions(int lang) : currentLanguage(lang)
{
}

Traductions::~Traductions()
{
}

std::string Traductions::get(Traductions::labels e)
{
    switch (e) {

    case playBtnLabel:
        return currentLanguage == EN ? "Play" : "Jouer";
    case optionsBtnLabel:
        return currentLanguage == EN ? "Preferences" : "Options";
    case leaveBtnLabel:
        return currentLanguage == EN ? "Leave" : "Quitter";
    case backBtnLabel:
        return currentLanguage == EN ? "Back" : "Retour";
    case optionFieldLanguage:
        return currentLanguage == EN ? "Language" : "Langue";
    case highscoresLabel:
        return currentLanguage == EN ? "Highscores" : "Meilleurs scores";
    case serversLabel:
        return currentLanguage == EN ? "R-Type > Servers" : "R-Type > Serveurs";
    case scoresNotFound:
        return currentLanguage == EN ? "There is no recent scores." : "Aucun scores trouvés.";
    case serversNotFound:
        return currentLanguage == EN ? "There is no recent server." : "Aucun serveur recent trouvé.";
    default:
        break;
    }
    return "unknown";
}

void Traductions::setLanguage(int lang)
{
    currentLanguage = lang;
}

int Traductions::getLanguage()
{
    return currentLanguage;
}


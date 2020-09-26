#include "language.h"
#include <QDebug>

Language::Language(languageType myLanguage)
{
    this->myLanguage = myLanguage;
    load();
}

void Language::set(languageType l)
{
    myLanguage = l;
}

QString Language::l(QString l)
{
    for (auto i : lData)
    {
        if (i.ENG == l.toStdString())
        {
            return (myLanguage==languageType::Polish)?QString::fromStdString(i.PL):QString::fromStdString(i.ENG);
        }
    }
    return  l;
}

Equivalent::Equivalent(std::string ENG, std::string PL)
{
    this->PL = PL;
    this->ENG = ENG;
}

void Language::load()
{
    lData.push_back(Equivalent("Labyrinth","Labirynt"));
    lData.push_back(Equivalent("Polish","Polski"));
    lData.push_back(Equivalent("English","Angielski"));
    lData.push_back(Equivalent("Menu language","Język menu"));
    lData.push_back(Equivalent("Settings","Ustawienia"));
    lData.push_back(Equivalent("Generate new","Generuj nowy"));
    lData.push_back(Equivalent("Exit","Zamknij"));
    lData.push_back(Equivalent("Find the exit","Szukaj wyjścia"));
    lData.push_back(Equivalent("Blindfold (right hand)","Po omacku (prawa ręka)"));
    lData.push_back(Equivalent("Blindfold (left hand)","Po omacku (lewa ręka)"));
    lData.push_back(Equivalent("forcefully (bruteforce)","Siłowo (bruteforce)"));
    lData.push_back(Equivalent("Wave propagation","Propagacja fali"));
    lData.push_back(Equivalent("Time table","Tablica czasu"));
    lData.push_back(Equivalent("Normal maze","Normalny labirynt"));
    lData.push_back(Equivalent("Horizontal maze","Poziomy labirynt"));
    lData.push_back(Equivalent("Vertical maze","Pionowy labirynt"));
}

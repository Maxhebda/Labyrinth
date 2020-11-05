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
    lData.push_back(Equivalent("Maze settings","Ustawienia labiryntu"));
    lData.push_back(Equivalent("Size","Rozmiar"));
    lData.push_back(Equivalent("Cell in a row","Komórek w rzędzie"));
    lData.push_back(Equivalent("Cell in a column","Komórek w kolumnie"));
    lData.push_back(Equivalent("Cell width","Szerokość komórki"));
    lData.push_back(Equivalent("Cancel","Anuluj"));
    lData.push_back(Equivalent("The changes will be visible after re-generating the maze","Zmiany będą widoczne po ponownym wygenerowaniu labiryntu"));
    lData.push_back(Equivalent("Window size","Rozmiar okna"));
    lData.push_back(Equivalent("Spiral maze, cyclones","Spiralny labirynt, cyklony"));
    lData.push_back(Equivalent("Straight lines (division in half)","Proste linie (podział na pół)"));
    lData.push_back(Equivalent("Straight lines (random split)","Proste linie (losowy podział)"));
    lData.push_back(Equivalent("Zigzags","Zygzaki"));
}

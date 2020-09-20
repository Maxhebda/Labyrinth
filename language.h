#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QList>

class Equivalent
{
public:
    Equivalent(std::string ENG, std::string PL);
    std::string PL;
    std::string ENG;
};

class Language
{
public:
    enum languageType { Polish, English };
    Language(languageType l = Polish);
    void set(languageType l);
    QString l(QString l);

private:
    languageType myLanguage;
    QList<Equivalent> lData;
    void load();
};

#endif // LANGUAGE_H

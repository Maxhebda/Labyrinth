#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <language.h>

//drawing libraries
#include <QImage>
#include <QtGui>
#include <QtCore>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Language
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage * image;
    QPainter * paintOnImage;
    Language *language;
    void refreshLanguage();
    byte globalX;           //number of cells Y
    byte globalY;           //number of cells Y
    byte globalWidth;       //ceil width

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void clickMenuPolish();
    void clickMenuEnglish();
    void clickMenuQuit();
};
#endif // MAINWINDOW_H

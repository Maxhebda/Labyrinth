#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <language.h>
#include <cell.h>
#include <board.h>
#include <QList>
#include <dialog.h>

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
    Ui::MainWindow * ui;
    Dialog * ui_mazeSettings;//menu Maze setings
    QImage * image;
    QPainter * paintOnImage;
    Language * language;
    void refreshLanguage();

    byte globalX;           //number of cells Y
    byte globalY;           //number of cells Y
    byte globalWidth;       //ceil width
    byte setglobalX;        //set in Maze setings menu
    byte setglobalY;        //set in Maze setings menu
    byte setglobalWidth;    //set in Maze setings menu
    void getGlobalSettings();

    void refreshWindowsSize();
    void drawBoard();
    void drawCell(uint8_t y, uint8_t x);
    Board * board;          //myMainBoard

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void clickMenuPolish();
    void clickMenuEnglish();
    void clickMenuQuit();
    void clickMenuMazeSetings();
    void clickMenuGenerateNormalMaze();
    void clickMenuGenerateHorizontalMaze();
    void clickMenuGenerateVerticalMaze();
    void clickMenuGenerateSpiralMaze();
    void clickMenuGenerateStraightLine();
};
#endif // MAINWINDOW_H

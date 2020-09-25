#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //--- set start parameters
    globalX = 20;
    globalY = 20;
    globalWidth = 32;

    //--- connect menu
    connect(ui->actionPolish,SIGNAL(triggered()),this, SLOT(clickMenuPolish()));
    connect(ui->actionEnglish,SIGNAL(triggered()),this, SLOT(clickMenuEnglish()));
    connect(ui->actionQuit,SIGNAL(triggered()),this, SLOT(clickMenuQuit()));

    //--- set default language
    language = new Language(Language::Polish);

    refreshWindowsSize();   //set windows size - auto width and height

    paintOnImage = new QPainter;
    paintOnImage->begin(image);
    //--- draw main frame
    paintOnImage->drawRect(0,0,globalX*globalWidth+1,globalY*globalWidth+1);

    board->generateFrame();
    drawBoard();
    //qDebug() << (6 & 4);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(10,10 + ui->menubar->height(),*image);
    painter.end();
}

MainWindow::~MainWindow()
{
    paintOnImage->end();
    delete image;
    delete paintOnImage;
    delete board;
    delete language;
    delete ui;
}

void MainWindow::clickMenuPolish()
{
    //block signal
    ui->actionPolish->blockSignals(true);
    ui->actionEnglish->blockSignals(true);
    //set checked
    ui->actionPolish->setChecked(true);
    ui->actionEnglish->setChecked(false);
    //unblock signal
    ui->actionPolish->blockSignals(false);
    ui->actionEnglish->blockSignals(false);

    //set language
    language->set(Language::Polish);
    refreshLanguage();
}

void MainWindow::clickMenuEnglish()
{
    //block signal
    ui->actionPolish->blockSignals(true);
    ui->actionEnglish->blockSignals(true);
    //set checked
    ui->actionPolish->setChecked(false);
    ui->actionEnglish->setChecked(true);
    //unblock signal
    ui->actionPolish->blockSignals(false);
    ui->actionEnglish->blockSignals(false);

    //set language
    language->set(Language::English);
    refreshLanguage();
}

void MainWindow::clickMenuQuit()
{
    //close();
}

void MainWindow::refreshLanguage()
{
    QWidget::setWindowTitle(language->l("Labyrinth"));
    ui->actionPolish->setText(language->l("Polish"));
    ui->actionEnglish->setText(language->l("English"));
    ui->menuJ_zyk_menu->setTitle(language->l("Menu language"));
    ui->menuSettings->setTitle(language->l("Settings"));
    ui->menuLabyrinth->setTitle(language->l("Labyrinth"));
    ui->actionNew->setText(language->l("Generate new"));
    ui->actionQuit->setText(language->l("Quit"));
    ui->menuSzukaj_wyj_cia->setTitle(language->l("Find the exit"));
    ui->actionBlindfold_Right->setText(language->l("Blindfold (right hand)"));
    ui->actionBlindfold_Left->setText(language->l("Blindfold (left hand)"));
    ui->actionSi_owo_bruteforce->setText(language->l("forcefully (bruteforce)"));
    ui->actionWave_propagation->setText(language->l("Wave propagation"));
    ui->actionTime_table->setText(language->l("Time table"));
}

void MainWindow::refreshWindowsSize()
{
    //--- paint / create palete
    QWidget::setMinimumHeight(globalY*globalWidth+22+ui->menubar->height());
    QWidget::setMaximumHeight(globalY*globalWidth+22+ui->menubar->height());
    QWidget::setMinimumWidth(globalX*globalWidth+22);
    QWidget::setMaximumWidth(globalX*globalWidth+22);

    image =  new QImage(globalX*globalWidth+2,globalY*globalWidth+2,QImage::Format_RGB32);
    image -> fill(QColor(217,217,217));

    //--- create my board
    board = new Board(globalY, globalX);
}

void MainWindow::drawBoard()
{
    for (int y = 0; y < globalY; y++)
    {
        for (int x = 0; x < globalX; x++)
        {
            drawCell(y,x);
        }
    }
    repaint();
}

void MainWindow::drawCell(int y, int x)
{

 if (board->getCell(y,x).getWall(Cell::UP))
 {
     paintOnImage->drawLine(x*globalWidth+1,y*globalWidth+1, x*globalWidth + globalWidth, y*globalWidth+1);
 }
 if (board->getCell(y,x).getWall(Cell::DOWN))
 {
     paintOnImage->drawLine(x*globalWidth+1, y*globalWidth + globalWidth, x*globalWidth + globalWidth, y*globalWidth + globalWidth);
 }
 if (board->getCell(y,x).getWall(Cell::RIGHT))
 {
     paintOnImage->drawLine(x*globalWidth + globalWidth, y*globalWidth+1,x*globalWidth + globalWidth, y*globalWidth + globalWidth);
 }
 if (board->getCell(y,x).getWall(Cell::LEFT))
 {
     paintOnImage->drawLine(x*globalWidth+1, y*globalWidth+1, x*globalWidth+1, y*globalWidth + globalWidth);
 }
}

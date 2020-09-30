#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);

    //--- set start parameters
    globalX = 10;
    globalY = 10;
    globalWidth = 100;

    //--- connect menu
    connect(ui->actionPolish,SIGNAL(triggered()),this, SLOT(clickMenuPolish()));
    connect(ui->actionEnglish,SIGNAL(triggered()),this, SLOT(clickMenuEnglish()));
    connect(ui->actionQuit,SIGNAL(triggered()),this, SLOT(clickMenuQuit()));
    connect(ui->actionNormal_maze,SIGNAL(triggered()),this, SLOT(clickMenuGenerateNormalMaze()));
    connect(ui->actionHorizontal_maze,SIGNAL(triggered()),this, SLOT(clickMenuGenerateHorizontalMaze()));
    connect(ui->actionVertical_maze,SIGNAL(triggered()),this, SLOT(clickMenuGenerateVerticalMaze()));

    //--- set default language
    language = new Language(Language::Polish);

    //-------------------------------- start palete
    refreshWindowsSize();                   //set windows size - auto width and height
    //-------------------------------- start palete

//    board->generateFrame();
    board->generateTheBeginningOfTheLabyrinth();
    board->generateMaze_methodDFS(0,0);
    drawBoard();
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

void MainWindow::clickMenuGenerateNormalMaze()
{
    refreshWindowsSize();
    board->clear();
    board->generateTheBeginningOfTheLabyrinth();
    board->generateMaze_methodDFS(0,0);
    drawBoard();
}

void MainWindow::clickMenuGenerateHorizontalMaze()
{
    refreshWindowsSize();
    board->clear();
    board->generateTheBeginningOfTheLabyrinth();
    board->generateMaze_methodDFS_horizontal(rand()%(globalY-1),rand()%(globalX-1));
    drawBoard();
}

void MainWindow::clickMenuGenerateVerticalMaze()
{
    refreshWindowsSize();
    board->clear();
    board->generateTheBeginningOfTheLabyrinth();
    board->generateMaze_methodDFS_vertical(rand()%(globalY-1),rand()%(globalX-1));
    drawBoard();
}

void MainWindow::clickMenuMazeSetings()
{

}

void MainWindow::refreshLanguage()
{
    QWidget::setWindowTitle(language->l("Labyrinth"));
    ui->actionPolish->setText(language->l("Polish"));
    ui->actionEnglish->setText(language->l("English"));
    ui->menuJ_zyk_menu->setTitle(language->l("Menu language"));
    ui->menuSettings->setTitle(language->l("Settings"));
    ui->menuLabyrinth->setTitle(language->l("Labyrinth"));
    ui->menuGenerateNew->setTitle(language->l("Generate new"));
    ui->actionQuit->setText(language->l("Quit"));
    ui->menuSzukaj_wyj_cia->setTitle(language->l("Find the exit"));
    ui->actionBlindfold_Right->setText(language->l("Blindfold (right hand)"));
    ui->actionBlindfold_Left->setText(language->l("Blindfold (left hand)"));
    ui->actionSi_owo_bruteforce->setText(language->l("forcefully (bruteforce)"));
    ui->actionWave_propagation->setText(language->l("Wave propagation"));
    ui->actionTime_table->setText(language->l("Time table"));
    ui->actionNormal_maze->setText(language->l("Normal maze"));
    ui->actionHorizontal_maze->setText(language->l("Horizontal maze"));
    ui->actionVertical_maze->setText(language->l("Vertical maze"));
}

void MainWindow::refreshWindowsSize()
{
    //--- create new board;
    board = new Board(globalY, globalX);    // create my board
    globalY = board->getHeight();           //set default
    globalX = board->getWidth();

    //--- paint / create palete
    QWidget::setMinimumHeight(globalY*globalWidth+22+ui->menubar->height());
    QWidget::setMaximumHeight(globalY*globalWidth+22+ui->menubar->height());
    QWidget::setMinimumWidth(globalX*globalWidth+22);
    QWidget::setMaximumWidth(globalX*globalWidth+22);

    image =  new QImage(globalX*globalWidth+2,globalY*globalWidth+2,QImage::Format_RGB32);
    image -> fill(QColor(217,217,217));

    paintOnImage = new QPainter;
    paintOnImage->begin(image);
    //--- draw main frame
    paintOnImage->drawRect(0,0,globalX*globalWidth+1,globalY*globalWidth+1);
}

void MainWindow::drawBoard()
{
    for (uint8_t y = 0; y < globalY; y++)
    {
        for (uint8_t x = 0; x < globalX; x++)
        {
            drawCell(y,x);
        }
    }
    repaint();
}

void MainWindow::drawCell(uint8_t y, uint8_t x)
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

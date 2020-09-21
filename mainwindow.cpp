#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>

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

    //--- paint / create palete
    QWidget::setMinimumHeight(globalY*(globalWidth+1)+20+ui->menubar->height());
    QWidget::setMaximumHeight(globalY*(globalWidth+1)+20+ui->menubar->height());
    QWidget::setMinimumWidth(globalX*(globalWidth+1)+20);
    QWidget::setMaximumWidth(globalX*(globalWidth+1)+20);

    image = new QImage(globalX*(globalWidth+1),globalY*(globalWidth+1),QImage::Format_RGB32);
    image -> fill(QColor(217,217,217));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);

    paintOnImage->drawRect(10,10,32,32);
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
    close();
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

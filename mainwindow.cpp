#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //--- connect menu
    connect(ui->actionPolish,SIGNAL(triggered()),this, SLOT(clickMenuPolish()));
    connect(ui->actionEnglish,SIGNAL(triggered()),this, SLOT(clickMenuEnglish()));
    connect(ui->actionQuit,SIGNAL(triggered()),this, SLOT(clickMenuQuit()));

    //--- set default language
    language = new Language(Language::Polish);
}

MainWindow::~MainWindow()
{
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

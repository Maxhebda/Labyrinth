#include "dialog.h"
#include "ui_dialog.h"
#include <QScreen>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    changeOfSettings = false;
    setX = 10;
    setY = 10;
    setWidth=30;
    getScreenWidthHeight();
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setstart(uint8_t y, uint8_t x, uint8_t width)
{
    ui->spinBox->setValue(x);
    ui->spinBox_2->setValue(y);
    ui->spinBox_3->setValue(width);
    setX = x;
    setY = y;
    setWidth = width;
}

void Dialog::on_pushButton_clicked()
{
    changeOfSettings = true;
    setX = ui->spinBox->value();
    setY = ui->spinBox_2->value();
    setWidth = ui->spinBox_3->value();
    close();
}

uint8_t Dialog::getX()
{
    return setX;
}

uint8_t Dialog::getY()
{
    return setY;
}

uint8_t Dialog::getWidth()
{
    return setWidth;
}

void Dialog::setLanguage(QString formTitle, QString groupText, QString labelCellInRow, QString labelCellInColumn, QString labelCellWidth, QString btnCancel, QString labelInfo, QString labelWindowSize)
{
    ui->label->setText(labelCellInRow);
    ui->label_2->setText(labelCellInColumn);
    ui->label_3->setText(labelCellWidth);
    ui->label_4->setText(labelInfo);
    ui->label_5->setText(labelWindowSize);
    ui->pushButton_2->setText(btnCancel);
    setWindowTitle(formTitle);
    ui->groupBox->setTitle(groupText);
}

void Dialog::on_pushButton_2_clicked()
{
    close();
}

bool Dialog::isChangeOfSettings()
{
    return changeOfSettings;
}

void Dialog::getScreenWidthHeight()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    screenHeight = screenGeometry.height();
    screenWidth = screenGeometry.width();
    qDebug() << screenWidth << "  " << screenHeight;

}

void Dialog::recalculateTheApplicationSize()
{   
    applicationSizeWidth = ui->spinBox->value() * ui->spinBox_3->value();
    applicationSizeHeight = ui->spinBox_2->value() * ui->spinBox_3->value();
    ui->label_6->setText(QString::number(applicationSizeWidth) + "/" + QString::number(applicationSizeHeight));

    if (applicationSizeHeight > screenHeight || applicationSizeWidth > screenWidth)
    {
        ui->label_6->setStyleSheet("font-weight: bold; color: red");
        ui->label_5->setStyleSheet("font-weight: bold; color: red");
    }
    else
    {
        ui->label_6->setStyleSheet("font-weight: normal; color: black");
        ui->label_5->setStyleSheet("font-weight: normal; color: black");
    }
}

void Dialog::on_spinBox_valueChanged(int arg1)
{
    recalculateTheApplicationSize();
}

void Dialog::on_spinBox_2_valueChanged(int arg1)
{
    recalculateTheApplicationSize();
}

void Dialog::on_spinBox_3_valueChanged(int arg1)
{
    recalculateTheApplicationSize();
}

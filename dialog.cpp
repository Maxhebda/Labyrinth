#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    setX = 10;
    setY = 10;
    setWidth=30;
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

void Dialog::setLanguage(QString formTitle, QString groupText, QString labelCellInRow, QString labelCellInColumn, QString labelCellWidth, QString btnCancel, QString labelInfo)
{
    ui->label->setText(labelCellInRow);
    ui->label_2->setText(labelCellInColumn);
    ui->label_3->setText(labelCellWidth);
    ui->label_4->setText(labelInfo);
    ui->pushButton_2->setText(btnCancel);
    setWindowTitle(formTitle);
    ui->groupBox->setTitle(groupText);
}

void Dialog::on_pushButton_2_clicked()
{
    close();
}

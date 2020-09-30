#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void setstart(uint8_t y, uint8_t x, uint8_t width);
    void setLanguage(QString formTitle, QString groupText, QString labelCellInRow, QString labelCellInColumn, QString labelCellWidth, QString btnCancel, QString labelInfo);
    uint8_t getX();
    uint8_t getY();
    uint8_t getWidth();
    Ui::Dialog *ui;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    uint8_t setY;
    uint8_t setX;
    uint8_t setWidth;
};

#endif // DIALOG_H

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
    void setLanguage(QString formTitle, QString groupText, QString labelCellInRow, QString labelCellInColumn, QString labelCellWidth, QString btnCancel, QString labelInfo, QString labelWindowSize);
    uint8_t getX();
    uint8_t getY();
    uint8_t getWidth();
    bool isChangeOfSettings();  // true if you clicked OK (save settings)

    //--- screen size
    uint16_t screenWidth;
    uint16_t screenHeight;

    //--- application size
    uint16_t applicationSizeWidth;
    uint16_t applicationSizeHeight;

    bool changeOfSettings;
    Ui::Dialog *ui;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

private:
    uint8_t setY;
    uint8_t setX;
    uint8_t setWidth;
    void getScreenWidthHeight();
    void recalculateTheApplicationSize();
};

#endif // DIALOG_H

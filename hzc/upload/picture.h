#pragma once
#include <opencv.hpp>
#include <QtWidgets/QWidget>
#include "ui_picture.h"
#include <qpushbutton.h>

class picture : public QWidget
{
    Q_OBJECT
       
public:
    picture(QWidget* parent = nullptr);
    ~picture();
    QPushButton* btn1;
    QPushButton* btn2;
public slots:
    /*Mat importPic();*/
    void startAdjust(int, char**);//用于压缩
signals:
    void sigClicked();//信号函数链接
private:
    Ui::pictureClass ui;
};



#include "widget.h"
#include "ui_widget.h"
#include<qtmaterialtoggle.h>
#include<qtmaterialflatbutton.h>
#include<qtmaterialflatbutton_internal.h>
#include<qtmaterialcircularprogress.h>
#include<qtmaterialcircularprogress_internal.h>
#include <qtmaterialraisedbutton.h>
#include <QColor>
using namespace Material;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Homework Test");


    //关闭恼人的特性
    ui->startCompression->setHaloVisible(false);
    ui->uploadPic->setHaloVisible(false);
    ui->function1->setHaloVisible(false);
    ui->function2->setHaloVisible(false);
    ui->function3->setHaloVisible(false);
    ui->function4->setHaloVisible(false);

    //修改颜色
    ui->startCompression->setBackgroundColor(QColor(0,128,128));
    ui->uploadPic->setBackgroundColor(QColor(0,128,128));
    ui->function1->setBackgroundColor(QColor(0,128,128));
    ui->function2->setBackgroundColor(QColor(0,128,128));
    ui->function3->setBackgroundColor(QColor(0,128,128));
    ui->function4->setBackgroundColor(QColor(0,128,128));

    //修改圆角半径
    ui->startCompression->setCornerRadius(5);
    ui->uploadPic->setCornerRadius(5);
    ui->function1->setCornerRadius(5);
    ui->function2->setCornerRadius(5);
    ui->function3->setCornerRadius(5);
    ui->function4->setCornerRadius(5);



    //拨动按钮
//    QtMaterialToggle *toggle=new QtMaterialToggle(this);
    //(x坐标,y坐标,长度,粗细)
//    toggle->setGeometry(30,30,100,50);

    //扁平按钮
//    QtMaterialRaisedButton *btn=new QtMaterialRaisedButton(this);
//    btn->setForegroundColor(QColor(0,198,231));
//    btn->setGeometry(100,100,250,40);
//    btn->setText("I am a flat button");
//    btn->applyPreset(Material::FlatPreset);
//    //设置字体
//    QFont font;
//    font.setFamily("Consolas");
//    font.setPixelSize(25);
//    btn->setFont(font);

    //加载动画
//    QtMaterialCircularProgress * circular = new QtMaterialCircularProgress(this);
//    circular->setColor(QColor::fromRgb(0,0,127));
//    circular->setGeometry(200,200,200,16);
}

Widget::~Widget()
{
    delete ui;
}

#include "widget.h"
#include "ui_widget.h"
#include<qtmaterialtoggle.h>
#include<qtmaterialflatbutton.h>
#include<qtmaterialflatbutton_internal.h>
#include<qtmaterialcircularprogress.h>
#include<qtmaterialcircularprogress_internal.h>
#include <qtmaterialraisedbutton.h>
#include <QColor>
#include <QFileDialog>
#include <QTextEdit>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include "Diag_and_Hori.h"
#include "IBR.h"
#include "STC.h"

//#include <./hzc/upload/Horizonal_Priority.cpp>
//#include <./hzc/upload/BigHeader.h>
//#include <./hzc/upload/IBR.cpp>

//using namespace std;
using namespace Material;

    //--------------------------------------------//
    //需要实现的特性：
    //1.未选择参数时弹窗提醒选择参数（图片、sigma、算法等）
    //2.处理完之后弹窗提醒
    //3.QtMaterialScrollBar实现控制台实时输出处理日志
    //4.一点点彩蛋...?
    //--------------------------------------------//


//23.6.5 在ui展示了部分widget的实现效果
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Homework Test");


    //关闭恼人的特性
    ui->startCompression->setHaloVisible(false);
    ui->helpCenter->setHaloVisible(false);
    ui->clearLog->setHaloVisible(false);
    ui->saveImage->setHaloVisible(false);
    ui->selectPicture->setHaloVisible(false);


    //修改颜色
    ui->startCompression->setBackgroundColor(QColor(52, 92, 183));
    ui->helpCenter->setBackgroundColor(QColor(52, 92, 183));
    ui->clearLog->setBackgroundColor(QColor(52, 92, 183));
    ui->saveImage->setBackgroundColor(QColor(52, 92, 183));
    ui->selectPicture->setBackgroundColor(QColor(52, 92, 183));

    //修改圆角半径
    ui->startCompression->setCornerRadius(7);
    ui->helpCenter->setCornerRadius(7);
    ui->clearLog->setCornerRadius(7);
    ui->saveImage->setCornerRadius(7);
    ui->selectPicture->setCornerRadius(7);


    //其他的一些细节
    ui->selectPicture->setCursor(Qt::OpenHandCursor);
    ui->epsilon_label->setReadOnly(1);
    //ui->textOutput->setFocus(Qt::ActiveWindowFocusReason);



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

const char* argv1; //原图路径
const char* argv2; //输出灰度图像路径
const char* argv3; //输出处理后图像路径
const char* argv4; //episilon

//STC独有
const char* argv5; //同类快阀值
const char* argv6; //均值阀值
const char* argv7; //方差阀值
const char* argv8; //切法 1 水平 0垂直

QString selectedFilePath;

//选择图像，并处理（未实现选择算法功能）
void Widget::on_selectPicture_clicked()
{
    //选择单个文件
    QString curPath=QDir::currentPath();//获取系统当前目录
    //获取应用程序的路径
    QString dlgTitle="Select a file:"; //对话框标题
    QString filter="Image(*.jpg *.png *.bmp)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    const std::string argvName = aFileName.toStdString();
    selectedFilePath = aFileName;

    QPixmap pixmap(selectedFilePath);
    pixmap = pixmap.scaled(381, 421, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(pixmap);
    ui->label->show();

    //参数，需要改进
    argv2 = "gray.bmp";
    argv3 = "decoded.bmp";
    argv4 = "30";

    argv5 = "30";
    argv6 = "30";
    argv7 = "30";
    argv8 = "1";

    //diag_main(argv1,argv2,argv3,argv4);
    //hori_main(argv1,argv2,argv3,argv4);


    if (!aFileName.isEmpty())
    {
        ui->textBrowser->append("SELECTED IMAGE");
        ui->textBrowser->append(aFileName);


//        ui->textBrowser->append("-----START PROCESSING-----");

//        for(int i=0;i<100;i++)
//            ui->textBrowser->append("-----START PROCESSING-----");
//        ui->textBrowser->append("File Direction:");
//        ui->textBrowser->append(aFileName);

//        //这里输出参数等信息
//        ui->textBrowser->append("------END PROCESSING------");

    }
}


void Widget::on_startCompression_clicked()
{
    argv1 = selectedFilePath.toStdString().c_str();

    if(ui->algorithm_tnam_diagonal->isChecked() == true)
        diag_main(argv1,argv2,argv3,argv4);
    if(ui->algorithm_tnam_horizonal->isChecked() == true)
        hori_main(argv1,argv2,argv3,argv4);
    if(ui->algorithm_ibr->isChecked() == true)
        ibr_main(argv1,argv2,argv3,argv4);
    if(ui->algorithm_stc->isChecked() == true)
        stc_main(argv1,argv2,argv3,argv5,argv6,argv7,argv8);




    ui->textBrowser->append("-----START PROCESSING-----");

    //ui->textBrowser->append(temp);
    ui->textBrowser->append(argv2);
    ui->textBrowser->append(argv3);
    ui->textBrowser->append(argv4);


    QPixmap pixmap("./decoded.bmp");
    pixmap = pixmap.scaled(381, 421, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(pixmap);
    ui->label_2->show();

}



void Widget::on_algorithm_tnam_diagonal_clicked()
{
    ui->algorithm_tnam_diagonal->setChecked(true);
    ui->algorithm_tnam_horizonal->setChecked(false);
    ui->algorithm_stc->setChecked(false);
    ui->algorithm_ibr->setChecked(false);
}


void Widget::on_algorithm_tnam_horizonal_clicked()
{
    ui->algorithm_tnam_diagonal->setChecked(false);
    ui->algorithm_tnam_horizonal->setChecked(true);
    ui->algorithm_stc->setChecked(false);
    ui->algorithm_ibr->setChecked(false);}


void Widget::on_algorithm_stc_clicked()
{
    ui->algorithm_tnam_diagonal->setChecked(false);
    ui->algorithm_tnam_horizonal->setChecked(false);
    ui->algorithm_stc->setChecked(true);
    ui->algorithm_ibr->setChecked(false);}


void Widget::on_algorithm_ibr_clicked()
{
    ui->algorithm_tnam_diagonal->setChecked(false);
    ui->algorithm_tnam_horizonal->setChecked(false);
    ui->algorithm_stc->setChecked(false);
    ui->algorithm_ibr->setChecked(true);}


void Widget::on_epsilon_slider_valueChanged(int value)
{
    QString s = QString::number(value,10);
    ui->epsilon_label->setText(s);
}


void Widget::on_fast_threshold_slider_valueChanged(int value)
{
    QString s = QString::number(value,10);
    ui->fast_threshold_label->setText(s);
}


void Widget::on_mean_value_slider_valueChanged(int value)
{
    QString s = QString::number(value,10);
    ui->mean_value_label->setText(s);
}


void Widget::on_variance_slider_valueChanged(int value)
{
    QString s = QString::number(value,10);
    ui->variance_label->setText(s);
}


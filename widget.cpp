#include "main_algorithm.h"
#include "widget.h"
#include "qboxlayout.h"
#include "ui_widget.h"
#include <qtmaterialtoggle.h>
#include <qtmaterialflatbutton.h>
#include <qtmaterialflatbutton_internal.h>
#include <qtmaterialcircularprogress.h>
#include <qtmaterialcircularprogress_internal.h>
#include <qtmaterialraisedbutton.h>
#include <QColor>
#include <QFileDialog>
#include <QTextEdit>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <QButtonGroup>
using namespace Material;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Image Segmentation Tool v1.0.0");

    //关闭恼人的特性
    {
        ui->startCompression->setHaloVisible(false);
        ui->helpCenter->setHaloVisible(false);
        ui->clearLog->setHaloVisible(false);
        ui->saveImage->setHaloVisible(false);
        ui->selectPicture->setHaloVisible(false);
    }

    //修改颜色
    {
    ui->startCompression->setBackgroundColor(QColor(12, 99, 67));
    ui->helpCenter->setBackgroundColor(QColor(12, 99, 67));
    ui->clearLog->setBackgroundColor(QColor(12, 99, 67));
    ui->saveImage->setBackgroundColor(QColor(12, 99, 67));
    ui->selectPicture->setBackgroundColor(QColor(12, 99, 67));

    ui->algorithm_tnam_diagonal->setCheckedColor(QColor(12, 99, 67));
    ui->algorithm_tnam_horizonal->setCheckedColor(QColor(12, 99, 67));
    ui->algorithm_ibr->setCheckedColor(QColor(12, 99, 67));
    ui->algorithm_stc_vertical->setCheckedColor(QColor(12, 99, 67));
    ui->algorithm_only_to_gray->setCheckedColor(QColor(12, 99, 67));
    ui->algorithm_stc_horizonal->setCheckedColor(QColor(12, 99, 67));
    ui->algorithm_tnam_horizonal->setCheckedColor(QColor(12, 99, 67));
    ui->algorithm_tnam_diagonal->setCheckedColor(QColor(12, 99, 67));
    ui->algorithm_ibr->setCheckedColor(QColor(12, 99, 67));

    ui->epsilon_slider->setThumbColor(QColor(12, 99, 67));//左边轨道的颜色
    ui->epsilon_slider->setDisabledColor(QColor(12, 99, 67));
    ui->epsilon_slider->setTrackColor(QColor(12, 99, 67));

    ui->mean_value_slider->setThumbColor(QColor(12, 99, 67));
    ui->mean_value_slider->setDisabledColor(QColor(12, 99, 67));
    ui->mean_value_slider->setTrackColor(QColor(12, 99, 67));

    ui->variance_slider->setThumbColor(QColor(12, 99, 67));
    ui->variance_slider->setDisabledColor(QColor(12, 99, 67));
    ui->variance_slider->setTrackColor(QColor(12, 99, 67));
    }

    //修改圆角半径
    {
    ui->startCompression->setCornerRadius(7);
    ui->helpCenter->setCornerRadius(7);
    ui->clearLog->setCornerRadius(7);
    ui->saveImage->setCornerRadius(7);
    ui->selectPicture->setCornerRadius(7);
    }

    //其他的一些细节
    {
    //ui->selectPicture->setCursor(Qt::OpenHandCursor);
    ui->epsilon_label->setReadOnly(1);
    ui->mean_value_label->setReadOnly(1);
    ui->variance_label->setReadOnly(1);
    }

    //设置按钮组
    {
    QButtonGroup * BtnGroupA = new QButtonGroup;
    BtnGroupA->addButton(ui->algorithm_ibr);
    BtnGroupA->addButton(ui->algorithm_stc_vertical);
    BtnGroupA->addButton(ui->algorithm_stc_horizonal);
    BtnGroupA->addButton(ui->algorithm_tnam_diagonal);
    BtnGroupA->addButton(ui->algorithm_tnam_horizonal);
    BtnGroupA->addButton(ui->algorithm_only_to_gray);
    }

}

Widget::~Widget()
{
    delete ui;
}




//输入参数表
const char* argv2 = "gray_image.bmp"; //输出灰度图像路径
const char* argv3 = "decoded_image.bmp"; //输出处理后图像路径
QString selectedFilePath; //原图路径
QString epsilon; //epsilon
QString mean_value; //均值阀值
QString variance; //方差阀值
QString cutmethod; //切法 1 水平 0垂直

//输出参数表
long compression_time;//编码时间
long decode_time;//解码时间
unsigned long long blocks;//块数
double psnr_value;//psnr值
double bpp_value;//bpp值
double cr_value;//cr值
long long qsc_time;//qsc处理时间
int region_nums; //区域数量

//处理参数
const char* qstringToConstChar(const QString& qstr)
{
    QByteArray byteArray = qstr.toUtf8(); // 或者使用 toLatin1()
    char* cstr = new char[byteArray.size() + 1];
    std::strcpy(cstr, byteArray.constData());
    return cstr;
}

//选择图像
void Widget::on_selectPicture_clicked()
{
    //获取图片的路径
    QString curPath=QDir::currentPath();//获取系统当前目录
    QString dlgTitle="Select a file:"; //对话框标题
    QString filter="Image(*.jpg *.png *.bmp)"; //文件过滤器
    QString tempPath = QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(tempPath.isNull() != 1 )
    selectedFilePath = tempPath;

    //图片显示到UI上
    QPixmap pixmap(selectedFilePath);
    if(pixmap.isNull()!=1)
    {
    pixmap = pixmap.scaled(450, 450, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(pixmap);
    ui->label->show();
    }

    //控制台输出
    if (!selectedFilePath.isEmpty())
    {
        //更改输出颜色
        ui->textBrowser->setTextColor(QColor(12, 99, 67));
        ui->textBrowser->append("-----------SELECT IMAGE-----------");
        ui->textBrowser->setTextColor(QColor(0,0,0));
        ui->textBrowser->append("IMAGE PATH:");
        ui->textBrowser->append(selectedFilePath);
    }
}

//保存图像
void Widget::on_saveImage_clicked()
{
    QString curPath=QDir::currentPath();//获取系统当前目录
    QString dlgTitle="File save to:"; //对话框标题
    QString filter="Image(*.bmp *.jpg *.png)"; //文件过滤器
    QString savePath;
    savePath = QFileDialog::getSaveFileName(this, dlgTitle, "", filter);
    if(savePath.isNull() != 1 )
    {
        if(ui->algorithm_only_to_gray->isChecked() == true)
        {
            QFile::copy("./gray_image.bmp", savePath);

        }
        else
        {
            QFile::copy("./decoded_image.bmp", savePath);

        }
        ui->textBrowser->setTextColor(QColor(12, 99, 67));
        ui->textBrowser->append("------------SAVE IMAGE------------");
        ui->textBrowser->setTextColor(QColor(0,0,0));    ui->textBrowser->append("SAVED IMAGE TO:");
        ui->textBrowser->append(savePath);
        ui->textBrowser->setTextColor(QColor(12, 99, 67));
        ui->textBrowser->append("----------------------------------");
        ui->textBrowser->setTextColor(QColor(0,0,0));
        ui->textBrowser->append("                           ");
    }
}

//传递参数并开始压缩
void Widget::on_startCompression_clicked()
{
    main_algorithm mainAlgorithm;
    const char* argv1 = qstringToConstChar(selectedFilePath);
    const char* argv4 = qstringToConstChar(epsilon);
    const char* argv5 = qstringToConstChar(mean_value);
    const char* argv6 = qstringToConstChar(variance);

    //显示参数
    ui->textBrowser->setTextColor(QColor(12, 99, 67));
    ui->textBrowser->append("----------SET PARAMETERS----------");
    ui->textBrowser->setTextColor(QColor(0,0,0));
    if(ui->algorithm_stc_horizonal->isChecked() == true)
    {
        ui->textBrowser->append("USE EPSILON:");
        ui->textBrowser->append(argv4);
        ui->textBrowser->append("Mean Value Threshold:");
        ui->textBrowser->append(argv5);
        ui->textBrowser->append("Variance Threshold:");
        ui->textBrowser->append(argv6);
        ui->textBrowser->append("Cutting Method:");
        ui->textBrowser->append("Horizonal");
        ui->textBrowser->append("SAVED GREY IMAGE TO:");
        ui->textBrowser->append("./gray_image.bmp");
        ui->textBrowser->append("SAVED DECODED IMAGE TO:");
        ui->textBrowser->append("./decoded_image.bmp");
        ui->textBrowser->append("SAVED SEGMENT IMAGE TO:");
        ui->textBrowser->append("./segment.bmp");
        ui->textBrowser->append("./segment_and_rebuild.bmp");
    }
    else if(ui->algorithm_stc_vertical->isChecked() == true)
    {
        ui->textBrowser->append("USE EPSILON:");
        ui->textBrowser->append(argv4);
        ui->textBrowser->append("Mean Value Threshold:");
        ui->textBrowser->append(argv5);
        ui->textBrowser->append("Variance Threshold:");
        ui->textBrowser->append(argv6);
        ui->textBrowser->append("Cutting Method:");
        ui->textBrowser->append("Vertical");
        ui->textBrowser->append("SAVED GREY IMAGE TO:");
        ui->textBrowser->append("./gray_image.bmp");
        ui->textBrowser->append("SAVED DECODED IMAGE TO:");
        ui->textBrowser->append("./decoded_image.bmp");
        ui->textBrowser->append("SAVED SEGMENT IMAGE TO:");
        ui->textBrowser->append("./segment.bmp");
        ui->textBrowser->append("./segment_and_rebuild.bmp");
    }
    else if(ui->algorithm_ibr->isChecked() == true || ui->algorithm_tnam_diagonal->isChecked() == true || ui->algorithm_tnam_horizonal->isChecked() == true)
    {
        ui->textBrowser->append("USE EPSILON:");
        ui->textBrowser->append(argv4);
        ui->textBrowser->append("SAVED GREY IMAGE TO:");
        ui->textBrowser->append("./gray_image.bmp");
        ui->textBrowser->append("SAVED DECODED IMAGE TO:");
        ui->textBrowser->append("./decoded_image.bmp");
        ui->textBrowser->append("SAVED SEGMENT IMAGE TO:");
        ui->textBrowser->append("./segment.bmp");
    }
    else if(ui->algorithm_only_to_gray->isChecked() == true)
    {
        ui->textBrowser->append("SAVED GREY IMAGE TO:");
        ui->textBrowser->append("./gray_image.bmp");
    }

    //开始处理
    if(ui->algorithm_only_to_gray->isChecked() == false)
    {
        ui->textBrowser->setTextColor(QColor(12, 99, 67));
        ui->textBrowser->append("----------PROCESS START----------");
        ui->textBrowser->setTextColor(QColor(0,0,0));
    }

    //选择处理算法
    if(ui->algorithm_tnam_diagonal->isChecked() == true)
        mainAlgorithm.diag_main(argv1,argv2,argv3,argv4);
    if(ui->algorithm_tnam_horizonal->isChecked() == true)
        mainAlgorithm.hori_main(argv1,argv2,argv3,argv4);
    if(ui->algorithm_ibr->isChecked() == true)
        mainAlgorithm.ibr_main(argv1,argv2,argv3,argv4);
    if(ui->algorithm_stc_vertical->isChecked() == true)
        mainAlgorithm.stc_main(argv1,argv2,argv3,argv4,argv5,argv6,"0");
    if(ui->algorithm_stc_horizonal->isChecked() == true)
        mainAlgorithm.stc_main(argv1,argv2,argv3,argv4,argv5,argv6,"1");
    if(ui->algorithm_only_to_gray->isChecked() == true)
    {
        //这里直接转换算了
        cv::Mat image = cv::imread(argv1);
        cv::Mat grayImage;
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
        // 保存灰度图像
        cv::imwrite("gray_image.bmp", grayImage);
    }

    //输出参数到日志
    if(ui->algorithm_stc_horizonal->isChecked() == true || ui->algorithm_stc_vertical->isChecked() == true)
    {
        //ui->textBrowser->append("Compression Time(ms):");
        //ui->textBrowser->append(QString::number(mainAlgorithm.compression_time));

        //ui->textBrowser->append("Decode Time(ms):");
        //ui->textBrowser->append(QString::number(mainAlgorithm.decode_time));
        ui->textBrowser->append("QSC Converge Time:");
        ui->textBrowser->append(QString::number(mainAlgorithm.qsc_time));

        ui->textBrowser->append("Blocks Used:");
        ui->textBrowser->append(QString::number(mainAlgorithm.blocks));

        ui->textBrowser->append("PSNR Value:");
        ui->textBrowser->append(QString::number(mainAlgorithm.psnr_value));

        ui->textBrowser->append("BPP Value:");
        ui->textBrowser->append(QString::number(mainAlgorithm.bpp_value));

        ui->textBrowser->append("CR Value:");
        ui->textBrowser->append(QString::number(mainAlgorithm.cr_value));

        ui->textBrowser->append("Number of Regions:");
        ui->textBrowser->append(QString::number(mainAlgorithm.region_nums));
    }
    else if(ui->algorithm_ibr->isChecked() == true || ui->algorithm_tnam_diagonal->isChecked() == true || ui->algorithm_tnam_horizonal->isChecked() == true)
    {
        ui->textBrowser->append("Compression Time(ms):");
        ui->textBrowser->append(QString::number(mainAlgorithm.compression_time));

        ui->textBrowser->append("Decode Time(ms):");
        ui->textBrowser->append(QString::number(mainAlgorithm.decode_time));
        ui->textBrowser->append("Blocks Used:");
        ui->textBrowser->append(QString::number(mainAlgorithm.blocks));

        ui->textBrowser->append("PSNR Value:");
        ui->textBrowser->append(QString::number(mainAlgorithm.psnr_value));

        ui->textBrowser->append("BPP Value:");
        ui->textBrowser->append(QString::number(mainAlgorithm.bpp_value));

        ui->textBrowser->append("CR Value:");
        ui->textBrowser->append(QString::number(mainAlgorithm.cr_value));
    }

    //重置参数
    delete[] argv1;
    delete[] argv4;
    delete[] argv5;
    delete[] argv6;

    //显示解码后图像
    QPixmap pixmap1("./gray_image.bmp");
    QPixmap pixmap2("./decoded_image.bmp");

    if(ui->algorithm_only_to_gray->isChecked() == true)
    {
        pixmap1 = pixmap1.scaled(450, 450, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pixmap1);
        ui->label_2->show();
    }
    else
    {
        pixmap2 = pixmap2.scaled(450, 450, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pixmap2);
        ui->label_2->show();
    }
    ui->textBrowser->setTextColor(QColor(12, 99, 67));
    ui->textBrowser->append("-----------PROCESS END------------");
    ui->textBrowser->append("                                  ");
    ui->textBrowser->setTextColor(QColor(0,0,0));

}


void Widget::on_algorithm_only_to_gray_clicked()
{
    ui->algorithm_only_to_gray->setChecked(true);
    ui->algorithm_tnam_diagonal->setChecked(false);
    ui->algorithm_tnam_horizonal->setChecked(false);
    ui->algorithm_stc_vertical->setChecked(false);
    ui->algorithm_stc_horizonal->setChecked(false);
    ui->algorithm_ibr->setChecked(false);
}


//按钮和滑块
void Widget::on_algorithm_tnam_diagonal_clicked()
{
    ui->algorithm_only_to_gray->setChecked(false);
    ui->algorithm_tnam_diagonal->setChecked(true);
    ui->algorithm_tnam_horizonal->setChecked(false);
    ui->algorithm_stc_vertical->setChecked(false);
    ui->algorithm_stc_horizonal->setChecked(false);
    ui->algorithm_ibr->setChecked(false);
}

void Widget::on_algorithm_tnam_horizonal_clicked()
{
    ui->algorithm_only_to_gray->setChecked(false);
    ui->algorithm_tnam_diagonal->setChecked(false);
    ui->algorithm_tnam_horizonal->setChecked(true);
    ui->algorithm_stc_vertical->setChecked(false);
    ui->algorithm_stc_horizonal->setChecked(false);
    ui->algorithm_ibr->setChecked(false);}

void Widget::on_algorithm_stc_vertical_clicked()
{
    ui->algorithm_only_to_gray->setChecked(false);
    ui->algorithm_tnam_diagonal->setChecked(false);
    ui->algorithm_tnam_horizonal->setChecked(false);
    ui->algorithm_stc_vertical->setChecked(true);
    ui->algorithm_stc_horizonal->setChecked(false);
    ui->algorithm_ibr->setChecked(false);
}

void Widget::on_algorithm_stc_horizonal_clicked()
{
    ui->algorithm_only_to_gray->setChecked(false);
    ui->algorithm_tnam_diagonal->setChecked(false);
    ui->algorithm_tnam_horizonal->setChecked(false);
    ui->algorithm_stc_vertical->setChecked(false);
    ui->algorithm_stc_horizonal->setChecked(true);
    ui->algorithm_ibr->setChecked(false);
}

void Widget::on_algorithm_ibr_clicked()
{
    ui->algorithm_only_to_gray->setChecked(false);
    ui->algorithm_tnam_diagonal->setChecked(false);
    ui->algorithm_tnam_horizonal->setChecked(false);
    ui->algorithm_stc_vertical->setChecked(false);
    ui->algorithm_stc_horizonal->setChecked(false);
    ui->algorithm_ibr->setChecked(true);}

//滑块
void Widget::on_epsilon_slider_valueChanged(int value)
{
    double val=double(value)/10;
    epsilon = QString::number(val, 'f', 1);
    ui->epsilon_label->setText(epsilon);

}

void Widget::on_mean_value_slider_valueChanged(int value)
{
    double val=double(value)/10;
    mean_value = QString::number(val, 'f', 1);
    ui->mean_value_label->setText(mean_value);
}

void Widget::on_variance_slider_valueChanged(int value)
{
    double val=double(value)/10;
    variance = QString::number(val, 'f', 1);
    ui->variance_label->setText(variance);
}

//清空日志
void Widget::on_clearLog_released()
{
    ui->textBrowser->clear();
}

//帮助按钮
void Widget::on_helpCenter_clicked()
{

    QDialog *dialog = new QDialog;
    {
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setWindowTitle("About");
        dialog->setFixedWidth(800);
        dialog->setFixedHeight(600);
        dialog->setMaximumWidth(800);
        dialog->setMaximumHeight(600);
        dialog->setMinimumWidth(800);
        dialog->setMinimumHeight(600);
    }

    QLabel *label = new QLabel(dialog);
    label->setAlignment(Qt::AlignCenter);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QFont font("微软雅黑", 12);
    label->setFont(font);
    label->setWordWrap(false);
    label->setTextFormat(Qt::RichText);
    QString labelText = "===================说明===================<br>"
                        "最后编辑于2023/6/11<br>"
                        "这是一个图像转换程序，实现了：<br>"
                        "1. RNAM垂直/水平分割算法<br>"
                        "2. IBR分割算法<br>"
                        "3. STC垂直/水平分割算法 <br>"
                        "RNAM/IBR/STC算法使用epsilon(ε)作为误差容许量，STC算法使用 <br>"
                        "epsilon(ε)和均值阈值、方差阈值来调整分割质量 <br>"
                        "可以用按钮选择需要的算法，用滑块来调整epsilon(ε)以及<br>"
                        "均值阈值、方差阈值，范围为[0,50]<br>"
                        "软件上方显示原图和处理后的图像，右边为日志输出窗口，展示输入 <br>"
                        "和输出的参数<br>"
                        "===================关于===================<br>"
                        "Made by: 汤骏哲、黄泽川、彭兆屹、郑楚豪、徐镜涵<br>"
                        "GitHub仓库: <a href='https://github.com/HIBIKl/CPP_Homework'>https://github.com/HIBIKl/CPP_Homework</a><br>"
                        "===================鸣谢===================<br>"
                        "软件使用 qt-material-widgets 组件库：<br>"
                        "<a href='https://github.com/laserpants/qt-material-widgets'>https://github.com/laserpants/qt-material-widgets</a>";
    label->setText(labelText);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setOpenExternalLinks(true);
    label->setAlignment(Qt::AlignLeft);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(label);
    dialog->setLayout(layout);

    dialog->show();
}


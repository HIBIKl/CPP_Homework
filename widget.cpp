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
    //��Ҫʵ�ֵ����ԣ�
    //1.δѡ�����ʱ��������ѡ�������ͼƬ��sigma���㷨�ȣ�
    //2.������֮�󵯴�����
    //3.QtMaterialScrollBarʵ�ֿ���̨ʵʱ���������־
    //4.һ���ʵ�...?
    //--------------------------------------------//


//23.6.5 ��uiչʾ�˲���widget��ʵ��Ч��
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Homework Test");


    //�ر����˵�����
    ui->startCompression->setHaloVisible(false);
    ui->helpCenter->setHaloVisible(false);
    ui->clearLog->setHaloVisible(false);
    ui->saveImage->setHaloVisible(false);
    ui->selectPicture->setHaloVisible(false);


    //�޸���ɫ
    ui->startCompression->setBackgroundColor(QColor(52, 92, 183));
    ui->helpCenter->setBackgroundColor(QColor(52, 92, 183));
    ui->clearLog->setBackgroundColor(QColor(52, 92, 183));
    ui->saveImage->setBackgroundColor(QColor(52, 92, 183));
    ui->selectPicture->setBackgroundColor(QColor(52, 92, 183));

    //�޸�Բ�ǰ뾶
    ui->startCompression->setCornerRadius(7);
    ui->helpCenter->setCornerRadius(7);
    ui->clearLog->setCornerRadius(7);
    ui->saveImage->setCornerRadius(7);
    ui->selectPicture->setCornerRadius(7);


    //������һЩϸ��
    ui->selectPicture->setCursor(Qt::OpenHandCursor);
    ui->epsilon_label->setReadOnly(1);
    //ui->textOutput->setFocus(Qt::ActiveWindowFocusReason);



//������ť
//    QtMaterialToggle *toggle=new QtMaterialToggle(this);
//(x����,y����,����,��ϸ)
//    toggle->setGeometry(30,30,100,50);
//��ƽ��ť
//    QtMaterialRaisedButton *btn=new QtMaterialRaisedButton(this);
//    btn->setForegroundColor(QColor(0,198,231));
//    btn->setGeometry(100,100,250,40);
//    btn->setText("I am a flat button");
//    btn->applyPreset(Material::FlatPreset);
//    //��������
//    QFont font;
//    font.setFamily("Consolas");
//    font.setPixelSize(25);
//    btn->setFont(font);
//���ض���
//    QtMaterialCircularProgress * circular = new QtMaterialCircularProgress(this);
//    circular->setColor(QColor::fromRgb(0,0,127));
//    circular->setGeometry(200,200,200,16);
}

Widget::~Widget()
{
    delete ui;
}

const char* argv1; //ԭͼ·��
const char* argv2; //����Ҷ�ͼ��·��
const char* argv3; //��������ͼ��·��
const char* argv4; //episilon

//STC����
const char* argv5; //ͬ��췧ֵ
const char* argv6; //��ֵ��ֵ
const char* argv7; //���ֵ
const char* argv8; //�з� 1 ˮƽ 0��ֱ

QString selectedFilePath;

//ѡ��ͼ�񣬲�����δʵ��ѡ���㷨���ܣ�
void Widget::on_selectPicture_clicked()
{
    //ѡ�񵥸��ļ�
    QString curPath=QDir::currentPath();//��ȡϵͳ��ǰĿ¼
    //��ȡӦ�ó����·��
    QString dlgTitle="Select a file:"; //�Ի������
    QString filter="Image(*.jpg *.png *.bmp)"; //�ļ�������
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    const std::string argvName = aFileName.toStdString();
    selectedFilePath = aFileName;

    QPixmap pixmap(selectedFilePath);
    pixmap = pixmap.scaled(381, 421, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(pixmap);
    ui->label->show();

    //��������Ҫ�Ľ�
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

//        //���������������Ϣ
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


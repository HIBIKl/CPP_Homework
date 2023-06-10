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
    //ui->uploadPic->setHaloVisible(false);
    //ui->function1->setHaloVisible(false);
    //ui->function2->setHaloVisible(false);
    //ui->function3->setHaloVisible(false);
    ui->function4->setHaloVisible(false);
    ui->selectPicture->setHaloVisible(false);

    //�޸���ɫ
    ui->startCompression->setBackgroundColor(QColor(0,128,128));
    //ui->uploadPic->setBackgroundColor(QColor(0,128,128));
    //ui->function1->setBackgroundColor(QColor(0,128,128));
    //ui->function2->setBackgroundColor(QColor(0,128,128));
    //ui->function3->setBackgroundColor(QColor(0,128,128));
    ui->function4->setBackgroundColor(QColor(0,128,128));
    ui->selectPicture->setBackgroundColor(QColor(0,128,128));

    //�޸�Բ�ǰ뾶
    ui->startCompression->setCornerRadius(5);
    //ui->uploadPic->setCornerRadius(5);
    //ui->function1->setCornerRadius(5);
    //ui->function2->setCornerRadius(5);
    //ui->function3->setCornerRadius(5);
    //ui->function4->setCornerRadius(5);

    //������һЩϸ��
    ui->selectPicture->setCursor(Qt::OpenHandCursor);
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

    //������������������������������������������������������������������������TEST������������������������������������������������//
    const char* argv1 = argvName.c_str();
    const char* argv2 = "gray.bmp";
    const char* argv3 = "decoded.bmp";
    const char* argv4 = "10";
    diag_main(argv1,argv2,argv3,argv4);
    //hori_main(argv1,argv2,argv3,argv4);\
    //������������������������������������������������������������������������TEST������������������������������������������������//

    if (!aFileName.isEmpty())
    {
        ui->textBrowser->append("-----START PROCESSING-----");
        ui->textBrowser->append("File Direction:");
        ui->textBrowser->append(aFileName);

        //���������������Ϣ
        ui->textBrowser->append("------END PROCESSING------");

    }
}


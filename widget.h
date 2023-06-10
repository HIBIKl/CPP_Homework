//#ifndef WIDGET_H
//#define WIDGET_H

//#include <QWidget>

//QT_BEGIN_NAMESPACE
//namespace Ui { class Widget; }
//QT_END_NAMESPACE

//class Widget : public QWidget
//{
//    Q_OBJECT

//public:
//    Widget(QWidget *parent = nullptr);
//    ~Widget();

//private:
//    Ui::Widget *ui;
//};
//#endif // WIDGET_H


#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_selectPicture_clicked();
    void on_startCompression_clicked();

    void on_algorithm_tnam_diagonal_clicked();


    void on_algorithm_tnam_horizonal_clicked();

    void on_algorithm_stc_clicked();

    void on_algorithm_ibr_clicked();


    void on_epsilon_slider_valueChanged(int value);

    void on_fast_threshold_slider_valueChanged(int value);

    void on_mean_value_slider_valueChanged(int value);

    void on_variance_slider_valueChanged(int value);

public slots:
    /*Mat importPic();*/
    //void startAdjustH(char**);//����ѹ��Horizonal
    //void startAdjustD(char**);//����ѹ��Diagonal
    //void startAdjustI(char**);//IBR
    //void startAdjustS(char**);//STC
signals:
    //void sigClicked();//�źź�������
    //void conTransport(int);//���ô���ʱ��������ĺ���
    
    //��ť��������ʹ��
    //connect(this->btn1, SIGNAL(QPushButton::clicked), this, SLOT(startAdjustH(char** argv)));

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

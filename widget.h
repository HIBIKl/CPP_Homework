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

    void on_algorithm_ibr_clicked();

    void on_algorithm_stc_vertical_clicked();

    void on_algorithm_stc_horizonal_clicked();

    void on_epsilon_slider_valueChanged(int value);

    void on_mean_value_slider_valueChanged(int value);

    void on_variance_slider_valueChanged(int value);

    void on_clearLog_released();

    void on_saveImage_clicked();

    void on_helpCenter_clicked();

public slots:

signals:


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

#include "picture.h"
#include "Header.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    picture w;
    w.show();
   
    return a.exec();

    /*Mat scr = imread("D:/lovely pic/6489669122.jpg");
    namedWindow("img", 0);
    imshow("img", scr);
    waitKey(0);
    destroyAllWindows();
    return 0;*/
}

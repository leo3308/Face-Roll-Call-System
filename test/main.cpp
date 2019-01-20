
#include "widget.h"
#include <QApplication>
#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

#include "face.h"


using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Widget ww;
    ww.show();
    //int value = FaceRecognition();
    return a.exec();
}

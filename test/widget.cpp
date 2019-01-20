#include "widget.h"
#include <QFormLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QValidator>
#include <string>
#include <iostream>
#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QLCDNumber>
#include <fstream>

//include opencv core
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"

using namespace std;
using namespace cv;
using namespace cv::face;

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    /*layout = new QGridLayout;
    for(int i=0 ; i< 18 ;i++){
        //QString a = QString::number(i);
        DepartmentBtn[i] = new QPushButton(this);
        DepartmentBtn[i]->setText(department[i]);
        connect(DepartmentBtn[i], SIGNAL(released()),this, SLOT(Dep_Btn_click()));
    }
    //connect(DepartmentBtn[1], SIGNAL(released()),this, SLOT(Dep_Btn_click()));
    for(int i=0; i<18;i++){
        layout->addWidget(DepartmentBtn[i],i/4,i%4);
        //layout->addWidget(DepartmentBtn[i],0,1);
    }
    setLayout(layout);
    this->adjustSize();
    setWindowTitle(tr("臺北大學點名系統"));*/
    //QString temp="";

    //temp = ((QPushButton*)sender())->text();
    //Dep_tmp = temp;
    //delete layout;
    //qDeleteAll(children());

    Dep_tmp = "資訊工程學系";
    QString num[4] = {"一","二","三","四"};

    for(int i=0 ; i< 4 ;i++){
        Grade[i] = new QPushButton(this);
        Grade[i]->setText(Dep_tmp+num[i]);
        //if(Dep_tmp == Dep){
            connect(Grade[i], SIGNAL(released()),this, SLOT(CS_grade_click()));
        //}
    }
    gradelayout = new QGridLayout;
    for(int i=0 ; i<4;i++ ){
        gradelayout->addWidget(Grade[i],0,i);
    }
    //backtoDep = new QPushButton(this);
    //backtoDep -> setText("Back to Department page");
    //connect(backtoDep, SIGNAL(released()),this, SLOT(back_click()));
    //gradelayout->addWidget(backtoDep,5,0);
    setLayout(gradelayout);
    //this->adjustSize();
    this->setFixedSize(550,200);
    BG_image.load("/Users/Leo/Desktop/Roll_Call_System/back_img.png");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(BG_image));
    this->setPalette(palette);
    //this->setAutoFillBackground(true);
    setWindowTitle(Dep_tmp);
}
void Widget :: Dep_Btn_click()
{
    QString temp="";
    QString Dep = "資訊工程學系";
    temp = ((QPushButton*)sender())->text();
    Dep_tmp = temp;
    delete layout;
    qDeleteAll(children());
    QString num[4] = {"一","二","三","四"};

    for(int i=0 ; i< 4 ;i++){
        Grade[i] = new QPushButton(this);
        Grade[i]->setText(temp+num[i]);
        if(Dep_tmp == Dep){
            connect(Grade[i], SIGNAL(released()),this, SLOT(CS_grade_click()));
        }
    }
    gradelayout = new QGridLayout;
    for(int i=0 ; i<4;i++ ){
        gradelayout->addWidget(Grade[i],0,i);
    }
    //backtoDep = new QPushButton(this);
    //backtoDep -> setText("Back to Department page");
    //connect(backtoDep, SIGNAL(released()),this, SLOT(back_click()));
    //gradelayout->addWidget(backtoDep,5,0);
    setLayout(gradelayout);
    this->adjustSize();
    setWindowTitle(temp);
}
void Widget :: back_click()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    if( b == backtoDep){
        delete gradelayout;
        qDeleteAll (children());
        layout = new QGridLayout;
        for(int i=0 ; i< 18 ;i++){
            //QString a = QString::number(i);
            DepartmentBtn[i] = new QPushButton(this);
            DepartmentBtn[i]->setText(department[i]);
            connect(DepartmentBtn[i], SIGNAL(released()),this, SLOT(Dep_Btn_click()));
        }
        for(int i=0; i<18;i++){
            layout->addWidget(DepartmentBtn[i],i/4,i%4);
            //layout->addWidget(DepartmentBtn[i],0,1);
        }
        setLayout(layout);
        setWindowTitle(tr("臺北大學點名系統"));
    }
    else if( b == backtoGrade || b == cancel){
        //delete cs_course_layout;
        destroyAllWindows();
        qDeleteAll(children());
        QString num[4] = {"一","二","三","四"};

        for(int i=0 ; i< 4 ;i++){
            Grade[i] = new QPushButton(this);
            Grade[i]->setText(Dep_tmp+num[i]);
            connect(Grade[i], SIGNAL(released()),this, SLOT(CS_grade_click()));
        }
        gradelayout = new QGridLayout;
        for(int i=0 ; i<4;i++ ){
            gradelayout->addWidget(Grade[i],0,i);
        }
        //backtoDep = new QPushButton(this);
        //backtoDep -> setText("Back to Department page");
        //connect(backtoDep, SIGNAL(released()),this, SLOT(back_click()));
        //gradelayout->addWidget(backtoDep,5,0);
        setLayout(gradelayout);
        this->setFixedSize(550,200);
        BG_image.load("/Users/Leo/Desktop/Roll_Call_System/back_img.png");
        QPalette palette;
        palette.setBrush(this->backgroundRole(),QBrush(BG_image));
        this->setPalette(palette);
        setWindowTitle(Dep_tmp);
    }
}
void Widget::CS_grade_click()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    QString temp = b->text();
    //delete gradelayout;
    qDeleteAll (children());
    cs_course_layout = new QGridLayout;
    if(b == Grade[0]){
        for(int i=0;i<6;i++){
            cs_course_btn[i] = new QPushButton(this);
            cs_course_btn[i] -> setText(CS_course1[i]);
            cs_course_layout -> addWidget(cs_course_btn[i],i/4,i%4);
            connect(cs_course_btn[i], SIGNAL(released()),this, SLOT(cs_course_click()));
        }
    }
    else if(b == Grade[1]){
        for(int i=0;i<6;i++){
            cs_course_btn[i] = new QPushButton(this);
            cs_course_btn[i] -> setText(CS_course2[i]);
            cs_course_layout -> addWidget(cs_course_btn[i],i/4,i%4);
            connect(cs_course_btn[i], SIGNAL(released()),this, SLOT(cs_course_click()));
        }
    }
    else if(b == Grade[2]){
        for(int i=0;i<12;i++){
            cs_course_btn[i] = new QPushButton(this);
            cs_course_btn[i] -> setText(CS_course3[i]);
            cs_course_layout -> addWidget(cs_course_btn[i],i/4,i%4);
            connect(cs_course_btn[i], SIGNAL(released()),this, SLOT(cs_course_click()));
        }
    }
    else {
        for(int i=0;i<4;i++){
            cs_course_btn[i] = new QPushButton(this);
            cs_course_btn[i] -> setText(CS_course4[i]);
            cs_course_layout -> addWidget(cs_course_btn[i],i/4,i%4);
            connect(cs_course_btn[i], SIGNAL(released()),this, SLOT(cs_course_click()));
        }
    }

    backtoGrade = new QPushButton(this);
    backtoGrade -> setText("上一頁");
    connect(backtoGrade, SIGNAL(released()),this, SLOT(back_click()));
    cs_course_layout->addWidget(backtoGrade,5,0);
    setLayout(cs_course_layout);
    this->adjustSize();
    setWindowTitle(temp+tr("課程"));
}
void Widget::cs_course_click()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    cour_tmp = b->text();

    char filename[]="/Users/Leo/Desktop/Roll_Call_System/LogIn.txt";
    fstream fp;
    fp.open(filename, ios::out);//開啟檔案
    fp << cour_tmp.toStdString() << endl;
    fp.close();

    qDeleteAll(children());
    text= new QLabel(tr("學生編號:"));
    num = new QLineEdit(this);
    num->setMaximumWidth(100);
    QValidator *validator = new QIntValidator(0,500000000,this);
    num -> setValidator(validator);
    exm = new QLabel(tr("（範例）"));
    ans = new QLabel(tr("410385033"));
    submit = new QPushButton(this);
    submit->setText("確認");
    connect(submit, SIGNAL(clicked()),this, SLOT(FaceRecognition2()));
    cancel = new QPushButton(this);
    cancel->setText("取消");
    connect(cancel, SIGNAL(released()),this, SLOT(back_click()));
    final = new QGridLayout;
    final->addWidget(text,0,0);
    final->addWidget(num,0,1);
    final->addWidget(exm,1,0);
    final->addWidget(ans,1,1);
    final->addWidget(submit,2,0);
    final->addWidget(cancel,2,1);
    setLayout(final);
    this->setFixedSize(200,200);
    BG_image.load("/Users/Leo/Desktop/Roll_Call_System/back_img2.png");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(BG_image));
    this->setPalette(palette);
    //this->adjustSize();
    setWindowTitle(cour_tmp);
}
void Widget::submit_click()
{
    QString content = num -> text();
    FaceRecognition2();
    cout << "why you crash" << endl;
}
void Widget::FaceRecognition2(){

    QString content = num -> text();
    qDeleteAll(children());
    text= new QLabel(tr("學生編號:"));
    num = new QLineEdit(this);
    QValidator *validator = new QIntValidator(0,500000000,this);
    num -> setValidator(validator);
    exm = new QLabel(tr("（範例）"));
    ans = new QLabel(tr("410385033"));
    submit = new QPushButton(this);
    submit->setText("確認");
    connect(submit, SIGNAL(clicked()),this, SLOT(FaceRecognition2()));
    cancel = new QPushButton(this);
    cancel->setText("取消");
    connect(cancel, SIGNAL(released()),this, SLOT(back_click()));

    final = new QGridLayout;
    final->addWidget(text,0,0);
    final->addWidget(num,0,1);
    final->addWidget(exm,1,0);
    final->addWidget(ans,1,1);
    final->addWidget(submit,2,0);
    final->addWidget(cancel,2,1);
    setLayout(final);
    this->setFixedSize(200,200);
    setWindowTitle(cour_tmp);
    QCoreApplication::processEvents();
    int leo_count = 0;

    cout << "start recognizing..." << endl;

    //load pre-trained data sets
    Ptr<BasicFaceRecognizer>  model = createFisherFaceRecognizer();
    model->load("/Users/Leo/Desktop/opencv_test/sideface.yml");


    Mat testSample = imread("/Users/Leo/Desktop/opencv_test/we_faces/s1/4.jpg", 0);

    int img_width = testSample.cols;
    int img_height = testSample.rows;


    //lbpcascades/lbpcascade_frontalface.xml
    string classifier = "/usr/local/Cellar/opencv3/3.2.0/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";

    CascadeClassifier face_cascade;
    string window = "Capture - face detection";

    if (!face_cascade.load(classifier)){
        cout << " Error loading file" << endl;
        //return -1;
    }

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "exit" << endl;
        //return -1;
    }

    //double fps = cap.get(CV_CAP_PROP_FPS);
    //cout << " Frames per seconds " << fps << endl;
    namedWindow(window, 1);
    int count = 0;
    int label = -1; double confidence = 0;

    while (1)
    {
        vector<Rect> faces;
        Mat frame;
        Mat graySacleFrame;
        Mat original;

        cap >> frame;
        //cap.read(frame);
        count = count + 1;//count frames;

        if (!frame.empty()){

            //clone from original frame
            original = frame;

            //convert image to gray scale and equalize
            cvtColor(original, graySacleFrame, CV_BGR2GRAY);
            //equalizeHist(graySacleFrame, graySacleFrame);

            //detect face in gray image
            face_cascade.detectMultiScale(graySacleFrame, faces, 1.1, 3, 0, cv::Size(90, 90));

            //number of faces detected
            cout << faces.size() << " faces detected" << endl;
            std::string frameset = std::to_string(count);
            std::string faceset = std::to_string(faces.size());

            //region of interest
            //cv::Rect roi;

            //person name
            string Pname = "";

            string confi="";
            for (int i = 0; i < faces.size(); i++)
            {
                //region of interest
                Rect face_i = faces[i];

                //crop the roi from grya image
                Mat face = graySacleFrame(face_i);

                //resizing the cropped image to suit to database image sizes
                Mat face_resized;
                cv::resize(face, face_resized, Size(img_width, img_height), 1.0, 1.0, INTER_CUBIC);

                //recognizing what faces detected
                //int label = -1; double confidence = 0;
                model->predict(face_resized, label, confidence);

                confi = to_string(confidence);

                cout << " confidence " << confidence << endl;

                //drawing green rectagle in recognize face
                rectangle(original, face_i, CV_RGB(0, 255, 0), 1);
                string text = "Detected";

                if(label == 410385043){
                    Pname = "4how pig";
                }
                else if(label == 410385033){
                    Pname = "leo pig";
                    leo_count++;
                }
                else if( label == 410385022){
                    Pname = "wanting pig";
                }
                else if (label == 410385041){
                    Pname = "shuan pig";
                }
                else{
                    Pname = "unknown";
                }
                int pos_x = std::max(face_i.tl().x - 10, 0);
                int pos_y = std::max(face_i.tl().y - 10, 0);

                //name the person who is in the image
                putText(original, text, Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
                //cv::imwrite("E:/FDB/"+frameset+".jpg", cropImg);

            }


            putText(original, "Frames: " + frameset, Point(30, 60), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
            putText(original, "Person: " + Pname, Point(30, 90), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
            //putText(original, "Confidence: " + confi, Point(30, 120), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
            //display to the window
            //stringstream ss;
            //ss << count;
            //string str = ss.str();
            //imwrite("/Users/Leo/Desktop/leo_face_pic/"+str+".jpg",original);
            /*QCoreApplication::processEvents();
            QImage imgIn = QImage((const unsigned char*) original.data, original.cols
                                  , original.rows, original.step , QImage::Format_RGB888).rgbSwapped();
            qDeleteAll(children());
            a = new QVBoxLayout;
            imgframe = new QLabel(this);
            imgframe -> setStyleSheet("background-color: #000");
            imgframe -> setGeometry(20,20,60,20);
            imgframe -> resize(1250,750);
            imgframe -> setMinimumSize(1250,750);
            imgframe->setAlignment(Qt::AlignCenter);
            imgframe->setPixmap(QPixmap::fromImage(imgIn).scaled(imgframe->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
            a->addWidget(imgframe);
            setLayout(a);*/

            //QCoreApplication::processEvents();
            cv::imshow(window, original);
            //cout << "model infor " << model->getDouble("threshold") << endl;

        }
        waitKey(100);
        //if (waitKey(100) >= 0) break;
        /*if(ans == label){
            QMessageBox::about(this,tr("測試訊框"),tr("Success"));
            //count = 200;
            //destroyWindow(window);
            break;
        }*/
        if(label == content.toInt()){
            double rate = (float)leo_count/count;
            rate *= 100;
            cout <<"rate : "<< rate<< "%" << endl;

            QTime time = QTime::currentTime();
            int seconds = second_to_hour(QTime(0, 0, 0).secsTo(time));
            char filename[]="/Users/Leo/Desktop/Roll_Call_System/LogIn.txt";
            fstream fp;
            fp.open(filename, ios::out|ios::app);//開啟檔案
            if(!fp){//如果開啟檔案失敗，fp為0；成功，fp為非0
                cout<<"Fail to open file: "<<filename<<endl;
            }
            cout<<"File Descriptor: "<<&fp<<endl;
            fp<<"Student ID : " << content.toInt() <<" ";
            fp<<"Login Time : "<<seconds/10000<<":"<<(seconds/100)%100<<":"<<seconds%100<<endl;//寫入字串
            fp.close();//關閉檔案

            imwrite("/Users/Leo/Desktop/Roll_Call_System/Login_image/"+content.toStdString()+".jpg",original);

            qDeleteAll(children());
            text= new QLabel(tr("學生編號:"));
            num = new QLineEdit(this);
            QValidator *validator = new QIntValidator(0,500000000,this);
            num -> setValidator(validator);
            exm = new QLabel(tr("（範例）"));
            ans = new QLabel(tr("410385033"));
            submit = new QPushButton(this);
            submit->setText("確認");
            connect(submit, SIGNAL(clicked()),this, SLOT(FaceRecognition2()));
            cancel = new QPushButton(this);
            cancel->setText("取消");
            connect(cancel, SIGNAL(released()),this, SLOT(back_click()));

            QLabel *student = new QLabel(content);
            QLabel *login = new QLabel(tr("Success"));
            final = new QGridLayout;
            final->addWidget(text,0,0);
            final->addWidget(num,0,1);
            final->addWidget(exm,1,0);
            final->addWidget(ans,1,1);
            final->addWidget(submit,2,0);
            final->addWidget(cancel,2,1);
            final->addWidget(student,3,0);
            final->addWidget(login,3,1);
            setLayout(final);
            this->setFixedSize(200,200);
            setWindowTitle(cour_tmp);
            QCoreApplication::processEvents();

            content = "-1";
            //break;
        }
    }
    //cap.release();
    //cout << "aaa";
    //return 0;
}
int Widget::second_to_hour(int second){
    int hour = second / 3600;
    second -= hour*3600;
    int min = second / 60;
    second -= min*60;
    int real_second = second;
    int sum = hour*10000 + min*100 + real_second;
    return sum;
}



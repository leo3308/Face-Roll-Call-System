#ifndef FACE_H
#define FACE_H
#include <iostream>
#include <string>

//include opencv core
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"

//file handling
#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;
using namespace cv::face;

static Mat MatNorm(InputArray _src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    switch (src.channels()) {
        case 1:
            cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
            break;
        case 3:
            cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
            break;
        default:
            src.copyTo(dst);
            break;
    }
    return dst;
}

static void dbread(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';'){
    std::ifstream file(filename.c_str(), ifstream::in);

    if (!file){
        string error = "no valid input file";
        CV_Error(CV_StsBadArg, error);
    }

    string line, path, label;
    while (getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, label);
        if (!path.empty() && !label.empty()){
            images.push_back(imread(path, 0));
            labels.push_back(atoi(label.c_str()));
        }
    }
}

void eigenFaceTrainer(){
    vector<Mat> images;
    vector<int> labels;

    try{
        string filename = "/Users/Leo/Desktop/b.txt";
        dbread(filename, images, labels);

        cout << "size of the images is " << images.size() << endl;
        cout << "size of the labes is " << labels.size() << endl;
        cout << "Training begins...." << endl;
    }
    catch (cv::Exception& e){
        cerr << " Error opening the file " << e.msg << endl;
        exit(1);
    }

    //create algorithm eigenface recognizer
    Ptr<FaceRecognizer>  model = createEigenFaceRecognizer();
    //train data
    model->train(images, labels);

    model->save("/Users/Leo/Desktop/eigenface.yml");

    cout << "Training finished...." << endl;

    waitKey(10000);
}

void fisherFaceTrainer(){
    /*in this two vector we put the images and labes for training*/
    vector<Mat> images;
    vector<int> labels;

    try{
        string filename = "/Users/Leo/Desktop/b.txt";
        dbread(filename, images, labels);

        cout << "size of the images is " << images.size() << endl;
        cout << "size of the labes is " << labels.size() << endl;
        cout << "Training begins...." << endl;
    }
    catch (cv::Exception& e){
        cerr << " Error opening the file " << e.msg << endl;
        exit(1);
    }


    Ptr<BasicFaceRecognizer> model = createFisherFaceRecognizer();

    model->train(images, labels);

    int height = images[0].rows;

    model->save("/Users/Leo/Desktop/fisherface.yml");

    cout << "Training finished...." << endl;

    Mat eigenvalues = model->getEigenValues();
    // And we can do the same to display the Eigenvectors (read Eigenfaces):
    Mat W = model->getEigenVectors();
    // Get the sample mean from the training data
    Mat mean = model->getMean();


    waitKey(10000);
}

void LBPHFaceTrainer(){

    vector<Mat> images;
    vector<int> labels;

    try{
        string filename = "E:/at.txt";
        dbread(filename, images, labels);

        cout << "size of the images is " << images.size() << endl;
        cout << "size of the labes is " << labels.size() << endl;
        cout << "Training begins...." << endl;
    }
    catch (cv::Exception& e){
        cerr << " Error opening the file " << e.msg << endl;
        exit(1);
    }

    //lbph face recognier model
    Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();

    //training images with relevant labels
    model->train(images, labels);

    //save the data in yaml file
    model->save("E:/FDB/yaml/LBPHface.yml");

    cout << "training finished...." << endl;

    waitKey(10000);
}

//lbpcascades works in lbphrecognier as fast as haarcascades
int  FaceRecognition(){

    int leo_count = 0;

    cout << "start recognizing..." << endl;

    //load pre-trained data sets
    Ptr<BasicFaceRecognizer>  model = createFisherFaceRecognizer();
    model->load("/Users/Leo/Desktop/opencv_test/fisherface.yml");

    Mat testSample = imread("/Users/Leo/Desktop/opencv_test/we_faces/s1/4.jpg", 0);

    int img_width = testSample.cols;
    int img_height = testSample.rows;


    //lbpcascades/lbpcascade_frontalface.xml
    string classifier = "/usr/local/Cellar/opencv3/3.2.0/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";

    CascadeClassifier face_cascade;
    string window = "Capture - face detection";

    if (!face_cascade.load(classifier)){
        cout << " Error loading file" << endl;
        return -1;
    }

    VideoCapture cap(0);
    //VideoCapture cap("C:/Users/lsf-admin/Pictures/Camera Roll/video000.mp4");

    if (!cap.isOpened())
    {
        cout << "exit" << endl;
        return -1;
    }

    //double fps = cap.get(CV_CAP_PROP_FPS);
    //cout << " Frames per seconds " << fps << endl;
    namedWindow(window, 1);
    int count = 0;

    while (true)
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
            original = frame.clone();

            //convert image to gray scale and equalize
            cvtColor(original, graySacleFrame, CV_BGR2GRAY);
            //equalizeHist(graySacleFrame, graySacleFrame);

            //detect face in gray image
            face_cascade.detectMultiScale(graySacleFrame, faces, 1.1, 3, 0, cv::Size(90, 90));

            //number of faces detected
            cout << faces.size() << " faces detected" << endl;
            std::string frameset = std::to_string(count);
            std::string faceset = std::to_string(faces.size());

            int width = 0, height = 0;

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
                int label = -1; double confidence = 0;
                model->predict(face_resized, label, confidence);

                confi = to_string(confidence);

                cout << " confidence " << confidence << endl;

                //drawing green rectagle in recognize face
                rectangle(original, face_i, CV_RGB(0, 255, 0), 1);
                string text = "Detected";

                if(label == 0){
                    Pname = "4how pig";
                }
                else if(label == 1){
                    Pname = "leo pig";
                    leo_count++;
                }
                else if( label == 2){
                    Pname = "wanting pig";
                }
                else if (label == 3){
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
            putText(original, "Confidence: " + confi, Point(30, 120), CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
            //display to the window
            stringstream ss;
            ss << count;
            string str = ss.str();
            //imwrite("/Users/Leo/Desktop/leo_face_pic/"+str+".jpg",original);
            cv::imshow(window, original);

            //cout << "model infor " << model->getDouble("threshold") << endl;

        }
        //if (waitKey(3000) >= 0) break;
        waitKey(100);
        if(count == 20){
            double rate = (float)leo_count/count;
            rate *= 100;
            cout <<"rate : "<< rate<< "%" << endl;
            break;
        }
    }
    destroyWindow(window);
    return 0;
}

#endif // FACE_H

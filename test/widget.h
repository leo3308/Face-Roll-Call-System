#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QImage>

class Widget : public QWidget
{
    Q_OBJECT

public :
    Widget(QWidget *parent = 0);
public slots:
    void Dep_Btn_click();
    void back_click();
    void CS_grade_click();
    void cs_course_click();
    void submit_click();
    void FaceRecognition2();
    int second_to_hour(int);
private:
    QString department[18] = {"法律學系","企業管理學系","休閒運動管理學系","經濟學系","會計學系","金融與合作經營學系","財政學系"
                              ,"不動產與城鄉環境學系","公共行政暨政策學系","中國文學系","歷史學系","應用外語學系","社會學系"
                              ,"社會工作學系","統計學系","電機工程學系","資訊工程學系","通訊工程學系"};
    QString CS_course1[6] = {"微積分II","線性代數","物件導向程式設計","物理學","數位系統設計","物件導向程式設計實習"};
    QString CS_course2[6] = {"數位電子電路實驗","微算機實驗","電腦網路實習","電腦網路","進階資料結構","多媒體技術與應用"};
    QString CS_course3[12] = {"資料庫系統","作業系統","資訊工程專論","正規語言","網路程式設計","雲端運算導論","資訊安全導論"
                           ,"影像處理導論","電腦視覺","網路安全導論","工程倫理","數位音訊處理"};
    QString CS_course4[4] = {"資訊工程專論","工程倫理","編譯器","數位音訊處理"};
    QString Dep_tmp = "";
    QString cour_tmp = "";
    QPushButton *DepartmentBtn[18];
    QPushButton *cs_course_btn[12];
    QPushButton *Grade[4];
    QPushButton *backtoDep,*backtoGrade;
    QPushButton *submit,*cancel;
    QLabel *exm,*ans;
    QLabel *text;
    QLabel *imgframe;
    QLineEdit *num;
    QGridLayout *layout;
    QGridLayout *cs_course_layout;
    QGridLayout *gradelayout;
    QImage BG_image;

    QVBoxLayout *a;
    QGridLayout *final;
};

#endif // WIDGET_H

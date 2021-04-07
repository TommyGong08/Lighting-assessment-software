#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include "viewstandard.h"
#include "grayscalestandard.h"
#include "luminancestandard.h"
#include "lumuniformstan.h"
#include "whitefieldcostd.h"
#include "ganraoguang.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ShowData(int DATA);
    void ganraoguang_ShowData(int DATA);
    void Recover_lightButton(Ui::MainWindow *dis);
    void Set_lightButton(int number,bool judge,Ui::MainWindow *dis);
    void initStyle();

    double data[100][100];
    QString data1[100][100];
    int Max_Colnum = 0;
    int Colsum_sum=0;
    int ROW=0;
    int DATA=0;
    int Last_DATA=0;


private slots:
    void on_pBViewStan_clicked();

    void on_pBLumStan_clicked();

    void on_pBViewWhieStan_clicked();

    void on_pBLumUnif_clicked();

    void on_pBGrayScale_clicked();

    void on_pBGetInfo_clicked();

    void on_pBReset_clicked();

    void on_pBEvaluate_clicked();

    void on_pBViewStan_6_clicked();

    void on_pBViewStan_7_clicked();

    void on_pBViewStan_8_clicked();



private:
    Ui::MainWindow *ui;
    bool isread = false;
    bool judge=true;
};
#endif // MAINWINDOW_H

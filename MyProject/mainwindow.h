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
    void ShowData();

    double data[15];
    int Colnum = 2;
    QString ori_data[15];

private slots:
    void on_pBViewStan_clicked();

    void on_pBLumStan_clicked();

    void on_pBViewWhieStan_clicked();

    void on_pBLumUnif_clicked();

    void on_pBGrayScale_clicked();

    void on_pBGetInfo_clicked();

    void on_pBReset_clicked();

    void on_pBEvaluate_clicked();

    void on_pBshushidu_clicked();

    void on_pBganraoguang_clicked();

private:
    Ui::MainWindow *ui;
    bool isread = false;
};
#endif // MAINWINDOW_H

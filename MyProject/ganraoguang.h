#ifndef GANRAOGUANG_H
#define GANRAOGUANG_H

#include <QDialog>
#include "ganraoguang_driver.h"
#include "ganraoguang_illuminancy.h"
#include "ganraoguang_lightness.h"
#include "mainwindow.h"

namespace Ui {
class GanRaoGuang;
}

class GanRaoGuang : public QDialog
{
    Q_OBJECT

public:
    explicit GanRaoGuang(QWidget *parent = nullptr);
    ~GanRaoGuang();
    void ShowData();

    double data[20];
    int Colnum = 2;
    QString ori_data[20];

private slots:
    void on_pushGRGshushidu_clicked();
    void on_pBGRGhuoqu_clicked();
    void on_pBGRGpingjia_clicked();
    void on_pBGetInfo_3_clicked();
    void on_pBViewStan_2_clicked();
    void on_pBViewStan_clicked();
    void on_pBViewStan_3_clicked();


private:
    Ui::GanRaoGuang *ui;
    bool isread = false;
};
#endif // GANRAOGUANG_H

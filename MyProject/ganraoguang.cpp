#include "ui_ganraoguang.h"
#include "ganraoguang.h"
#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QAxObject>
#include <QVariant>
#include <QList>

GanRaoGuang::GanRaoGuang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GanRaoGuang)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");//
}

GanRaoGuang::~GanRaoGuang()
{
    delete ui;
}

void GanRaoGuang::on_pushGRGshushidu_clicked()
{
    this->hide();
    MainWindow m;
    //m.exec();
    //MainWindow main;
    //main.exec();
}

void GanRaoGuang::on_pBGRGhuoqu_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this, QStringLiteral("选择Excel文件"), "",QStringLiteral("Exel file(*.xls *.xlsx)"));
    if(filePath.isEmpty())return;

    QAxObject* excel=new QAxObject(this);
    excel->setControl("Excel.Application");//连接Excel控件
    excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
    excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
    //qDebug() << filePath << endl;

    //打开文件
    QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
    workbooks->dynamicCall("Open (const QString&)", filePath);
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
    //QAxObject *workbook = excel->querySubObject("Open (const QString &)", filePath);
    //qDebug() << "1" << endl;

    //打开表
    QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
    QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//工作表1，即sheet1
    //qDebug() << "2" << endl;

    //获取表中的数据到QVariant中
    QAxObject *usedRange=worksheet->querySubObject("UsedRange");
    QVariant var=usedRange->dynamicCall("value");
   // qDebug() << "3" << endl;

    QVariantList varRowContents=var.toList();
    //const int rowCount = varRowContents.size();
    QVariantList tmp;
    for(int i=15; i<20; ++i)
    {
        tmp=varRowContents[i].toList();
        //result.append(tmp);
        qDebug() << tmp[Colnum].value<double>() << endl;
        data[i] = tmp[Colnum].value<double>();
        ori_data[i] =  QString::number(data[i], 'f', 0);
    }
    //删除，防止程序关闭后有excel进程残留
    excel->dynamicCall("Quit(void)");
    delete excel;
    ShowData();
    isread = true;
}

void GanRaoGuang::ShowData()
{
    ui->lineEdit->setText(ori_data[15]);
    ui->lineEdit_2->setText(ori_data[16]);
    ui->lineEdit_4->setText(ori_data[17]);
    ui->lineEdit_3->setText(ori_data[18]);
    ui->lineEdit_5->setText(ori_data[19]);

}
void GanRaoGuang::on_pBGRGpingjia_clicked()
{
    //评价视角
    if(!isread)
    {
        QMessageBox::information(NULL, "错误", "未导入数据,无法评价", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
    }
    if(data[15]<=600)
    {
        //视角标签设置为绿色
        ui->LBCoordinate->setStyleSheet("QLabel{background-color:rgb(0,238,0);}");
    }else{
        ui->LBCoordinate->setStyleSheet("QLabel{background-color:rgb(255,106,106);}");
    }
    if(data[16]<=25&&data[17]<=5)
    {
         ui->LBCoordinate_2->setStyleSheet("QLabel{background-color:rgb(0,238,0);}");
    }else{
         ui->LBCoordinate_2->setStyleSheet("QLabel{background-color:rgb(255,106,106);}");
    }
    if(data[18]<=5 && data[19]<=15 )
    {
        ui->LBCoordinate_3->setStyleSheet("QLabel{background-color:rgb(0,238,0);}");
    }else{
        ui->LBCoordinate_3->setStyleSheet("QLabel{background-color:rgb(255,106,106);}");
    }

}
void GanRaoGuang::on_pBGetInfo_3_clicked()
{
    //重置textEdit
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    //重置label颜色
    ui->LBCoordinate->setStyleSheet("QLabel{background-color: transparent;}");
    ui->LBCoordinate_2->setStyleSheet("QLabel{background-color: transparent;}");
    ui->LBCoordinate_3->setStyleSheet("QLabel{background-color: transparent;}");
    isread = false;

}

void GanRaoGuang::on_pBViewStan_clicked()
{
    GanRaoGuang_Lightness Lightness;
    Lightness.exec();

}
void GanRaoGuang::on_pBViewStan_2_clicked()
{
    GanRaoGuang_Illuminancy Illuminancy;
    Illuminancy.exec();


}
void GanRaoGuang::on_pBViewStan_3_clicked()
{
    GanRaoGuang_Driver Driver;
    Driver.exec();

}

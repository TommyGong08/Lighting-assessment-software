#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QAxObject>
#include <QVariant>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pBViewStan_clicked()
{
    ViewStandard viewstandard;
    viewstandard.exec();
}

void MainWindow::on_pBLumStan_clicked()
{
    LuminanceStandard lumstan;
    lumstan.exec();
}



void MainWindow::on_pBViewWhieStan_clicked()
{
    WhiteFieldCoStd whitestand;
    whitestand.exec();
}



void MainWindow::on_pBLumUnif_clicked()
{
    LumUniformStan lumunistand;
    lumunistand.exec();
}



void MainWindow::on_pBGrayScale_clicked()
{
    GrayScaleStandard graystand;
    graystand.exec();
}
/*
void MainWindow::on_pBGetInfo_clicked()
{
    QString path = "D:/QTlearning/MyProject/test.txt";
    if(path.isEmpty() == false)
    {
        //文件对象
        QFile file(path);
        //只读文件
        bool isopen = file.open(QIODevice::ReadOnly | QIODevice::Text);
        if(isopen == true)
        {
            //读文件
            //QByteArray array = file.readAll();
            isread = true;
            qDebug() << "0" ;
            QString displayString;
            int i=1;
            while(!file.atEnd())
            {
                 QByteArray line = file.readLine();
                 QString str(line);
                 line = line.simplified();
                 ori_data[i] = line;
                 data[i] = line.toDouble();
                 qDebug() << data[i] << ";" << i;
                 i++;
            }
        }
        else qDebug() << "Can't Open the file!";
        //关闭文件
        file.close();
    }
    ShowData();
}
*/

void MainWindow::on_pBGetInfo_clicked()
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
    for(int i=1; i<15; ++i)
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


void MainWindow::ShowData()
{
    ui->lineEdit_1->setText(ori_data[1]);
    ui->lineEdit_2->setText(ori_data[2]);
    ui->lineEdit_3->setText(ori_data[3]);
    ui->lineEdit_4->setText(ori_data[4]);
    ui->lineEdit_5->setText(ori_data[5]);
    ui->lineEdit_6->setText(ori_data[6]);
    ui->lineEdit_7->setText(ori_data[7]);
    ui->lineEdit_8->setText(ori_data[8]);
    ui->lineEdit_9->setText(ori_data[9]);
    ui->lineEdit_10->setText(ori_data[10]);
    ui->lineEdit_11->setText(ori_data[11]);
    ui->lineEdit_12->setText(ori_data[12]);
    ui->lineEdit_13->setText(ori_data[13]);
    ui->lineEdit_14->setText(ori_data[14]);
}

void MainWindow::on_pBReset_clicked()
{
    //重置textEdit
    ui->lineEdit_1->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    ui->lineEdit_8->setText("");
    ui->lineEdit_9->setText("");
    ui->lineEdit_10->setText("");
    ui->lineEdit_11->setText("");
    ui->lineEdit_12->setText("");
    ui->lineEdit_13->setText("");
    ui->lineEdit_14->setText("");

    //重置label颜色
    ui->LBView->setStyleSheet("QLabel{background-color: transparent;}");
    ui->LBBright->setStyleSheet("QLabel{background-color: transparent;}");
    ui->LBCoordinate->setStyleSheet("QLabel{background-color: transparent;}");
    ui->LBlumUni->setStyleSheet("QLabel{background-color: transparent;}");
    ui->LBGrayLev->setStyleSheet("QLabel{background-color: transparent;}");
    isread = false;
}

void MainWindow::on_pBEvaluate_clicked()
{
    //评价视角
    if(!isread)
    {
        QMessageBox::information(NULL, "错误", "未导入数据,无法评价", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
    }
    if(data[1]>=50 && data[2]>=50 && data[3]>=10 && data[4] >=20)
    {
        //视角标签设置为绿色
        ui->LBView->setStyleSheet("QLabel{background-color:rgb(0,238,0);}");
    }else{
        ui->LBView->setStyleSheet("QLabel{background-color:rgb(255,106,106);}");
    }
    if(data[5]>=5000 && data[6]>=4000 && data[7]>=2000
       && data[8] >=1000 && data[9] >=300 && data[10]>=120)
    {
         ui->LBBright->setStyleSheet("QLabel{background-color:rgb(0,238,0);}");
    }else{
         ui->LBBright->setStyleSheet("QLabel{background-color:rgb(255,106,106);}");
    }
    if(data[11]>=-0.030 && data[11]<=-0.030 && data[12] >=-0.030 && data[12] <=0.030)
    {
        ui->LBCoordinate->setStyleSheet("QLabel{background-color:rgb(0,238,0);}");
    }else{
        ui->LBCoordinate->setStyleSheet("QLabel{background-color:rgb(255,106,106);}");
    }
    if(data[13]<10)
    {
        ui->LBlumUni->setStyleSheet("QLabel{background-color:rgb(0,238,0);}");
    }else{
        ui->LBlumUni->setStyleSheet("QLabel{background-color:rgb(255,106,106);}");
    }
    if( data[14]>=256)
    {
        ui->LBGrayLev->setStyleSheet("QLabel{background-color:rgb(0,238,0);}");
    }else{
        ui->LBGrayLev->setStyleSheet("QLabel{background-color:rgb(255,106,106);}");
    }
}

//点击舒适度评价跳转到舒适度界面
void MainWindow::on_pBshushidu_clicked()
{

}

//点击干扰光评价跳转到干扰光界面
void MainWindow::on_pBganraoguang_clicked()
{
    GanRaoGuang ganraoguang;
    //this->hide();
    ganraoguang.exec();
}

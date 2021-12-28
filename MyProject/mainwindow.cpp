#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QAxObject>
#include <QVariant>
#include <QList>
#include "qfile.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ninePointsMode = false;
    this->initStyle();
    //this->setStyleSheet("background-color:rgb(238,233,233)");
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

void MainWindow::on_pBViewStan_6_clicked()
{
    GanRaoGuang_Driver graystand;
    graystand.exec();
}
void MainWindow::on_pBViewStan_7_clicked()
{
    GanRaoGuang_Lightness graystand;
    graystand.exec();
}
void MainWindow::on_pBViewStan_8_clicked()
{
    GanRaoGuang_Illuminancy graystand;
    graystand.exec();
}

void MainWindow::on_pBViewStan_9_clicked()
{
    refresh_rate graystand;
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
    initStyle();
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
    QAxObject * rows = usedRange->querySubObject("Rows");
    QAxObject * columns = usedRange->querySubObject("Columns");
    int intRows = rows->property("Count").toInt();
    int intCols = columns->property("Count").toInt();
    qDebug() << "xls行数："<<intRows;
    qDebug() << "xls列数："<<intCols;
    int Col = columns -> property("Count").toInt();
    int Row = rows -> property("Count").toInt();
    int RowStart = usedRange -> property("Row").toInt();
    int ColStart = usedRange -> property("Column").toInt();

    ui->lineEdit->setText(QString::number(Col-1, 'f', 0));
    Max_Colnum=Col;
    qDebug() << Col<<" "<<Row<<" "<<RowStart<<" "<<ColStart;

    for (int i = RowStart+1; i < RowStart + Row; i++){
        QAxObject * cell = worksheet -> querySubObject("Cells(int,int)", i, ColStart);
        QString value = cell -> dynamicCall("Value2()").toString();
        if(value=="left_view")       ROW=1;
        else if(value=="right_view") ROW=2;
        else if(value=="up_view")    ROW=3;
        else if(value=="down_view")  ROW=4;
        else if(value=="out_full")   ROW=5;
        else if(value=="out_doub")   ROW=6;
        else if(value=="out_single") ROW=7;
        else if(value=="in_full")    ROW=8;
        else if(value=="in_doub")    ROW=9;
        else if(value=="in_single")  ROW=10;
        else if(value=="white_x")    ROW=11;
        else if(value=="white_y")    ROW=12;
        else if(value=="junyun")     ROW=13;
        else if(value=="gray")       ROW=14;
        else if(value=="ganrao_1")   ROW=15;
        else if(value=="ganrao_2")   ROW=16;
        else if(value=="ganrao_3")   ROW=17;
        else if(value=="ganrao_4")   ROW=18;
        else if(value=="ganrao_5")   ROW=19;
        else if(value=="refresh_rate")   ROW=20;
        delete cell;
        qDebug()<<value<<" "<<ROW;
        for(int j=ColStart+1;j<ColStart+Col;j++){
//            QTextCharFormat fmt;
//            fmt.setForeground(QColor(Qt::red));
//            ui->plainTextEdit->mergeCurrentCharFormat(fmt);
//            ui->plainTextEdit->insertPlainText("Life is short\n");
            QAxObject * cell = worksheet -> querySubObject("Cells(int,int)", i, j);
            QString value = cell -> dynamicCall("Value2()").toString();
            data1[ROW][j-ColStart]=value;
            data[ROW][j-ColStart]=value.toInt();
            qDebug()<<data[ROW][j-ColStart];

        }

    }

//    QVariant var=usedRange->dynamicCall("value");
//   // qDebug() << "3" << endl;

//    QVariantList varRowContents=var.toList();
//    //const int rowCount = varRowContents.size();
//    QVariantList tmp;
//    for(int i=1; i<15; ++i)
//    {
//        tmp=varRowContents[i].toList();
//        //result.append(tmp);
//        qDebug() << tmp[Colnum].value<double>() << endl;
//        data[i] = tmp[Colnum].value<double>();
//        ori_data[i] =  QString::number(data[i], 'f', 0);
//    }
    //删除，防止程序关闭后有excel进程残留
    excel->dynamicCall("Quit(void)");
    delete excel;
//    ShowData();
    isread = true;
}


void MainWindow::ShowData(int DATA)
{
    ui->lineEdit_15->setText(data1[1][DATA]);
    ui->lineEdit_16->setText(data1[2][DATA]);
    ui->lineEdit_17->setText(data1[3][DATA]);
    ui->lineEdit_18->setText(data1[4][DATA]);
    ui->lineEdit_19->setText(data1[5][DATA]);
    ui->lineEdit_20->setText(data1[6][DATA]);
    ui->lineEdit_21->setText(data1[7][DATA]);
    ui->lineEdit_22->setText(data1[8][DATA]);
    ui->lineEdit_23->setText(data1[9][DATA]);
    ui->lineEdit_24->setText(data1[10][DATA]);
    ui->lineEdit_25->setText(data1[11][DATA]);
    ui->lineEdit_26->setText(data1[12][DATA]);
    ui->lineEdit_27->setText(data1[13][DATA]);
    ui->lineEdit_28->setText(data1[14][DATA]);
}

void MainWindow::ganraoguang_ShowData(int DATA)
{
    ui->lineEdit_7->setText(data1[15][DATA]);
    ui->lineEdit_8->setText(data1[16][DATA]);
    ui->lineEdit_9->setText(data1[17][DATA]);
    ui->lineEdit_10->setText(data1[18][DATA]);
    ui->lineEdit_11->setText(data1[19][DATA]);
    ui->lineEdit_12->setText(data1[20][DATA]);
}


void MainWindow::on_pBReset_clicked()
{
    initStyle();
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
    Recover_lightButton(ui);//恢复灯光
    QString s=ui->lineEdit_1->text();//获取要显示的数据是第几组
    DATA=s.toInt();
    if(DATA<=0||DATA>=Max_Colnum){
        QMessageBox::information(NULL, "错误", "不存在该组数据，请重新输入你要评价的数据组数", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
    }
    ui->plainTextEdit->clear();
    int x=ui->tabWidget->currentIndex();
    QTextCharFormat fmt;
    fmt.setForeground(QColor(Qt::black));
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
    ui->plainTextEdit->insertPlainText("第"+QString::number(DATA, 'f', 0)+"组数据:\n");
    qDebug()<<x;
    if(x==0){
        ShowData(DATA);
        judge=true;
        QTextCharFormat fmt;
        fmt.setForeground(QColor(Qt::red));
        ui->plainTextEdit->mergeCurrentCharFormat(fmt);
        if(data[1][DATA]<50){
            ui->plainTextEdit->insertPlainText("视角中的左视角不符合标准！\n");
            judge=false;
        }
        if(data[2][DATA]<50){
            ui->plainTextEdit->insertPlainText("视角中的右视角不符合标准！\n");
            judge=false;
        }
        if(data[3][DATA]<10){
            ui->plainTextEdit->insertPlainText("视角中的上视角不符合标准！\n");
            judge=false;
        }
        if(data[4][DATA]<20){
            ui->plainTextEdit->insertPlainText("视角中的下视角不符合标准！\n");
            judge=false;
        }
        if(data[5][DATA]<5000){
            ui->plainTextEdit->insertPlainText("亮度中的室外全彩不符合标准！\n");
            judge=false;
        }
        if(data[6][DATA]<4000){
            ui->plainTextEdit->insertPlainText("亮度中的室外双色不符合标准！\n");
            judge=false;
        }
        if(data[7][DATA]<2000){
            ui->plainTextEdit->insertPlainText("亮度中的室外单色不符合标准！\n");
            judge=false;
        }
        if(data[8][DATA]<1000){
            ui->plainTextEdit->insertPlainText("亮度中的室内全彩不符合标准！\n");
            judge=false;
        }
        if(data[9][DATA]<300){
            ui->plainTextEdit->insertPlainText("亮度中的室内双色不符合标准！\n");
            judge=false;
        }
        if(data[10][DATA]<120){
            ui->plainTextEdit->insertPlainText("亮度中的室内单色不符合标准！\n");
            judge=false;
        }
        if(data[11][DATA]<-0.030&&data[11][DATA]>0.030){
            ui->plainTextEdit->insertPlainText("白场色坐标中的Δx的值不符合标准！\n");
            judge=false;
        }
        if(data[12][DATA]<-0.030&&data[12][DATA]>0.030){
            ui->plainTextEdit->insertPlainText("白场色坐标中的Δy的值不符合标准！\n");
            judge=false;
        }
        if(data[13][DATA]>10){
            ui->plainTextEdit->insertPlainText("亮度均匀性不符合标准！\n");
            judge=false;
        }
        if(data[14][DATA]<256){
            ui->plainTextEdit->insertPlainText("灰度等级不符合标准！\n");
            judge=false;
        }
        if(judge){
            QTextCharFormat fmt;
            fmt.setForeground(QColor(Qt::green));
            ui->plainTextEdit->mergeCurrentCharFormat(fmt);
            ui->plainTextEdit->insertPlainText("符合标准！\n");
            Set_lightButton(DATA,judge,ui);
        }
        else
            Set_lightButton(DATA,judge,ui);
    }

    else
    {
        ganraoguang_ShowData(DATA);
        judge=true;
        QTextCharFormat fmt;
        fmt.setForeground(QColor(Qt::red));
        ui->plainTextEdit->mergeCurrentCharFormat(fmt);
        if(data[15][DATA]>600){
            ui->plainTextEdit->insertPlainText("亮度不符合标准！\n");
            judge=false;
        }
        if(data[16][DATA]>25){
            ui->plainTextEdit->insertPlainText("照度中的非熄灯时段不符合标准！\n");
            judge=false;
        }
        if(data[17][DATA]>5){
            ui->plainTextEdit->insertPlainText("照度中的熄灯时段不符合标准！\n");
            judge=false;
        }
        if(data[18][DATA]>5){
            ui->plainTextEdit->insertPlainText("驾驶员干扰光中的适应亮度不符合标准！\n");
            judge=false;
        }
        if(data[19][DATA]>15){
            ui->plainTextEdit->insertPlainText("驾驶员干扰光中的阈值增量不符合标准！\n");
            judge=false;
        }
        if(data[20][DATA]<60||data[20][DATA]>5000){
            ui->plainTextEdit->insertPlainText("驾驶员干扰光中的阈值增量不符合标准！\n");
            judge=false;
        }
        if(judge){
            QTextCharFormat fmt;
            fmt.setForeground(QColor(Qt::green));
            ui->plainTextEdit->mergeCurrentCharFormat(fmt);
            ui->plainTextEdit->insertPlainText("符合标准！\n");
            Set_lightButton(DATA,judge,ui);
        }
        else
            Set_lightButton(DATA,judge,ui);
    }

}

void MainWindow::Recover_lightButton( Ui::MainWindow *dis)
{
    dis->lightButton1_1->setLightBlue();
    dis->lightButton1_2->setLightBlue();
    dis->lightButton1_3->setLightBlue();
    dis->lightButton1_6->setLightBlue();
    dis->lightButton1_7->setLightBlue();
    dis->lightButton1_8->setLightBlue();
    dis->lightButton1_11->setLightBlue();
    dis->lightButton1_12->setLightBlue();
    dis->lightButton1_13->setLightBlue();
    if(ninePointsMode == false){
        dis->lightButton1_4->setLightBlue();
        dis->lightButton1_5->setLightBlue();
        dis->lightButton1_9->setLightBlue();
        dis->lightButton1_10->setLightBlue();
        dis->lightButton1_14->setLightBlue();
        dis->lightButton1_15->setLightBlue();
        dis->lightButton1_16->setLightBlue();
        dis->lightButton1_17->setLightBlue();
        dis->lightButton1_18->setLightBlue();
        dis->lightButton1_19->setLightBlue();
        dis->lightButton1_20->setLightBlue();
        dis->lightButton1_21->setLightBlue();
        dis->lightButton1_22->setLightBlue();
        dis->lightButton1_23->setLightBlue();
        dis->lightButton1_24->setLightBlue();
        dis->lightButton1_25->setLightBlue();
    }
    else if (ninePointsMode == true){
        dis->lightButton1_4->setLightGray();
        dis->lightButton1_5->setLightGray();
        dis->lightButton1_9->setLightGray();
        dis->lightButton1_10->setLightGray();
        dis->lightButton1_14->setLightGray();
        dis->lightButton1_15->setLightGray();
        dis->lightButton1_16->setLightGray();
        dis->lightButton1_17->setLightGray();
        dis->lightButton1_18->setLightGray();
        dis->lightButton1_19->setLightGray();
        dis->lightButton1_20->setLightGray();
        dis->lightButton1_21->setLightGray();
        dis->lightButton1_22->setLightGray();
        dis->lightButton1_23->setLightGray();
        dis->lightButton1_24->setLightGray();
        dis->lightButton1_25->setLightGray();
    }
}

void MainWindow::Set_lightButton(int number,bool judge,Ui::MainWindow *dis)
{
    number=number%21+number/21;
    if(number==1){
        if(judge) dis->lightButton1_1->setLightGreen();
        else      dis->lightButton1_1->setLightRed();
    }
    else if(number==2){
        if(judge) dis->lightButton1_2->setLightGreen();
        else      dis->lightButton1_2->setLightRed();
    }
    else if(number==3){
        if(judge) dis->lightButton1_3->setLightGreen();
        else      dis->lightButton1_3->setLightRed();
    }
    else if(number==4){
        if(judge) dis->lightButton1_4->setLightGreen();
        else      dis->lightButton1_4->setLightRed();
    }
    else if(number==5){
        if(judge) dis->lightButton1_5->setLightGreen();
        else      dis->lightButton1_5->setLightRed();
    }
    else if(number==6){
        if(judge) dis->lightButton1_6->setLightGreen();
        else      dis->lightButton1_6->setLightRed();
    }
    else if(number==7){
        if(judge) dis->lightButton1_7->setLightGreen();
        else      dis->lightButton1_7->setLightRed();
    }
    else if(number==8){
        if(judge) dis->lightButton1_8->setLightGreen();
        else      dis->lightButton1_8->setLightRed();
    }
    else if(number==9){
        if(judge) dis->lightButton1_9->setLightGreen();
        else      dis->lightButton1_9->setLightRed();
    }
    else if(number==10){
        if(judge) dis->lightButton1_10->setLightGreen();
        else      dis->lightButton1_10->setLightRed();
    }
    else if(number==11){
        if(judge) dis->lightButton1_11->setLightGreen();
        else      dis->lightButton1_11->setLightRed();
    }
    else if(number==12){
        if(judge) dis->lightButton1_12->setLightGreen();
        else      dis->lightButton1_12->setLightRed();
    }
    else if(number==13){
        if(judge) dis->lightButton1_13->setLightGreen();
        else      dis->lightButton1_13->setLightRed();
    }
    else if(number==14){
        if(judge) dis->lightButton1_14->setLightGreen();
        else      dis->lightButton1_14->setLightRed();
    }
    else if(number==15){
        if(judge) dis->lightButton1_15->setLightGreen();
        else      dis->lightButton1_15->setLightRed();
    }
    else if(number==16){
        if(judge) dis->lightButton1_16->setLightGreen();
        else      dis->lightButton1_16->setLightRed();
    }
    else if(number==17){
        if(judge) dis->lightButton1_17->setLightGreen();
        else      dis->lightButton1_17->setLightRed();
    }
    else if(number==18){
        if(judge) dis->lightButton1_18->setLightGreen();
        else      dis->lightButton1_18->setLightRed();
    }
    else if(number==19){
        if(judge) dis->lightButton1_19->setLightGreen();
        else      dis->lightButton1_19->setLightRed();
    }
    else if(number==20){
        if(judge) dis->lightButton1_20->setLightGreen();
        else      dis->lightButton1_20->setLightRed();
    }
    else if(number==21){
        if(judge) dis->lightButton1_21->setLightGreen();
        else      dis->lightButton1_21->setLightRed();
    }
    else if(number==22){
        if(judge) dis->lightButton1_22->setLightGreen();
        else      dis->lightButton1_22->setLightRed();
    }
    else if(number==23){
        if(judge) dis->lightButton1_23->setLightGreen();
        else      dis->lightButton1_23->setLightRed();
    }
    else if(number==24){
        if(judge) dis->lightButton1_24->setLightGreen();
        else      dis->lightButton1_24->setLightRed();
    }
    else if(number==25){
        if(judge) dis->lightButton1_25->setLightGreen();
        else      dis->lightButton1_25->setLightRed();
    }
}

void MainWindow::initStyle()
{
    //重置textEdit
    ui->lineEdit_7->setText("");
    ui->lineEdit_8->setText("");
    ui->lineEdit_9->setText("");
    ui->lineEdit_10->setText("");
    ui->lineEdit_11->setText("");
    ui->lineEdit_12->setText("");
    ui->lineEdit_15->setText("");
    ui->lineEdit_16->setText("");
    ui->lineEdit_17->setText("");
    ui->lineEdit_18->setText("");
    ui->lineEdit_19->setText("");
    ui->lineEdit_20->setText("");
    ui->lineEdit_21->setText("");
    ui->lineEdit_22->setText("");
    ui->lineEdit_23->setText("");
    ui->lineEdit_24->setText("");
    ui->lineEdit_25->setText("");
    ui->lineEdit_26->setText("");
    ui->lineEdit_27->setText("");
    ui->lineEdit_28->setText("");
    Recover_lightButton(ui);//恢复灯光
    ui->lineEdit->setText("");
    ui->lineEdit_1->setText("");
    ui->plainTextEdit->clear();
}



void MainWindow::grayButtonDisplay(Ui::MainWindow *dis){
    if(ninePointsMode == false){
        dis->lightButton1_4->setLightBlue();
        dis->lightButton1_5->setLightBlue();
        dis->lightButton1_9->setLightBlue();
        dis->lightButton1_10->setLightBlue();
        dis->lightButton1_14->setLightBlue();
        dis->lightButton1_15->setLightBlue();
        dis->lightButton1_16->setLightBlue();
        dis->lightButton1_17->setLightBlue();
        dis->lightButton1_18->setLightBlue();
        dis->lightButton1_19->setLightBlue();
        dis->lightButton1_20->setLightBlue();
        dis->lightButton1_21->setLightBlue();
        dis->lightButton1_22->setLightBlue();
        dis->lightButton1_23->setLightBlue();
        dis->lightButton1_24->setLightBlue();
        dis->lightButton1_25->setLightBlue();
    }
    else if (ninePointsMode == true){
        dis->lightButton1_4->setLightGray();
        dis->lightButton1_5->setLightGray();
        dis->lightButton1_9->setLightGray();
        dis->lightButton1_10->setLightGray();
        dis->lightButton1_14->setLightGray();
        dis->lightButton1_15->setLightGray();
        dis->lightButton1_16->setLightGray();
        dis->lightButton1_17->setLightGray();
        dis->lightButton1_18->setLightGray();
        dis->lightButton1_19->setLightGray();
        dis->lightButton1_20->setLightGray();
        dis->lightButton1_21->setLightGray();
        dis->lightButton1_22->setLightGray();
        dis->lightButton1_23->setLightGray();
        dis->lightButton1_24->setLightGray();
        dis->lightButton1_25->setLightGray();
    }
}


void MainWindow::on_pBNinePoints_clicked()
{
    ninePointsMode = true;
    //qDebug() << "nine point mode: true";
    grayButtonDisplay(ui);
}

void MainWindow::on_pBTwentyFivePoints_clicked()
{
    ninePointsMode = false;
    //qDebug() << "nine point mode: false";
    grayButtonDisplay(ui);
}

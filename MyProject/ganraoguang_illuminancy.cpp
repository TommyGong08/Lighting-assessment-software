#include "ganraoguang_illuminancy.h"
#include "ui_ganraoguang_illuminancy.h"

GanRaoGuang_Illuminancy::GanRaoGuang_Illuminancy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GanRaoGuang_Illuminancy)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");
}

GanRaoGuang_Illuminancy::~GanRaoGuang_Illuminancy()
{
    delete ui;
}

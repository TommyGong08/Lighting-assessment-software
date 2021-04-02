#include "ganraoguang_driver.h"
#include "ui_ganraoguang_driver.h"

GanRaoGuang_Driver::GanRaoGuang_Driver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GanRaoGuang_Driver)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");
}

GanRaoGuang_Driver::~GanRaoGuang_Driver()
{
    delete ui;
}

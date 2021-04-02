#include "ganraoguang_lightness.h"
#include "ui_ganraoguang_lightness.h"

GanRaoGuang_Lightness::GanRaoGuang_Lightness(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GanRaoGuang_Lightness)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");
}

GanRaoGuang_Lightness::~GanRaoGuang_Lightness()
{
    delete ui;
}

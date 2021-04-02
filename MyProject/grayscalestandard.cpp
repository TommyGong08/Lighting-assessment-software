#include "grayscalestandard.h"
#include "ui_grayscalestandard.h"

GrayScaleStandard::GrayScaleStandard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrayScaleStandard)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");
}

GrayScaleStandard::~GrayScaleStandard()
{
    delete ui;
}

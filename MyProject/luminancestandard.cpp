#include "luminancestandard.h"
#include "ui_luminancestandard.h"

LuminanceStandard::LuminanceStandard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LuminanceStandard)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");
}

LuminanceStandard::~LuminanceStandard()
{
    delete ui;
}

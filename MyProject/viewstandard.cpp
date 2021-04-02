#include "viewstandard.h"
#include "ui_viewstandard.h"

ViewStandard::ViewStandard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewStandard)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");
}

ViewStandard::~ViewStandard()
{
    delete ui;
}

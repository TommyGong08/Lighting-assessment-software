#include "lumuniformstan.h"
#include "ui_lumuniformstan.h"

LumUniformStan::LumUniformStan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LumUniformStan)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");
}

LumUniformStan::~LumUniformStan()
{
    delete ui;
}

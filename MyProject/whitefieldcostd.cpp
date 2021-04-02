#include "whitefieldcostd.h"
#include "ui_whitefieldcostd.h"

WhiteFieldCoStd::WhiteFieldCoStd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WhiteFieldCoStd)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(238,233,233)");
}

WhiteFieldCoStd::~WhiteFieldCoStd()
{
    delete ui;
}

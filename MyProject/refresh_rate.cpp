#include "refresh_rate.h"
#include "ui_refresh_rate.h"

refresh_rate::refresh_rate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::refresh_rate)
{
    ui->setupUi(this);
}

refresh_rate::~refresh_rate()
{
    delete ui;
}

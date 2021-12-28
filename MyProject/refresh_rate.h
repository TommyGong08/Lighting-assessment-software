#ifndef REFRESH_RATE_H
#define REFRESH_RATE_H

#include <QDialog>

namespace Ui {
class refresh_rate;
}

class refresh_rate : public QDialog
{
    Q_OBJECT

public:
    explicit refresh_rate(QWidget *parent = nullptr);
    ~refresh_rate();

private:
    Ui::refresh_rate *ui;
};

#endif // REFRESH_RATE_H

#ifndef GANRAOGUANG_DRIVER_H
#define GANRAOGUANG_DRIVER_H

#include <QDialog>

namespace Ui {
class GanRaoGuang_Driver;
}

class GanRaoGuang_Driver : public QDialog
{
    Q_OBJECT

public:
    explicit GanRaoGuang_Driver(QWidget *parent = nullptr);
    ~GanRaoGuang_Driver();

private:
    Ui::GanRaoGuang_Driver *ui;
};

#endif // GANRAOGUANG_DRIVER_H

#ifndef GANRAOGUANG_ILLUMINANCY_H
#define GANRAOGUANG_ILLUMINANCY_H

#include <QDialog>

namespace Ui {
class GanRaoGuang_Illuminancy;
}

class GanRaoGuang_Illuminancy : public QDialog
{
    Q_OBJECT

public:
    explicit GanRaoGuang_Illuminancy(QWidget *parent = nullptr);
    ~GanRaoGuang_Illuminancy();

private:
    Ui::GanRaoGuang_Illuminancy *ui;
};

#endif // GANRAOGUANG_ILLUMINANCY_H

#ifndef GANRAOGUANG_LIGHTNESS_H
#define GANRAOGUANG_LIGHTNESS_H

#include <QDialog>

namespace Ui {
class GanRaoGuang_Lightness;
}

class GanRaoGuang_Lightness : public QDialog
{
    Q_OBJECT

public:
    explicit GanRaoGuang_Lightness(QWidget *parent = nullptr);
    ~GanRaoGuang_Lightness();

private:
    Ui::GanRaoGuang_Lightness *ui;
};

#endif // GANRAOGUANG_LIGHTNESS_H

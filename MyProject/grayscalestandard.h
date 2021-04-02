#ifndef GRAYSCALESTANDARD_H
#define GRAYSCALESTANDARD_H

#include <QDialog>

namespace Ui {
class GrayScaleStandard;
}

class GrayScaleStandard : public QDialog
{
    Q_OBJECT

public:
    explicit GrayScaleStandard(QWidget *parent = nullptr);
    ~GrayScaleStandard();

private:
    Ui::GrayScaleStandard *ui;
};

#endif // GRAYSCALESTANDARD_H

#ifndef LUMINANCESTANDARD_H
#define LUMINANCESTANDARD_H

#include <QDialog>

namespace Ui {
class LuminanceStandard;
}

class LuminanceStandard : public QDialog
{
    Q_OBJECT

public:
    explicit LuminanceStandard(QWidget *parent = nullptr);
    ~LuminanceStandard();

private:
    Ui::LuminanceStandard *ui;
};

#endif // LUMINANCESTANDARD_H

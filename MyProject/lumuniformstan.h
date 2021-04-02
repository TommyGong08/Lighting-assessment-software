#ifndef LUMUNIFORMSTAN_H
#define LUMUNIFORMSTAN_H

#include <QDialog>

namespace Ui {
class LumUniformStan;
}

class LumUniformStan : public QDialog
{
    Q_OBJECT

public:
    explicit LumUniformStan(QWidget *parent = nullptr);
    ~LumUniformStan();

private:
    Ui::LumUniformStan *ui;
};

#endif // LUMUNIFORMSTAN_H

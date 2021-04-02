#ifndef WHITEFIELDCOSTD_H
#define WHITEFIELDCOSTD_H

#include <QDialog>

namespace Ui {
class WhiteFieldCoStd;
}

class WhiteFieldCoStd : public QDialog
{
    Q_OBJECT

public:
    explicit WhiteFieldCoStd(QWidget *parent = nullptr);
    ~WhiteFieldCoStd();

private:
    Ui::WhiteFieldCoStd *ui;
};

#endif // WHITEFIELDCOSTD_H

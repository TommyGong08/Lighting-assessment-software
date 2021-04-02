#ifndef VIEWSTANDARD_H
#define VIEWSTANDARD_H

#include <QDialog>

namespace Ui {
class ViewStandard;
}

class ViewStandard : public QDialog
{
    Q_OBJECT

public:
    explicit ViewStandard(QWidget *parent = nullptr);
    ~ViewStandard();

private:
    Ui::ViewStandard *ui;
};

#endif // VIEWSTANDARD_H

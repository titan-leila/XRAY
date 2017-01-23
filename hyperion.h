#ifndef HYPERION_H
#define HYPERION_H

#include <QDialog>

namespace Ui {
class hyperion;
}

class hyperion : public QDialog
{
    Q_OBJECT

public:
    explicit hyperion(QWidget *parent = 0);
    ~hyperion();

private:
    Ui::hyperion *ui;
};

#endif // HYPERION_H

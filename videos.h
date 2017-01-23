#ifndef VIDEOS_H
#define VIDEOS_H

#include <QDialog>

namespace Ui {
class Videos;
}

class Videos : public QDialog
{
    Q_OBJECT

public:
    explicit Videos(QWidget *parent = 0);
    ~Videos();

private:
    Ui::Videos *ui;
};

#endif // VIDEOS_H

#ifndef PRICEWINDOW_H
#define PRICEWINDOW_H

#include <QDialog>

namespace Ui {
class PriceWindow;
}

class PriceWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PriceWindow(QWidget *parent = 0);
    ~PriceWindow();

private:
    Ui::PriceWindow *ui;
};

#endif // PRICEWINDOW_H

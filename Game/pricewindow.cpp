#include "pricewindow.h"
#include "ui_pricewindow.h"

PriceWindow::PriceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PriceWindow)
{
    ui->setupUi(this);
}

PriceWindow::~PriceWindow()
{
    delete ui;
}

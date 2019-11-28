#include "startdialog.h"
#include "ui_startdialog.h"

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    ui->setupUi(this);
    setWindowTitle("Settings");
    setWindowIcon(QIcon(QPixmap("../../juho-ja-leo/Game/Sprites/adamsmith_small.png")));
    //this->setWindowState(Qt::WindowFullScreen);
}

startDialog::~startDialog()
{
    delete ui;
}

void startDialog::on_buttonBox_accepted()
{
    emit nameConfirmed(ui->nameEdit->text().toStdString());
}

#include "startdialog.h"
#include "ui_startdialog.h"

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    ui->setupUi(this);
    setWindowTitle("Adam Smith's Capitalization");
    setWindowIcon(QIcon(QPixmap(
                            "../../juho-ja-leo/Game/Sprites/adamsmith_small.png")));
    ui->bgImage->setPixmap(QPixmap("../../juho-ja-leo/Game/Sprites/background.png"));
    ui->bgImage->setFixedSize(500,500);
}

startDialog::~startDialog()
{
    delete ui;
}

void startDialog::on_buttonBox_accepted()
{
    emit nameConfirmed(ui->nameEdit->text().toStdString());
}

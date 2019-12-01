#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
class startDialog;
}
/**
 * @brief The startDialog class asks for player name and starts the game
 */
class startDialog : public QDialog
{
    Q_OBJECT

public:
    explicit startDialog(QWidget *parent = 0);
    Ui::startDialog *ui;
    ~startDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void nameConfirmed(std::string name);

private:

};

#endif // STARTDIALOG_H

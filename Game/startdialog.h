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
    explicit startDialog(QWidget *parent = nullptr);
    Ui::startDialog *ui;
    ~startDialog();

private slots:
    /**
     * @brief on_buttonBox_accepted called when user presses ok
     *  at the dialog screen
     */
    void on_buttonBox_accepted();

signals:
    /**
     * @brief nameConfirmed sends the given username to connected components
     * @param name
     */
    void nameConfirmed(std::string name);

private:

};

#endif // STARTDIALOG_H

#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <string>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();

private slots:
    void on_OkButton_clicked();

signals:
    void nameConfirmed(QString name);

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H

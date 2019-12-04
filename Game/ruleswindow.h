#ifndef RULESWINDOW_H
#define RULESWINDOW_H

#include <QDialog>

namespace Ui {
class rulesWindow;
}

class rulesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit rulesWindow(QWidget *parent = 0);
    ~rulesWindow();

    void showRules();
    void showStory();

private slots:
    void on_RulesButton_clicked();

    void on_StoryButton_clicked();

private:
    Ui::rulesWindow *ui;
};

#endif // RULESWINDOW_H

#ifndef RULESWINDOW_H
#define RULESWINDOW_H

#include <QDialog>
#include <fstream>
#include <iostream>

namespace Ui {
class rulesWindow;
}

class rulesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit rulesWindow(QWidget *parent = nullptr);
    ~rulesWindow();

    /**
     * @brief showRules
     * shows rules in the window's text box
     */
    void showRules();

    /**
     * @brief showStory
     * shows game's backstory in the window's text box
     */
    void showStory();

private slots:
    /**
     * @brief on_RulesButton_clicked
     * activates showRules()
     */
    void on_RulesButton_clicked();

    /**
     * @brief on_StoryButton_clicked
     * activates showStory()
     */
    void on_StoryButton_clicked();

    /**
     * @brief on_highScoreButton_clicked
     * loads scores from highscores.txt text file and shows them in window's
     * text box
     */
    void on_highScoreButton_clicked();

private:
    Ui::rulesWindow *ui;
};

#endif // RULESWINDOW_H

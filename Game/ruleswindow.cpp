#include "ruleswindow.h"
#include "ui_ruleswindow.h"

rulesWindow::rulesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rulesWindow)
{
    ui->setupUi(this);
    showRules();
}

rulesWindow::~rulesWindow()
{
    delete ui;
}

void rulesWindow::showRules()
{
    ui->textBrowser->setText(
               "In this game you play as Adam Smith, the father of capitalism! Your aim is to earn money by building houses, "
               "hiring dirty finns to work for you and searching for treasures while avoiding robbers and alcoholics.\n\n"
               "To win the game, you need to make more money than you started with, find at least one treasure and get to the town"
               " in 20 turns. \n\n"
               "One turn composes of four possible actions that can be made in arbitrary order: Moving, seaching, building and hiring. \n\n"
               "You can zoom in and out of the map with + (plus) and - (minus) keys and move the view around the map with arrow keys.\n"
               "Right clicking a tile gives information about it.\n\n"
               "A tile can hold only one building. Different tiles have different capacities for workers:\n\n"
               "Grassland: 3 workers\n"
               "Forest: 4 workers \n"
               "Water: 5 workers. \n\n"
               "You can see your current money next to the coin icon.\n"
               "Most actions are done by clicking a button and then left clicking a tile in the map.\n\n"
               "Moving: You can move to any direction an amount specified by dice. Make sure to throw the dice before moving.\n\n"
               "Searching: You can search a tile next to you. There is a chance of finding a great treasure as well as being robbed. "
               "Searching costs 10 units of money. \n\n"
               "Building: You can build on a tile that is next to you. Different buildings cost different amounts of money "
               "and produce different amounts of money. A building does not make profit without workers.\n\n"
               "Hiring: You can hire people working in any of your buildings. Hiring a skilled person costs more but also "
               "yields a greater bonus to buildings production.\n\n"
               "To stop any action, just press the button again.\n"
               "You can do each action once per round. \n\n"
               "Young money, cash money!");
}

void rulesWindow::showStory()
{
    ui->textBrowser->setText(
                "Unknown to most, Adam Smith, the forefather of capitalism and an absolute mad lad, "
                 "made a secret detour on his way from Glasgow to Toulouse. "
                 "What could be the reason for this detour? Where did Smith go? What did he find?!\n\n"
                 "As a young lad living in 1700s Scotland, Smith had a severe accident. "
                 "This near-death experience led Smith to question his entire life. "
                 "After years spent in solitude meditating, Smith finally figured it out: It's all about money!\n\n"
                 "Inspired by his revolutionary idea, Smith devoted his life for spreading the joyful word of capitalism. "
                 "Unfortunately, not everyone agreed with Smith. A small county in a cold, dark and uncivilized "
                 "country far up north had declared its disinterest on capitalistic worldview. The name of this small county was Pirkanmaa. "
                 "Play as Adam Smith the father of capitalism in 1700s Pirkanmaa.\n\n"
                 "Show the dirty finns how capitalism solves all the problems by robbing their natural "
                 "resources and forcing them to work in sweatshops. \n\nBut beware: If Adam Smith goes too long without tea and biscuits, there's no "
                 "telling what will happen. You have 20 days to conquer Pirkanmaa before heading back to Britain. \n\nExperience the glory and satisfaction "
                 "in making as much money as possible as well as claim your part of the happiness that capitalism has "
                 "brought us in Adam Smith's Capitalization!");
}

void rulesWindow::on_RulesButton_clicked()
{
    ui->label->setText("Game rules: ");
    showRules();
}

void rulesWindow::on_StoryButton_clicked()
{
    ui->label->setText("Backstory: ");
    showStory();
}

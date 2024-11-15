#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    resize(800, 600);
    auto testButton = new QPushButton();
    testButton->setText("测试");
    testButton->resize(50,30);
    testButton->setProperty("class", "test-button");
    auto bgLayout = new QGridLayout;
    bgLayout->addItem(new QSpacerItem(30,30,QSizePolicy::Expanding),0,0);
    bgLayout->addWidget(testButton,0,1);
    bgLayout->addItem(new QSpacerItem(30,30,QSizePolicy::Expanding),0,2);

    auto bgWdiget = new QWidget;
    bgWdiget->setProperty("class", "main-window");
    bgWdiget->setLayout(bgLayout);

    setCentralWidget(bgWdiget);
}

MainWindow::~MainWindow() {}

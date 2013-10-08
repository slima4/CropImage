#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphicsview.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    _mainView = new CGraphicsView(ui->mainWidget);
    ui->gridLayout->addWidget(_mainView, 0, 0, 1, 1);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}


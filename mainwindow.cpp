#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphicsview.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    mainView = new CGraphicsView(ui->mainWidget);
    mainView->setObjectName(QStringLiteral("mainView"));

    ui->gridLayout->addWidget(mainView, 0, 0, 1, 1);

    connect(ui->actionOpen_image, SIGNAL(triggered()), SLOT(onActionOpenImage()));
}

CMainWindow::~CMainWindow()
{
    delete ui;
}


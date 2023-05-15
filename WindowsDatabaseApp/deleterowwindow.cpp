#include "deleterowwindow.h"
#include "ui_deleterowwindow.h"

DeleteRowWindow::DeleteRowWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteRowWindow)
{
    ui->setupUi(this);
}

DeleteRowWindow::~DeleteRowWindow()
{
    delete ui;
}

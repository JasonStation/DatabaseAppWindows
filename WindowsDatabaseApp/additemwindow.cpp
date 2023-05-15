#include "additemwindow.h"
#include "ui_additemwindow.h"

AddItemWindow::AddItemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemWindow)
{
    ui->setupUi(this);
}

AddItemWindow::~AddItemWindow()
{
    delete ui;
}

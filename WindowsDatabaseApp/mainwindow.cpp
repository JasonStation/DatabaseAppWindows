#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additemwindow.h"
#include "ui_additemwindow.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDebug>
#include <QAction>
#include "deleterowwindow.h"
#include "ui_deleterowwindow.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(openFile()) qDebug("Success");
    else qDebug("Fail");

    ui->tableWidget->clear();
    readDatabase();

    QStringList headerNames;
    headerNames << "ID      " << "Nama          " << " Harga Satuan       " << " Jumlah         ";
    ui->tableWidget->setColumnCount(headerNames.length());
    ui->tableWidget->setHorizontalHeaderLabels(headerNames);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    QAction *addAction = ui->menuData->addAction("Add...");
    connect(addAction, SIGNAL(triggered()), this, SLOT(addItemButtonPressed()));

    QAction *deleteAction = ui->menuData->addAction("Delete...");
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItemFromTable()));

    QAction *closeAction = ui->menuFile->addAction("Exit...");
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

    QAction *helpAction = ui->menuHelp->addAction("Made by: 2440051574 - Jason Leonardo");
   // connect(helpAction, SIGNAL(triggered()), this, SLOT(viewInformation()));

}

void MainWindow::AddItemToTable(QString &itemId, QString &itemName, int itemPrice, int itemQuantity){
    QSqlQuery q(database);

    q.prepare("INSERT INTO computers (computerId, computerName, computerPrice, computerStock) VALUES"
              " (:computerId, :computerName, :computerPrice, :computerStock)");

    q.bindValue(":computerId", itemId);
    q.bindValue(":computerName", itemName);
    q.bindValue(":computerPrice", itemPrice);
    q.bindValue(":computerStock", itemQuantity);

    bool succ = q.exec();
    if(succ) qDebug("Success inserting data");
    else qDebug() << "Error: " << q.lastError().text();


    int getItemCount = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(getItemCount+1);
    ui->tableWidget->setItem(getItemCount, 0, new QTableWidgetItem(itemId));
    ui->tableWidget->setItem(getItemCount, 1, new QTableWidgetItem(itemName));
    ui->tableWidget->setItem(getItemCount, 2, new QTableWidgetItem(QString::number(itemPrice)));
    ui->tableWidget->setItem(getItemCount, 3, new QTableWidgetItem(QString::number(itemQuantity)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::openFile(){
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("C://ComputerStore.db");
    return database.open();
}

void MainWindow::readDatabase(){
    int rowCounter = 0;
    QSqlQuery q("SELECT computerId, computerName, computerPrice, computerStock FROM computers", database);
    int i = 0;
    while(q.next()){
        ui->tableWidget->setItem(rowCounter, 0, new QTableWidgetItem(q.value("computerId").toString()));
        ui->tableWidget->setItem(rowCounter, 1, new QTableWidgetItem(q.value("computerName").toString()));
        ui->tableWidget->setItem(rowCounter, 2, new QTableWidgetItem(q.value("computerPrice").toString()));
        ui->tableWidget->setItem(rowCounter, 3, new QTableWidgetItem(q.value("computerStock").toString()));
        i++;
    }
}

void MainWindow::addItemButtonPressed(){
    AddItemWindow a;

    if (a.exec() == QDialog::Accepted)
    {
        QString id = a.ui->lineKode->text();
        QString name = a.ui->lineNama->text();
        int price = a.ui->spinHarga->value();
        int quantity = a.ui->spinJumlah->value();
        AddItemToTable(id, name, price, quantity);

}


}

void MainWindow::deleteItemFromTable(){
    findWindow.open();
    QPushButton *findButton = findWindow.ui->pushButton;
    connect(findButton, SIGNAL(clicked()), this, SLOT(findItem()));
}

void MainWindow::findItem(){
    QString findCode = findWindow.ui->lineKode->text();
    QSqlQuery qFind("SELECT computerId, computerName, computerPrice, computerStock FROM computers " + findCode, database);
    findWindow.ui->labelNama->setText(qFind.value("computerId").toString());
    findWindow.ui->labelHarga->setText(qFind.value("computerPrice").toString());
    findWindow.ui->spinJumlah->setValue(qFind.value("computerStock").toInt());
    int totalPrice = qFind.value("computerPrice").toInt() * qFind.value("computerStock").toInt();
    findWindow.ui->labelTotal->setText(QString::number(totalPrice));

    QString newValue = QString::number(findWindow.ui->spinJumlah->value());

    QSqlQuery updateQuery("UPDATE computers SET computerStock = " + newValue + " WHERE computerId = " + findCode, database);

}

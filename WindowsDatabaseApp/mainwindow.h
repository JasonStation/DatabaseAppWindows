#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include "deleterowwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool openFile();
    void readDatabase();
    DeleteRowWindow findWindow;

private:
    Ui::MainWindow *ui;
    void AddItemToTable(QString &itemId, QString &itemName, int itemPrice, int itemQuantity);

    QSqlDatabase database;
private slots:
    void addItemButtonPressed();
    void deleteItemFromTable();
    void findItem();


};

#endif // MAINWINDOW_H

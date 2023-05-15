#ifndef DELETEROWWINDOW_H
#define DELETEROWWINDOW_H

#include <QDialog>

namespace Ui {
class DeleteRowWindow;
}

class DeleteRowWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteRowWindow(QWidget *parent = nullptr);
    ~DeleteRowWindow();


    Ui::DeleteRowWindow *ui;
};

#endif // DELETEROWWINDOW_H

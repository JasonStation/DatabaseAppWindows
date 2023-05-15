#ifndef ADDITEMWINDOW_H
#define ADDITEMWINDOW_H

#include <QDialog>

namespace Ui {
class AddItemWindow;
}

class AddItemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemWindow(QWidget *parent = nullptr);
    ~AddItemWindow();

//private:
    Ui::AddItemWindow *ui;
};

#endif // ADDITEMWINDOW_H

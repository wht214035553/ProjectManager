#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "titleBar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void setWindowSize();


private:
    Ui::MainWindow *ui;

private:
    TitleBar *m_pTitleBar;
    QVBoxLayout *m_pMainLayout;
};

#endif // MAINWINDOW_H

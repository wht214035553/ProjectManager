#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTranslator>
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
    void setLanguage(QString file);


private:
    Ui::MainWindow *ui;

private:
    TitleBar *m_pTitleBar;
    QVBoxLayout *m_pMainLayout;
    QTranslator *m_pTranslator;
};

#endif // MAINWINDOW_H

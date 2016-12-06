#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qapplication.h"
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowSize();

    m_pTranslator = new QTranslator(this);
    this->setLanguage(":/en.qm");

    m_pTitleBar = new TitleBar(this);
    installEventFilter(m_pTitleBar);

    setWindowTitle(tr("PM"));
    setWindowIcon(QIcon(":/icon"));

    QMenu *menu[10];
    menu[0] = new QMenu("文件");
    menu[0]->addAction("编辑");
    menu[0]->addAction("查看");
    menu[0]->addAction("工具");

    QAction *act[10];
    act[0] = new QAction("新建",this);
    act[0]->setShortcut(Qt::CTRL | Qt::Key_A );
    act[0]->setStatusTip("这是一个新建菜单");

    act[1] = new QAction("打开",this);
    act[1]->setCheckable(true);

    menu[1] = new QMenu("保存");
    menu[1]->addAction(act[0]);
    menu[1]->addAction(act[1]);

    menu[2] = new QMenu("打印");
    menu[2]->addAction("打印设置");
    menu[2]->addMenu(menu[1]);


    QMenuBar *pMenuBar = new QMenuBar(this);
    pMenuBar->addMenu(menu[0]);
    pMenuBar->addMenu(menu[2]);

    m_pMainLayout = new QVBoxLayout();
    m_pMainLayout->addWidget(m_pTitleBar);
    m_pMainLayout->addWidget(pMenuBar);
    m_pMainLayout->addStretch();
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    QWidget *widget = new QWidget(this);
    widget->setLayout(m_pMainLayout);
    setCentralWidget(widget);
}

void MainWindow::setWindowSize()
{
    QDesktopWidget *deskTop = QApplication::desktop();
    int curMonitor = deskTop->screenNumber(this);
    //availableGeometry screenGeometry
    QRect rect = deskTop->availableGeometry(curMonitor);

    //this->resize(rect.width() - 100, rect.height() - 100);
    this->resize(800,600);
    this->move((deskTop->width() - this->width())/2, (deskTop->height() - this->height())/2);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void MainWindow::setLanguage(QString file)
{
    m_pTranslator->load(file);
    qApp->installTranslator(m_pTranslator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

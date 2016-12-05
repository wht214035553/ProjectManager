#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include "titleBar.h"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent,QColor titleBarBackgroudColor, \
                   unsigned int titleFontSize,QString titleColor)
    : QWidget(parent)
{
    setFixedHeight(30);

    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(20, 20);
    m_pIconLabel->setScaledContents(true);

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMinimizeButton->setFixedSize(27, 22);
    m_pMaximizeButton->setFixedSize(27, 22);
    m_pCloseButton->setFixedSize(27, 22);

    m_pTitleLabel->setObjectName("whiteLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pMinimizeButton->setToolTip("Minimize");
    m_pMaximizeButton->setToolTip("Maximize");
    m_pCloseButton->setToolTip("Close");

    m_pRubberBand = new QRubberBand(QRubberBand::Rectangle);
    m_pRubberBand->setWindowOpacity(0.3);
    m_bLeftButtonPressed = false;
    m_bLeftButtonPressedAndMove= false;

    setTitleBarBackgroudColor(titleBarBackgroudColor);
    setTitleFont(titleFontSize);
    setTitleColor(titleColor);
    m_desktopRect = QApplication::desktop()->availableGeometry( \
                QApplication::desktop()->screenNumber(this));

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pTitleLabel);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(5, 0, 5, 0);

    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

TitleBar::~TitleBar()
{
    delete m_pRubberBand;
    m_pRubberBand = NULL;
}

void TitleBar::setTitleBarBackgroudColor(QColor color)
{
    QPalette palette;

    this->setAutoFillBackground(true);
    palette.setColor(QPalette::Background, color);
    this->setPalette(palette);
}

void TitleBar::setTitleBarBackgroudImage(QString imageFile)
{
    QPalette palette;

    this->setAutoFillBackground(true);
    palette.setBrush(QPalette::Background, QBrush(QPixmap(imageFile)));
    this->setPalette(palette);
}

void TitleBar::setTitleFont(unsigned int fontSize)
{
    QFont font;
    font.setPointSize(fontSize);
    this->m_pTitleLabel->setFont(font);
}

void TitleBar::setTitleColor(QString color)
{
    this->m_pTitleLabel->setStyleSheet(color);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->button()==Qt::LeftButton)
        emit m_pMaximizeButton->clicked();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
    event->ignore();
#else
    if (event->button() == Qt::LeftButton)
    {
        QRect frameRect = this->window()->frameGeometry();
        m_pRubberBand->setGeometry(frameRect);
        m_PressPoint = event->globalPos();
        m_DragPoint = frameRect.topLeft();
        m_bLeftButtonPressed = true;
    }
#endif
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
#else
    if (m_bLeftButtonPressed)
    {
        m_pRubberBand->show();
        int windowWidth = this->window()->width();
        int windowHeight = this->window()->height();
        int desktopWidth = m_desktopRect.width();
        int desktopHeight = m_desktopRect.height();
        int suitWidth = desktopWidth - windowWidth;
        int suitHeight = desktopHeight - windowHeight;

        QPoint point = m_DragPoint + event->globalPos() - m_PressPoint;

        if (point.x() > suitWidth)
            point.setX(suitWidth);
        else if (point.x() < 0)
            point.setX(0);

        if (point.y() > suitHeight)
            point.setY(suitHeight);
        else if (point.y() < 0)
            point.setY(0);

        m_pRubberBand->move(point);
        m_bLeftButtonPressedAndMove = true;
    }
#endif
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
#else
    if (event->button() == Qt::LeftButton && m_bLeftButtonPressed && m_bLeftButtonPressedAndMove)
    {
        m_pRubberBand->hide();
        QWidget *pWindow = this->window();
        int windowWidth = pWindow->width();
        int windowHeight = pWindow->height();
        int desktopWidth = m_desktopRect.width();
        int desktopHeight = m_desktopRect.height();
        int suitWidth = desktopWidth - windowWidth;
        int suitHeight = desktopHeight - windowHeight;
        QPoint point = m_DragPoint + event->globalPos() - m_PressPoint;

        if (point.x() > suitWidth)
            point.setX(suitWidth);
        else if (point.x() < 0)
            point.setX(0);

        if (point.y() > suitHeight)
            point.setY(suitHeight);
        else if (point.y() < 0)
            point.setY(0);

        //pWindow->setGeometry(m_pRubberBand->geometry());
        pWindow->move(point);
        m_bLeftButtonPressed = false;
        m_bLeftButtonPressedAndMove = false;
    }
#endif
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMaximized();
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton)
        {
            pWindow->isMaximized() ? \
                        pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_pMaximizeButton->setToolTip(tr("Restore"));
            m_pMaximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
            m_pMaximizeButton->setToolTip(tr("Maximize"));
        }

        m_pMaximizeButton->setStyle(QApplication::style());
    }
}

// wht 摘抄自 http://blog.csdn.net/liang19890820/article/details/50555298
//

#ifndef TITLE_BAR
#define TITLE_BAR

#include <QWidget>
#include <QRubberBand>

class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0,QColor titleBarBackgroudColor = QColor(96,96,96), \
                      unsigned int titleFontSize = 15, QString titleColor = "color:rgb(0,0,0)");
    ~TitleBar();

public:
    //设置标题栏背景颜色
    void setTitleBarBackgroudColor(QColor color = QColor(96,96,96));

    //设置标题栏背景图片
    void setTitleBarBackgroudImage(QString imageFile);

    //设置标题栏文字大小
    void setTitleFont(unsigned int fontSize = 15);

    //设置标题栏文字颜色
    void setTitleColor(QString color = "color:rgb(0,0,0)");
protected:

    // 双击标题栏进行界面的最大化/还原
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    // 进行鼠界面的拖动
    virtual void mousePressEvent(QMouseEvent *event);

    // 鼠标移动事件，非windows平台用于拖动窗口
    virtual void mouseMoveEvent(QMouseEvent *event);

    // 鼠标释放事件，非windows平台用于拖动窗口
    virtual void mouseReleaseEvent(QMouseEvent *event);

    // 设置界面标题与图标
    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:

    // 进行最小化、最大化/还原、关闭操作
    void onClicked();

private:

    // 最大化/还原
    void updateMaximize();

private:
    QLabel *m_pIconLabel;
    QLabel *m_pTitleLabel;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pMaximizeButton;
    QPushButton *m_pCloseButton;
    QRubberBand *m_pRubberBand;
    bool m_bLeftButtonPressed;
    bool m_bLeftButtonPressedAndMove;
    QPoint m_PressPoint;
    QPoint m_DragPoint;
    QRect m_desktopRect;
};

#endif // TITLE_BAR

#include "mainwindow.h"

MainWindow::MainWindow(QWindow *parent)
    : QWindow(parent)
    , m_backingStore(new QBackingStore(this))
{
    // 窗口大小
    int w, h;
    w = h = 500;
    unit = 10;

    // 窗口居中，固定大小
    setGeometry((QApplication::desktop()->width()-w)/4, (QApplication::desktop()->height()-h)/2, w, h);
    //setMaximumSize(QSize(width(), height()));
    //setMinimumSize(QSize(width(), height()));

    // 窗口标题
    setTitle("Bresenham");
    setIcon(QIcon::fromTheme("show_table_column"));
}

void MainWindow::exposeEvent(QExposeEvent *)
{
    // 窗口显示时进行渲染
    if(isExposed())
        renderNow();
}

void MainWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    // 窗口调整大小后重新渲染
    m_backingStore->resize(resizeEvent->size());
    if(isExposed())
        renderNow();
}

// 画线
void BresenhamLine(int x0, int y0, int x1, int y1, QPainter *p)
{
    int x, y, dx, dy, d;
    x = x0;
    y = y0;
    dx = x1 - x0;
    dy = y1 - y0;
    d = -dx;
    for(;x <= x1;x++)
    {
        p->fillRect(x, y, 1, 1, Qt::white);
        d = d + 2 * dy;
        if(d > 0)
        {
            y++;
            d = d - 2 * dx;
        }
    }
}

// 画圆
void BresenhamCircle(int r, QPainter *p)
{
    int x, y, d;
    x = 0;
    y = r;
    d = 3 - 2 * r;
    for(;x < y;x++)
    {
        p->fillRect(x, y, 1, 1, Qt::white);
        if(d < 0)
            d = d + 4 * x + 6;
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
    }
}

// 画椭圆
void BresenhamEllipse(int a, int b, QPainter *p)
{
    int x, y;
    double d;
    x = 0;
    y = b;
    d = b*b + a*a * (0.25 - b);
    for(;b*b*(x+1) < a*a*(y-0.5);x++)
    {
        p->fillRect(x, y, 1, 1, Qt::white);
        if(d <= 0)
        {
            d = d + b*b*(2*x+3);
        }
        else
        {
            d = d + b*b*(2*x+3)+a*a*(2-2*y);
            y--;
        }
    }
    d = b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
    for(;y >= 0;y--)
    {
        p->fillRect(x, y, 1, 1, Qt::white);
        if(d <= 0)
        {
            d = d + b*b*(2*x+2)+a*a*(3-2*y);
            x++;
        }
        else
        {
            d = d + a*a*(3-2*y);
        }
    }
}

// 画抛物线
void BresenhamXX(double a, int h, QPainter *p)
{
    int x, y;
    double d;
    x = 0;
    y = 0;
    d = 0.5 - a;
    for(;2*a*x < 1;x++)
    {
        p->fillRect(x, y, 1, 1, Qt::white);
        if(d <= 0)
        {
            d = d - a*(2*x+3)+1;
            y++;
        }
        else
        {
            d = d - a*(2*x+3);
        }
    }
    d = y + 1 - a*(0.5+x)*(0.5+x);
    for(;y <= h;y++)
    {
        p->fillRect(x, y, 1, 1, Qt::white);
        if(d <= 0)
        {
            d = d + 1;
        }
        else
        {
            d = d - 2*a*(x+1)+1;
            x++;
        }
    }
}

// 画正弦
void BresenhamSin(double a, int w, QPainter *p)
{
    int x, y;
    double d;
    x = 0;
    y = 0;
    d = 0.5 - a*sin(1/a);
    for(;x < a*acos(-1)/2&&y <= w;x++)
    {
        p->fillRect(x, y, 1, 1, Qt::white);
        if(d <= 0)
        {
            //d = d + a*(sin((x+1)/a)-sin((x+2)/a))+1;
            d = d + a*(2*cos((2*x+3)/2.0/a)*sin(-1.0/2/a))+1;
            y++;
        }
        else
        {
            //d = d + a*(sin((x+1)/a)-sin((x+2)/a));
            d = d + a*(2*cos((2*x+3)/2.0/a)*sin(-1.0/2/a));
        }
    }
}

void MainWindow::renderNow()
{
    // 窗口隐藏时不渲染
    if(!isExposed())
        return;

    // 创建画布，大小为窗口大小
    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    // 在画布上创建画笔
    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    // 灰色背景
    painter.fillRect(0, 0, width(), height(), QColor("#31363b"));

    // 绘制表格
    painter.setPen(Qt::black);
    int i, j;
    for(i = 0;i <= height();i+=unit)
        painter.drawLine(0, i, width(), i);
    for(j = 0;j <= width();j+=unit)
        painter.drawLine(j, 0, j, height());

    // 绘制坐标轴
    painter.setPen(Qt::white);
    painter.drawLine(0, ((i/unit)%2==0?i/2+unit/2:i/2), width(), ((i/unit)%2==0?i/2+unit/2:i/2));
    painter.drawLine(((j/unit)%2==0?j/2-unit/2:j/2), 0, ((j/unit)%2==0?j/2-unit/2:j/2), height());
    painter.translate(((j/unit)%2==0?j/2-unit/2:j/2)-unit/2, ((i/unit)%2==0?i/2+unit/2:i/2)+unit/2);
    painter.scale(unit, -unit);

    BresenhamLine(-100/unit, -100/unit, 200/unit, 100/unit, &painter);
    BresenhamCircle(200/unit, &painter);
    BresenhamEllipse(200/unit, 100/unit, &painter);
    BresenhamXX(1.0/16*10/unit, height()/unit/2, &painter);
    BresenhamSin(16*10/unit, width()/unit/2, &painter);

    painter.setPen(QPen(Qt::red, 0));
    painter.drawLine(QPointF(-100/unit+0.5, -100/unit+0.5), QPointF(200/unit+0.5, 100/unit+0.5));
    painter.drawEllipse(QRectF(-200/unit+0.5, -200/unit+0.5, 400/unit, 400/unit));
    painter.drawEllipse(QRectF(-200/unit+0.5, -100/unit+0.5, 400/unit, 200/unit));
    for(i = 0;2*1.0/16*i < 1;i++)
    {
        double y = 1.0/16*i*i;
        if(abs(y-int(y)) <= 0.5)
        {
            painter.fillRect(QRectF(i+0.25, int(y)+0.25, 0.5, 0.5), Qt::red);
        }
        else
        {
            painter.fillRect(QRectF(i+0.25, int(y)+1.25, 0.5, 0.5), Qt::red);
        }
    }
    for(i = int(1.0/16*i*i);i <= height()/unit/2;i++)
    {
        double x = sqrt(i*16);
        if(x > width()/unit/2) break;
        if(abs(x-int(x)) <= 0.5)
        {
            painter.fillRect(QRectF(int(x)+0.25, i+0.25, 0.5, 0.5), Qt::red);
        }
        else
        {
            painter.fillRect(QRectF(int(x)+1.25, i+0.25, 0.5, 0.5), Qt::red);
        }
    }

    for(i = 0;i <= 8*acos(-1);i++)
    {
        double y = 16.0*sin(1.0*i/16);
        if(abs(y-int(y)) <= 0.5)
        {
            painter.fillRect(QRectF(i+0.25, int(y)+0.25, 0.5, 0.5), Qt::red);
        }
        else
        {
            painter.fillRect(QRectF(i+0.25, int(y)+1.25, 0.5, 0.5), Qt::red);
        }
    }

    // 渲染结束
    painter.end();
    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}

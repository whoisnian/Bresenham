#include "ui_canvas.h"
#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>
#include <cmath>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
    type = 0;
    originColor = Qt::red;
    bresenhamColor = Qt::green;
    centerX = 0;
    centerY = 0;
    unit = 4;
    tran = false;
    calcTime = false;
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::setBar(QStatusBar *bar)
{
    statusbar = bar;
}

void Canvas::setType(int t)
{
    statusbar->clearMessage();
    statusbar->showMessage(QString("绘制中 。。。"));
    type = t;
    calcTime = true;
    this->update();
}

void Canvas::originLine(int x0, int y0, int x1, int y1, QPainter *p)
{
    int x, y;
    double res;
    for(x = x0;x <= x1;x++)
    {
        res = 1.0*(y1-y0)*(x-x0)/(x1-x0)+y0;
        if(abs(res-int(res)) <= 0.5)
            y = int(res);
        else
            y = int(res)+(res>=0?1:-1);
        p->fillRect(x, y, 1, 1, originColor);
    }
}

void Canvas::bresenhamLine(int x0, int y0, int x1, int y1, QPainter *p)
{
    int x = x0, y = y0, dx, dy, d;
    dx = x1 - x0;
    dy = y1 - y0;
    d = -dx;
    for(;x <= x1;x++)
    {
        p->fillRect(x, y, 1, 1, bresenhamColor);
        d = d + 2 * dy;
        if(d > 0)
        {
            y++;
            d = d - 2 * dx;
        }
    }
}

void Canvas::originCircle(int r, QPainter *p)
{
    int x = 0, y = r;
    double res = r;
    for(x = 0;x <= res;x++)
    {
        res = sqrt(r*r-x*x);
        if(abs(res-int(res)) <= 0.5)
            y = int(res);
        else
            y = int(res)+(res>=0?1:-1);
        p->fillRect(x, y, 1, 1, originColor);
        p->fillRect(x, -y, 1, 1, originColor);
        p->fillRect(-x, y, 1, 1, originColor);
        p->fillRect(-x, -y, 1, 1, originColor);
        p->fillRect(y, x, 1, 1, originColor);
        p->fillRect(y, -x, 1, 1, originColor);
        p->fillRect(-y, x, 1, 1, originColor);
        p->fillRect(-y, -x, 1, 1, originColor);
    }
}

void Canvas::bresenhamCircle(int r, QPainter *p)
{
    int x = 0, y = r, d = 3 - 2 * r;
    for(;x < y;x++)
    {
        p->fillRect(x, y, 1, 1, bresenhamColor);
        p->fillRect(x, -y, 1, 1, bresenhamColor);
        p->fillRect(-x, y, 1, 1, bresenhamColor);
        p->fillRect(-x, -y, 1, 1, bresenhamColor);
        p->fillRect(y, x, 1, 1, bresenhamColor);
        p->fillRect(y, -x, 1, 1, bresenhamColor);
        p->fillRect(-y, x, 1, 1, bresenhamColor);
        p->fillRect(-y, -x, 1, 1, bresenhamColor);
        if(d < 0)
            d = d + 4 * x + 6;
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
    }
}

void Canvas::originEllipse(int a, int b, QPainter *p)
{
    int x = 0, y = b;
    double res = b;
    for(x = 0;b*b*x <= a*a*res;x++)
    {
        res = sqrt((a*a*b*b-b*b*x*x)/a/a);
        if(abs(res-int(res)) <= 0.5)
            y = int(res);
        else
            y = int(res)+(res>=0?1:-1);
        p->fillRect(x, y, 1, 1, originColor);
        p->fillRect(x, -y, 1, 1, originColor);
        p->fillRect(-x, y, 1, 1, originColor);
        p->fillRect(-x, -y, 1, 1, originColor);
    }
    for(;y >= 0;y--)
    {
        res = sqrt((a*a*b*b-a*a*y*y)/b/b);
        if(abs(res-int(res)) <= 0.5)
            x = int(res);
        else
            x = int(res)+(res>=0?1:-1);
        p->fillRect(x, y, 1, 1, originColor);
        p->fillRect(x, -y, 1, 1, originColor);
        p->fillRect(-x, y, 1, 1, originColor);
        p->fillRect(-x, -y, 1, 1, originColor);
    }
}

void Canvas::bresenhamEllipse(int a, int b, QPainter *p)
{
    int x = 0, y = b;
    double d = b*b + a*a * (0.25 - b);
    for(;b*b*(x+1) <= a*a*(y-0.5);x++)
    {
        p->fillRect(x, y, 1, 1, bresenhamColor);
        p->fillRect(x, -y, 1, 1, bresenhamColor);
        p->fillRect(-x, y, 1, 1, bresenhamColor);
        p->fillRect(-x, -y, 1, 1, bresenhamColor);
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
        p->fillRect(x, y, 1, 1, bresenhamColor);
        p->fillRect(x, -y, 1, 1, bresenhamColor);
        p->fillRect(-x, y, 1, 1, bresenhamColor);
        p->fillRect(-x, -y, 1, 1, bresenhamColor);
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

void Canvas::originParabola(int a, int h, QPainter *p)
{
    int x = 0, y = 0;
    double res = 0;
    for(x = 0;2*x <= a;x++)
    {
        res = x*x/a;
        if(abs(res-int(res)) <= 0.5)
            y = int(res);
        else
            y = int(res)+(res>=0?1:-1);
        p->fillRect(x, y, 1, 1, originColor);
        p->fillRect(-x, y, 1, 1, originColor);
    }
    for(;y <= h;y++)
    {
        res = sqrt(y*a);
        if(abs(res-int(res)) <= 0.5)
            x = int(res);
        else
            x = int(res)+(res>=0?1:-1);
        p->fillRect(x, y, 1, 1, originColor);
        p->fillRect(-x, y, 1, 1, originColor);
    }
}

void Canvas::bresenhamParabola(int a, int h, QPainter *p)
{
    int x = 0, y = 0;
    double d = 0.5 * a - 1.0;
    for(;2*x < a;x++)
    {
        p->fillRect(x, y, 1, 1, bresenhamColor);
        p->fillRect(-x, y, 1, 1, bresenhamColor);
        if(d <= 0)
        {
            d = d - (2*x+3)+a;
            y++;
        }
        else
        {
            d = d - (2*x+3);
        }
    }
    d = a*(y + 1) - (0.5+x)*(0.5+x);
    for(;y <= h;y++)
    {
        p->fillRect(x, y, 1, 1, bresenhamColor);
        p->fillRect(-x, y, 1, 1, bresenhamColor);
        if(d <= 0)
        {
            d = d + a;
        }
        else
        {
            d = d - 2*(x+1)+a;
            x++;
        }
    }
}

void Canvas::originSin(int a, int w, QPainter *p)
{
    int x = 0, y = 0;
    double res = 0;
    for(x = 0;x <= w;x++)
    {
        res = a*sin(x*1.0/a);
        if(abs(res-int(res)) <= 0.5)
            y = int(res);
        else
            y = int(res)+(res>=0?1:-1);
        p->fillRect(x, y, 1, 1, originColor);
        p->fillRect(-x, -y, 1, 1, originColor);
    }
}

void Canvas::bresenhamSin(int a, int w, QPainter *p)
{
    int x = 0, y = 0, i = 0;
    double d = 0;
    while(x <= w)
    {
        d = y + 0.5 - a*sin((x+1)*1.0/a);
        for(;x < 2*i*a*acos(-1)+a*acos(-1)*1.0/2&&x <= w;x++)
        {
            p->fillRect(x, y, 1, 1, bresenhamColor);
            p->fillRect(-x, -y, 1, 1, bresenhamColor);
            if(d <= 0)
            {
                d = d + a*(sin((x+1)*1.0/a)-sin((x+2)*1.0/a))+1;
                y++;
            }
            else
            {
                d = d + a*(sin((x+1)*1.0/a)-sin((x+2)*1.0/a));
            }
        }
        d = y - 0.5 - a*sin((x+1)*1.0/a);
        for(;x < 2*i*a*acos(-1)+a*acos(-1)*3.0/2&&x <= w;x++)
        {
            p->fillRect(x, y, 1, 1, bresenhamColor);
            p->fillRect(-x, -y, 1, 1, bresenhamColor);
            if(d <= 0)
            {
                d = d + a*(sin((x+1)*1.0/a)-sin((x+2)*1.0/a));
            }
            else
            {
                d = d + a*(sin((x+1)*1.0/a)-sin((x+2)*1.0/a))-1;
                y--;
            }
        }
        i++;
    }
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 灰色背景
    painter.fillRect(0, 0, width(), height(), QColor("#31363b"));

    // 绘制表格
    painter.setPen(Qt::black);
    int i, j;
    for(i = 0;i <= height();i+=unit)
        painter.drawLine(0, i+centerY%unit, width(), i+centerY%unit);
    for(j = 0;j <= width();j+=unit)
        painter.drawLine(j+centerX%unit, 0, j+centerX%unit, height());

    // 绘制坐标轴
    painter.setPen(Qt::white);
    painter.drawLine(0, i/2+centerY+(i/unit%2==0?unit/2:0), width(), i/2+centerY+(i/unit%2==0?unit/2:0));
    painter.drawLine(j/2+centerX+(j/unit%2==0?unit/2:0), 0, j/2+centerX+(j/unit%2==0?unit/2:0), height());
    painter.translate(j/2+centerX+(j/unit%2==0?unit:unit/2), i/2+centerY-(i/unit%2==0?0:unit/2));
    painter.scale(unit, -unit);

    // 根据选项绘图
    clock_t t1 = 0, t2 = 0;
    int times;
    if(calcTime)
        times = 100000;
    else
        times = 1;
    switch(type)
    {
    // y=0.2x+10 即从(-250, -40)到(250, 60)
    case 1:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->originLine(-250, -40, 250, 60, &painter);
        t2 = clock();
        break;
    case 2:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->bresenhamLine(-250, -40, 250, 60, &painter);
        t2 = clock();
        break;
    // x^2+y^2=50^2
    case 3:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->originCircle(50, &painter);
        t2 = clock();
        break;
    case 4:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->bresenhamCircle(50, &painter);
        t2 = clock();
        break;
    // x^2/50^2+y^2/20^2=1
    case 5:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->originEllipse(50, 20, &painter);
        t2 = clock();
        break;
    case 6:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->bresenhamEllipse(50, 20, &painter);
        t2 = clock();
        break;
    // y=x^2/16
    case 7:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->originParabola(16, 250, &painter);
        t2 = clock();
        break;
    case 8:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->bresenhamParabola(16, 250, &painter);
        t2 = clock();
        break;
    // y=16sin(x/16)
    case 9:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->originSin(16, 250, &painter);
        t2 = clock();
        break;
    case 10:
        t1 = clock();
        for(int i = 0;i < times;i++)
            this->bresenhamSin(16, 250, &painter);
        t2 = clock();
        break;
    default:
        type = 0;
    }
    painter.end();

    if(type != 0&&calcTime)
    {
        statusbar->clearMessage();
        statusbar->showMessage(QString("平均耗时：") + QString::number(1.0*(t2-t1)*1000/times/CLOCKS_PER_SEC) + QString(" ms"), 5000);
    }
    calcTime = false;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        oriX = event->pos().x();
        oriY = event->pos().y();
        tran = true;
    }
    else if(event->button() == Qt::RightButton)
    {
        type = 0;
        centerX = 0;
        centerY = 0;
        unit = 4;
        tran = false;
        calcTime = false;
        this->update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        tran = false;
        this->update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(tran)
    {
        nowX = event->pos().x();
        nowY = event->pos().y();
        centerX += nowX-oriX;
        centerY += nowY-oriY;
        oriX = event->pos().x();
        oriY = event->pos().y();
        this->update();
    }
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0&&unit < 10)
    {
        unit += 1;
    }
    else if(event->delta() < 0&&unit > 1)
    {
        unit -= 1;
    }
    this->update();
}

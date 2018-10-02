#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QStatusBar>

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    // 设定主程序状态栏
    void setBar(QStatusBar *bar);
    // 设定绘图方式
    void setType(int t);

private:
    Ui::Canvas *ui;
    QStatusBar *statusbar;
    // 直接计算时图像颜色
    QColor originColor;
    // 算法优化时图像颜色
    QColor bresenhamColor;
    // 用于计算鼠标拖动时的偏移量
    int oriX, oriY, nowX, nowY, centerX, centerY;
    // 单元格大小
    int unit;
    // 鼠标拖动中
    bool tran;
    // 需要计算绘图时间
    bool calcTime;
    // 绘图方式
    int type;
    /*
     *  type number
     *
     *  0: none
     *  1: line_ori
     *  2: line_bresenham
     *  3: circle_ori
     *  4: circle_bresenham
     *  5: ellipse_ori
     *  6: ellipse_bresenham
     *  7: parabola_ori
     *  8: parabola_bresenham
     *  9: sin_ori
     * 10: sin_bresenham
     */

    void originLine(int x0, int y0, int x1, int y1, QPainter *p);
    void bresenhamLine(int x0, int y0, int x1, int y1, QPainter *p);
    void originCircle(int r, QPainter *p);
    void bresenhamCircle(int r, QPainter *p);
    void originEllipse(int a, int b, QPainter *p);
    void bresenhamEllipse(int a, int b, QPainter *p);
    void originParabola(int a, int h, QPainter *p);
    void bresenhamParabola(int a, int h, QPainter *p);
    void originSin(int a, int w, QPainter *p);
    void bresenhamSin(int a, int w, QPainter *p);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif // CANVAS_H

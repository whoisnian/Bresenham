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

    void setBar(QStatusBar *bar);
    void setType(int t);

private:
    Ui::Canvas *ui;
    QStatusBar *statusbar;
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
};

#endif // CANVAS_H

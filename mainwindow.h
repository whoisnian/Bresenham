#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QtGui>

class MainWindow : public QWindow
{
    Q_OBJECT
public:
    MainWindow(QWindow *parent = 0);
    void renderNow();

protected:
    void exposeEvent(QExposeEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QBackingStore *m_backingStore;
    int unit;
};

#endif // MAINWINDOW_H

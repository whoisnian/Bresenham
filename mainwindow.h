#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_line_1_clicked();

    void on_pushButton_line_2_clicked();

    void on_pushButton_circle_1_clicked();

    void on_pushButton_circle_2_clicked();

    void on_pushButton_ellipse_1_clicked();

    void on_pushButton_ellipse_2_clicked();

    void on_pushButton_parabola_1_clicked();

    void on_pushButton_parabola_2_clicked();

    void on_pushButton_sin_1_clicked();

    void on_pushButton_sin_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

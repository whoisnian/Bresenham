#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_canvas->setBar(ui->statusBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_line_1_clicked()
{
    ui->widget_canvas->setType(1);
}

void MainWindow::on_pushButton_line_2_clicked()
{
    ui->widget_canvas->setType(2);
}

void MainWindow::on_pushButton_circle_1_clicked()
{
    ui->widget_canvas->setType(3);
}

void MainWindow::on_pushButton_circle_2_clicked()
{
    ui->widget_canvas->setType(4);
}

void MainWindow::on_pushButton_ellipse_1_clicked()
{
    ui->widget_canvas->setType(5);
}

void MainWindow::on_pushButton_ellipse_2_clicked()
{
    ui->widget_canvas->setType(6);
}

void MainWindow::on_pushButton_parabola_1_clicked()
{
    ui->widget_canvas->setType(7);
}

void MainWindow::on_pushButton_parabola_2_clicked()
{
    ui->widget_canvas->setType(8);
}

void MainWindow::on_pushButton_sin_1_clicked()
{
    ui->widget_canvas->setType(9);
}

void MainWindow::on_pushButton_sin_2_clicked()
{
    ui->widget_canvas->setType(10);
}

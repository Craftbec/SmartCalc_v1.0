#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QtCharts/QSplineSeries>
#include <QtGui>

extern "C" {
#include "../calc.h"
#include "../chek.h"
#include "../pars.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void drawGraph(
      bool notEmpty = 0);  // функция, отвечающая за отрисовку графика
  void drawGraph2(
      bool notEmpty = 0);  // функция, отвечающая за отрисовку графика
  void recountPixels();  // в зависимости от точности (об этом позже) считаем
                         // количество пикселей на один условный сантиметр
  void getData();  // получаем значения границ графика и точности
  QChart *chart;
  QSplineSeries *series1;
  QSplineSeries *series2;
  void drawLine();
  void initChart();

 private:
  Ui::MainWindow *ui;
  double minX, maxX, minY, maxY;
  double onePixelX, onePixelY;  // количество пикселей на шаг
  double Ox, Oy;                // координаты центра
  int pictWidth, pictHeight;  // ширина и высота картинки

 private slots:
  void digits();

  // private slots:
  //     void doub();

 private slots:
  void equal_click();

  // private slots:
  //     void on_button_dot_clicked();

  void on_pushButton_clicked();

  void on_GRAf_clicked();
  //   void getData();
  //   void recountPixels();
  //   void drawGraph(bool notEmpty);
  void on_AC_clicked();
};
#endif  // MAINWINDOW_H

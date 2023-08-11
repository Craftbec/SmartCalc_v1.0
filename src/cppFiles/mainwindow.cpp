#include "mainwindow.h"

#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->_0, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->_1, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->_2, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->_3, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->_4, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->_5, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->_6, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->_7, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->_8, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->_9, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->del, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->skobka_o, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->skobka_z, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->sub, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->tochka, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->stepen, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->xxx, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->AC, SIGNAL(clicked()), this, SLOT(on_AC_clicked()));
  connect(ui->ravno, SIGNAL(clicked()), this, SLOT(equal_click()));
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "(x)") {
    ui->label->setText(ui->label->text() + 'x');
  } else if (button->text() == "xʸ ") {
    ui->label->setText(ui->label->text() + '^');
  } else if (button->text() == "÷") {
    ui->label->setText(ui->label->text() + '/');
  } else if (button->text() == "mod") {
    ui->label->setText(ui->label->text() + '%');
  } else if (button->text() == "√ x") {
    ui->label->setText(ui->label->text() + 's' + 'q' + 'r' + 't' + '(');
  } else if (button->text() == "cos" || button->text() == "sin" ||
             button->text() == "tan" || button->text() == "log" ||
             button->text() == "ln" || button->text() == "acos" ||
             button->text() == "asin" || button->text() == "atan") {
    ui->label->setText(ui->label->text() + button->text() + '(');
  } else {
    ui->label->setText(ui->label->text() + button->text());
  }
}

void MainWindow::equal_click() {
  QString new_label = ui->label->text();
  std::string str = new_label.toStdString();
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  QByteArray strx = ui->doubleSpinBox->text().toLocal8Bit();
  char *c_str2 = strx.data();
  char *res = is_x(cstr, c_str2);
  res = calculate(cstr);
  std::string res_str(res);
  if (strcmp(res, "Incorrect expression")) free_str(res);
  QString label = QString::fromStdString(res_str);
  ui->label->setText(label);
  delete[] cstr;
}

void MainWindow::on_pushButton_clicked() {
  QString new_label = ui->label->text();
  QByteArray ba = new_label.toLocal8Bit();
  char *c_str2 = ba.data();
  c_str2 = min_unar(c_str2);
  QString label = QString::fromStdString(c_str2);
  ui->label->setText(label);
}

void MainWindow::on_GRAf_clicked() {
  getData();
  recountPixels();
  drawGraph(1);
}

void MainWindow::getData() {
  minX = ui->doubleSpinBox_2->value();
  maxX = ui->doubleSpinBox_3->value();
  minY = ui->doubleSpinBox_4->value();
  maxY = ui->doubleSpinBox_5->value();
  if (minX >= maxX) {
    minX = -10;
    maxX = 10;
    ui->doubleSpinBox_2->setValue(-10);
    ui->doubleSpinBox_3->setValue(10);
  }
  if (minY >= maxY) {
    minY = -10;
    maxY = 10;
    ui->doubleSpinBox_4->setValue(-10);
    ui->doubleSpinBox_5->setValue(10);
  }
}

void MainWindow::recountPixels() {
  onePixelX = 411.0 / (maxX - minX);
  onePixelY = 291.0 / (maxY - minY);
  Ox = fabs(minX);
  Oy = maxY;
}

void MainWindow::drawGraph(bool notEmpty) {
  char c_str2[256] = {0};
  pictHeight = 291;
  pictWidth = 411;
  QPixmap graph(411, 291);
  QPainter paint;
  paint.begin(&graph);
  paint.eraseRect(0, 0, 411, 291);
  paint.drawLine(Ox * onePixelX, 0, Ox * onePixelX, pictHeight);
  paint.drawLine(0, Oy * onePixelY, pictWidth, Oy * onePixelY);
  paint.setPen(QPen(Qt::black, 3));
  for (int i = minX; i <= maxX; i += 1.0)
    paint.drawPoint((i + Ox) * onePixelX, Oy * onePixelY);
  for (int i = minY; i <= maxY; i += 1.0)
    paint.drawPoint(Ox * onePixelX, (i + Oy) * onePixelY);
  QPainterPath path;
  double step = (maxX - minX) * 0.001;
  for (double X = minX; X <= maxX; X += step) {
    QByteArray ba = ui->label->text().toLocal8Bit();
    char *c_str = ba.data();
    sprintf(c_str2, "%.3f", X);
    char *result = is_x(c_str, c_str2);
    result = calculate(result);
    double Y = atof(result);
    Y = Y * (-1.0);
    paint.drawPoint((X + Ox) * onePixelX, (Y + Oy) * onePixelY);
    paint.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    paint.drawPath(path);
  }
  paint.end();
  ui->label_2->setPixmap(graph);
  return;
}

void MainWindow::drawGraph2(bool notEmpty) {
  QPixmap graph(411, 291);
  QPainter paint;
  paint.begin(&graph);
  paint.eraseRect(0, 0, 411, 291);
  paint.end();
  ui->label_2->setPixmap(graph);
  return;
}

void MainWindow::on_AC_clicked() {
  ui->label->setText("");
  recountPixels();
  drawGraph2();
}

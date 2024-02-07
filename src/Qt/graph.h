#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QWidget>
// #include "mainwindow.h"

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

  // private slots:
 public slots:
  void on_pushButton_clicked();
  void slot(QString input);

 private:
  Ui::Graph *ui;
  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;

  // public slots:
};

#endif  // GRAPH_H

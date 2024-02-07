#include "graph.h"

#include "mainwindow.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

int valid_int(char *input) {
  int res = 0;
  int flag_non_valid = 0;
  for (size_t i = 0; i < strlen(input); i++) {
    if (!is_number(input[i]) && input[i] != '-') {
      flag_non_valid = 1;
    }
  }
  if (!flag_non_valid) {
    res = 1;
  }
  return res;
}

int valid_string(QString input) {
  int res = 0;
  int flag_empty = 0;
  int flag_large = 0;

  if (input.length() == 0) {
    flag_empty = 1;
  }
  if (input.length() > 9) {
    flag_large = 1;
  }

  if (!flag_empty && !flag_large) {
    char *int_input = input.toUtf8().data();
    if (valid_int(int_input) == 1) {
      res = 1;
    }
  }

  return res;
}

int valid_cord(int min, int max) {
  int res = 0;
  if (min < max)
    if (max >= -1000000 && max <= 1000000)
      if (min >= -1000000 && min <= 1000000) res = 1;
  return res;
}

void Graph::on_pushButton_clicked() {
  // printf("%s\n", input_str);

  int flag_valid_cord = 0, flag_ok = 0;
  int x_min, x_max, y_min, y_max;
  QString x_min_text = ui->lineEdit->text();
  QString x_max_text = ui->lineEdit_2->text();
  QString y_min_text = ui->lineEdit_3->text();
  QString y_max_text = ui->lineEdit_4->text();
  if (valid_string(x_min_text) && valid_string(x_max_text) &&
      valid_string(y_min_text) && valid_string(y_max_text)) {
    if (valid_cord(x_min_text.toInt(), x_max_text.toInt()) &&
        valid_cord(y_min_text.toInt(), y_max_text.toInt()))
      flag_valid_cord = 1;
  }

  if (flag_valid_cord) {
    ui->label_5->setText("");
    x_min = x_min_text.toInt();
    x_max = x_max_text.toInt();
    y_min = y_min_text.toInt();
    y_max = y_max_text.toInt();

    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min, y_max);

    double X = 0, Y = 0, h = 0.1;
    if (x_max - x_min >= 200) h = 1;

    if (x_max - x_min >= 10000) h = 2;

    if (x_max - x_min >= 100000) h = 4;

    //    if (x_max-x_min >=200000)
    //    h = 8;

    // printf("%s\n", input_str);

    QString input_text = ui->label_7->text();
    //    char *input_str = input_text.toUtf8().data();
    ui->widget->clearGraphs();
    x.clear();
    y.clear();
    for (X = x_min; X < x_max; X += h) {
      char *input_str = input_text.toUtf8().data();
      flag_ok = final_func(input_str, &Y, X);
      if (flag_ok == 1) {
        x.push_back(X);
        y.push_back(Y);
      }
    }

    // for (X = -2; X < 4; X+=h) {
    //     x.push_back(X);
    //     y.push_back(X*X);
    // }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();

    // ui->widget->xAxis->setRange(-10, 10);

  } else {
    ui->label_5->setText("Incorrect cords");
  }
}

void Graph::slot(QString input) { ui->label_7->setText(input); }

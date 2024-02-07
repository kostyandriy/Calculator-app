#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  form = new (Form);
  graph = new (Graph);

  connect(this, &MainWindow::signal, graph, &Graph::slot);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_33_clicked() {
  int flag_empty = 0;
  int flag_large = 0;

  QString text = ui->lineEdit_2->text();
  if (text.length() == 0) {
    flag_empty = 1;
  }
  if (text.length() > MAX_SIZE_STRING) {
    flag_large = 1;
  }

  if (!flag_empty && !flag_large) {
    char *input = text.toUtf8().data();
    char res[MAX_SIZE_STRING] = "";
    trim_input(input, res);
    if (valid_input(res)) {
      graph->show();
      emit signal(text);
      // peredat res kakto
    } else {
      ui->label_2->setText("Incorrect input");
    }
  }
  if (flag_empty) {
    ui->label_2->setText("Empty input");
  }
  if (flag_large) {
    ui->label_2->setText("Too large input");
  }

  // graph->show();
}

void MainWindow::on_pushButton_31_clicked() { form->show(); }

void MainWindow::on_pushButton_18_clicked() {
  QString symbolToAdd = "1";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_19_clicked() {
  QString symbolToAdd = "2";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_28_clicked() {
  QString symbolToAdd = "3";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_14_clicked() {
  QString symbolToAdd = "4";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_12_clicked() {
  QString symbolToAdd = "5";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_24_clicked() {
  QString symbolToAdd = "6";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_13_clicked() {
  QString symbolToAdd = "7";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_15_clicked() {
  QString symbolToAdd = "8";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_23_clicked() {
  QString symbolToAdd = "9";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_20_clicked() {
  QString symbolToAdd = "0";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_17_clicked() {
  QString symbolToAdd = "(";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_16_clicked() {
  QString symbolToAdd = ")";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_25_clicked() {
  QString symbolToAdd = "*";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_22_clicked() {
  QString symbolToAdd = "/";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_29_clicked() {
  QString symbolToAdd = "-";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_21_clicked() {
  QString symbolToAdd = "+";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_32_clicked() {
  QString symbolToAdd = "x";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_10_clicked() {
  QString symbolToAdd = "^";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + symbolToAdd);
}

void MainWindow::on_pushButton_clicked() {
  QString textToAdd = "sin";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_2_clicked() {
  QString textToAdd = "cos";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_3_clicked() {
  QString textToAdd = "tan";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_4_clicked() {
  QString textToAdd = "asin";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_5_clicked() {
  QString textToAdd = "acos";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_6_clicked() {
  QString textToAdd = "atan";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_7_clicked() {
  QString textToAdd = "ln";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_8_clicked() {
  QString textToAdd = "log";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_9_clicked() {
  QString textToAdd = "sqrt";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_30_clicked() {
  QString textToAdd = "mod";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_34_clicked() {
  QString textToAdd = ".";
  ui->lineEdit_2->setText(ui->lineEdit_2->text() + textToAdd);
}

void MainWindow::on_pushButton_27_clicked() { ui->lineEdit_2->backspace(); }

void MainWindow::on_pushButton_26_clicked() { ui->lineEdit_2->clear(); }

int valid_x(char *input) {
  int res = 0;
  int len = strlen(input);
  int flag_not_valid_symb = 0;

  for (int i = 0; i < len && !flag_not_valid_symb; i++) {
    if (i == 0 && input[i] == '-') i++;
    if (!is_number(input[i]) && !is_dot(input, i)) flag_not_valid_symb = 1;
  }

  if (!flag_not_valid_symb && valid_number(input)) res = 1;
  return res;
}

void MainWindow::on_pushButton_35_clicked() {
  int flag_x_empty = 0;
  int flag_x_large = 0;
  //    int flag_x_all = 0;
  //    int flag_x_valid = 0;

  QString x_text = ui->lineEdit->text();
  if (x_text.length() == 0) {
    flag_x_empty = 1;
  }
  if (x_text.length() > MAX_SIZE_STRING) {
    flag_x_large = 1;
  }

  if (!flag_x_empty && !flag_x_large) {
    char *x_input = x_text.toUtf8().data();
    if (valid_x(x_input) == 1) {
      ui->label->setText(x_text);
    } else {
      ui->label_2->setText("Incorrect x input, x was not set");
    }
  }

  if (flag_x_empty) {
    ui->label_2->setText("Empty x input, x was not set");
  }
  if (flag_x_large) {
    ui->label_2->setText("Too large x input, x was not set");
  }
}

void MainWindow::on_pushButton_11_clicked() {
  int flag_empty = 0;
  int flag_large = 0;

  QString value_x = ui->label->text();
  double x = value_x.toDouble();

  QString text = ui->lineEdit_2->text();
  if (text.length() == 0) {
    flag_empty = 1;
  }
  if (text.length() > MAX_SIZE_STRING) {
    flag_large = 1;
  }

  if (!flag_empty && !flag_large) {
    char *input = text.toUtf8().data();
    double result = 0;
    int flag = final_func(input, &result, x);
    if (flag == 1) {
      ui->label_2->setText(QString::number(result, 'f', 8));
    }
    if (flag == -1) {
      ui->label_2->setText("Error in calculation");
    }
    if (flag == -2) {
      ui->label_2->setText("Error in input");
    }
  }
  if (flag_empty) {
    ui->label_2->setText("Empty input");
  }
  if (flag_large) {
    ui->label_2->setText("Too large input");
  }
}

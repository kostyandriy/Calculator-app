#include "form.h"

#include "mainwindow.h"
#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
}

Form::~Form() { delete ui; }

int valid_unsigned_int(char *input) {
  int res = 0;
  int flag_non_valid = 0;
  for (size_t i = 0; i < strlen(input); i++) {
    if (!is_number(input[i])) {
      flag_non_valid = 1;
    }
  }
  if (!flag_non_valid) {
    res = 1;
  }
  return res;
}

int valid_precent(QString text) {
  int res = 0;
  int flag_empty = 0, flag_large = 0;
  if (text.length() == 0) {
    flag_empty = 1;
  }
  if (text.length() > 100) {
    flag_large = 1;
  }
  if (!flag_empty && !flag_large) {
    char *input = text.toUtf8().data();
    if (valid_number(input) == 1) {
      int value = text.toInt();
      if (value >= 0 && value <= 100) res = 1;
    }
  }
  return res;
}

int valid_time(QString text) {
  int res = 0;
  int flag_empty = 0, flag_large = 0;
  if (text.length() == 0) {
    flag_empty = 1;
  }
  if (text.length() > 4) {
    flag_large = 1;
  }
  if (!flag_empty && !flag_large) {
    char *input = text.toUtf8().data();
    if (valid_unsigned_int(input) == 1) {
      int value = text.toInt();
      if (value > 0 && value <= 1200) res = 1;
    }
  }
  return res;
}

int valid_sum(QString text) {
  int res = 0;
  int flag_empty = 0, flag_large = 0;
  if (text.length() == 0) {
    flag_empty = 1;
  }
  if (text.length() > 9) {
    flag_large = 1;
  }
  if (!flag_empty && !flag_large) {
    char *input = text.toUtf8().data();
    if (valid_number(input) == 1) {
      int value = text.toInt();
      if (value > 0 && value <= 100000000) res = 1;
    }
  }
  return res;
}

void Form::on_pushButton_clicked() {
  QString precent = ui->lineEdit_3->text();
  QString sum = ui->lineEdit->text();
  QString time = ui->lineEdit_2->text();

  if (valid_precent(precent) && valid_sum(sum) && valid_time(time)) {
    ui->label_17->setText("");
    double payment = 0, diff = 0, total = 0;
    double sum_ready = sum.toDouble();
    int time_ready = time.toInt();
    double precent_ready = precent.toDouble();
    precent_ready = precent_ready / 1200;
    if (ui->comboBox->currentText() == "Annuitentnie") {
      payment = per_month_ann(sum_ready, precent_ready, time_ready);
      total = payment * time_ready;
      diff = total - sum_ready;
    }
    if (ui->comboBox->currentText() == "Differentials") {
      payment = per_month_diff(sum_ready, precent_ready, time_ready, &total);
      diff = total - sum_ready;
    }
    ui->label_14->setText(QString::number(payment, 'f', 2));
    ui->label_15->setText(QString::number(diff, 'f', 2));
    ui->label_16->setText(QString::number(total, 'f', 2));

  } else {
    ui->label_17->setText("Incorrect input");
  }
}

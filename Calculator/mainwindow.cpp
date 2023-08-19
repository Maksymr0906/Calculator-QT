
#include "mainwindow.h"
#include "ui_mainwindow.h"

double firstNumber{};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(addDigitToResult()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clearResult()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(addDotToResult()));
    connect(ui->pushButton_invertSign, SIGNAL(clicked()), this, SLOT(invertSign()));
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_subtract, SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(mathOperations()));
    connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(calculateResult()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addDigitToResult() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    long double number = (ui->resultShow->text() + button->text()).toDouble();
    QString result = QString::number(number, 'g', 12);

    if(ui->resultShow->text().contains(".") && button->text() == "0") {
        result = ui->resultShow->text() + button->text();
    }

    ui->resultShow->setText(result);
}

void MainWindow::clearResult() {
    firstNumber = 0;
    ui->resultShow->setText(QString("0"));

    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
}

void MainWindow::addDotToResult() {
    if(!ui->resultShow->text().contains('.')) {
        ui->resultShow->setText(ui->resultShow->text() + '.');
    }
}

void MainWindow::invertSign() {
    long double number = ui->resultShow->text().toDouble();
    number *= -1;
    ui->resultShow->setText(QString::number(number, 'g', 12));
}

void MainWindow::calculateResult() {
    double secondNumber = ui->resultShow->text().toDouble();
    double result{ui->resultShow->text().toDouble()};

    if(ui->pushButton_add->isChecked()) {
        result = firstNumber + secondNumber;
        ui->pushButton_add->setChecked(false);
    }
    else if(ui->pushButton_subtract->isChecked()) {
        result = firstNumber - secondNumber;
        ui->pushButton_subtract->setChecked(false);
    }
    else if(ui->pushButton_divide->isChecked()) {
        if(secondNumber == 0)
            result = 0;
        else
            result = firstNumber / secondNumber;
        ui->pushButton_divide->setChecked(false);
    }
    else if(ui->pushButton_multiply->isChecked()) {
        result = firstNumber * secondNumber;
        ui->pushButton_multiply->setChecked(false);
    }

    ui->resultShow->setText(QString::number(result, 'g', 12));
}

void MainWindow::mathOperations() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    button->setChecked(true);
    firstNumber = ui->resultShow->text().toDouble();
    ui->resultShow->setText(QString("0"));
}

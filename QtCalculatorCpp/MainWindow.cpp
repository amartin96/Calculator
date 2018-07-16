#include "MainWindow.h"
#include "Calculator.h"

MainWindow::MainWindow()
{
    setupUi(this);

    m_buttonValues = {
            {pushButton0, '0'},
            {pushButton1, '1'},
            {pushButton2, '2'},
            {pushButton3, '3'},
            {pushButton4, '4'},
            {pushButton5, '5'},
            {pushButton6, '6'},
            {pushButton7, '7'},
            {pushButton8, '8'},
            {pushButton9, '9'},
            {pushButtonAdd, '+'},
            {pushButtonSubtract, '-'},
            {pushButtonMultiply, '*'},
            {pushButtonDivide, '/'},
            {pushButtonLParen, '('},
            {pushButtonRParen, ')'},
            {pushButtonDecimal, '.'},
    };

    // the signal for pushButtonClear is bound from within Qt Designer (its in the UI File)
    // the other signals need to be bound manually

    connect(pushButtonEnter, &QPushButton::clicked, this, MainWindow::onEnterClicked);

    connect(pushButton0, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButton1, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButton2, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButton3, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButton4, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButton5, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButton6, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButton7, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButton8, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButton9, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButtonAdd, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButtonSubtract, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButtonMultiply, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButtonDivide, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButtonLParen, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButtonRParen, &QPushButton::clicked, this, MainWindow::onButtonClicked);
    connect(pushButtonDecimal, &QPushButton::clicked, this, MainWindow::onButtonClicked);
}

void MainWindow::onButtonClicked()
{
    label->setText(label->text() + m_buttonValues[qobject_cast<QPushButton*>(sender())]);
}

void MainWindow::onEnterClicked()
{
    label->setNum(Calculator::calculate(label->text().toStdString()));
}

#include "moc_MainWindow.cpp"
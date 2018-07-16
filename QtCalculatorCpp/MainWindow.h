#pragma once

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

private:
    QMap<QPushButton*, char> m_buttonValues;

public:
    explicit MainWindow();

private slots:
    void onButtonClicked();
    void onEnterClicked();
};

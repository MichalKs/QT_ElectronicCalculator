#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void calculateClicked(void);
    void enableCalcButton(void);
    void opChanged(int op);

private:
    enum OperationType {
        calcFreqency = 0,
        calcCapacitance = 1,
        calcInductance = 2,
    };

    static const double indUnits[];
    static const double capUnits[];
    static const double freqUnits[];


};

#endif // MAINWINDOW_H

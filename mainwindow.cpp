#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cmath>
#include <sstream>

const double MainWindow::indUnits[] = {1e-6, 1e-9, 1e-3};
const double MainWindow::capUnits[] = {1e-9, 1e-12, 1e-6, 1e-3};
const double MainWindow::freqUnits[] = {1e3, 1e6, 1};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QLocale::setDefault(QLocale::English);

    setupUi(this);

    connect(calcButton, SIGNAL(clicked()), this, SLOT(calculateClicked()));

    connect(indValue, SIGNAL(textChanged(QString)), this, SLOT(enableCalcButton()));
    connect(capValue, SIGNAL(textChanged(QString)), this, SLOT(enableCalcButton()));
    connect(freqValue, SIGNAL(textChanged(QString)), this, SLOT(enableCalcButton()));

    connect(opCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(opChanged(int)));

    indValue->setValidator(new QDoubleValidator(this));
    capValue->setValidator(new QDoubleValidator(this));
    freqValue->setValidator(new QDoubleValidator(this));

}

MainWindow::~MainWindow() {

}

void MainWindow::calculateClicked(void) {

    QString cValStr = capValue->text();
    double cVal = cValStr.toDouble();
    double cPow = capUnits[ capUnit->currentIndex() ];
    cVal *= cPow;
    std::cout << "Capacitance: " << cVal << std::endl;
    QString lValStr = indValue->text();
    double lVal = lValStr.toDouble();
    double lPow = indUnits[ indUnit->currentIndex() ];
    lVal *= lPow;
    std::cout << "Capacitance: " << lVal << std::endl;
    QString fValStr = freqValue->text();
    double fVal = fValStr.toDouble();
    double fPow = freqUnits[ freqUnit->currentIndex() ];
    fVal *= fPow;
    std::cout << "Capacitance: " << fVal << std::endl;


    int op = opCombo->currentIndex();

    if (op == calcFreqency) {
        std::cout << "Operation: f" << std::endl;

        fVal = 1 / (2 * M_PI * sqrt(lVal * cVal) );
        std::ostringstream stringStream;
        stringStream << (fVal / fPow);
        std::string str (stringStream.str());
        QString qstr = QString::fromStdString(str);
        freqValue->setText(qstr);

    } else if (op == calcCapacitance) {
        std::cout << "Operation: C" << std::endl;

        cVal = 1 / (4 * M_PI * M_PI * fVal * fVal * lVal);

        std::ostringstream stringStream;
        stringStream << cVal / cPow;
        std::string str (stringStream.str());
        QString qstr = QString::fromStdString(str);
        capValue->setText(qstr);

    } else if (op == calcInductance) {
        std::cout << "Operation: L" << std::endl;

        lVal = 1 / (4 * M_PI * M_PI * fVal * fVal * cVal);

        std::ostringstream stringStream;
        stringStream << lVal / lPow;
        std::string str (stringStream.str());
        QString qstr = QString::fromStdString(str);
        indValue->setText(qstr);

    }

    double zlVal = 2 * M_PI * fVal * lVal;
    double zcVal = -1/(2 * M_PI * fVal * cVal);

    std::ostringstream stringStream1;
    stringStream1 << zlVal;
    std::string str1 (stringStream1.str());
    QString qstr1 = QString::fromStdString(str1);
    indImpValue->setText(qstr1);

    std::ostringstream stringStream2;
    stringStream2 << zcVal;
    std::string str2 (stringStream2.str());
    QString qstr2 = QString::fromStdString(str2);
    capImpValue->setText(qstr2);

}

void MainWindow::enableCalcButton(void) {

    OperationType op = (OperationType) opCombo->currentIndex();

    if (op == calcFreqency) {
        std::cout << "enableCalcButton: f" << std::endl;
        if( (!indValue->text().isEmpty()) && (!capValue->text().isEmpty())) {
            if (indValue->hasAcceptableInput() && capValue->hasAcceptableInput()) {
                calcButton->setEnabled(true);
                return;
            }
        }
    } else if (op == calcCapacitance) {
        std::cout << "enableCalcButton: C" << std::endl;
        if( (!indValue->text().isEmpty()) && (!freqValue->text().isEmpty())) {
            if (indValue->hasAcceptableInput() && freqValue->hasAcceptableInput()) {
                calcButton->setEnabled(true);
                return;
            }
        }
    } else if (op == calcInductance) {
        std::cout << "enableCalcButton: L" << std::endl;
        if( (!freqValue->text().isEmpty()) && (!capValue->text().isEmpty())) {
            if (freqValue->hasAcceptableInput() && capValue->hasAcceptableInput()) {
                calcButton->setEnabled(true);
                return;
            }
        }
    }

    calcButton->setEnabled(false);

}

void MainWindow::opChanged(int op) {

    std::cout << "opChanged: new op = " << op << std::endl;
    enableCalcButton();

}

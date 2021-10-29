//
// Created by hered on 15.10.2021.
//

#include "InputParser.h"

InputParser::InputParser(QMainWindow *parent): QStatusBar(parent) {}

InputParser::~InputParser(){}

void InputParser::onx0Change(double value) {
    dataChange("x0", value);
}

void InputParser::ony0Change(double value) {
    dataChange("y0", value);
}

void InputParser::onXChange(double value) {
    dataChange("X", value);
}

void InputParser::onNChange(double value) {
    dataChange("N", value);
}

void InputParser::dataChange(const QString& arg, double value) {
    showMessage(arg + QString(" changed"));
    if(arg == QString("y0"))
        y0 = value;
    else if(arg == QString("x0"))
        x0 = value, emit setN(std::abs(x0 - X));
    else if(arg == QString("X"))
        X = value, emit setN(std::abs(x0 - X));
    else if (arg == QString("N"))
        N = (int)value;
    h = std::abs(X - x0) / N;
    emit setLineSeries(x0, y0, h, N);
}


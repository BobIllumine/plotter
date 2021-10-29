//
// Created by hered on 15.10.2021.
//

#include "StepLabel.h"

StepLabel::StepLabel(QWidget *parent): QLabel(parent) {}

StepLabel::~StepLabel() {}

void StepLabel::setX(double value) {
    X = value;
    setNum(std::abs(X - x0) / N);
}

void StepLabel::setx0(double value) {
    x0 = value;
    setNum(std::abs(X - x0) / N);
}

void StepLabel::setN(double value) {
    N = value;
    setNum(std::abs(X - x0) / N);
}
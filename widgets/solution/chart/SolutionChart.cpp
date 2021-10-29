//
// Created by hered on 15.10.2021.
//

#include "SolutionChart.h"

SolutionChart::SolutionChart(QGraphicsItem *parent): QChart(parent),
                                                    xAxis(new QValueAxis()),
                                                    yAxis(new QValueAxis()),
                                                    exact(new QLineSeries()),
                                                    euler(new QLineSeries()),
                                                    heun(new QLineSeries),
                                                    rungeKutta(new QLineSeries()),
                                                    x(new QLineSeries()),
                                                    y(new QLineSeries()) {

    xAxis->setRange(0, 5), xAxis->setTickCount(10);
    yAxis->setRange(0, 5e5), yAxis->setTickCount(10);

    yAxis->setLabelFormat("%.1e");
    this->addAxis(xAxis, Qt::AlignBottom);
    this->addAxis(yAxis, Qt::AlignLeft);

    *x << QPointF(xAxis->min(), 0) << QPointF(xAxis->max(), 0);
    *y << QPointF(0, yAxis->min()) << QPointF(0, yAxis->max());

    x->setPen(QPen(QColor(0, 0, 0)));
    y->setPen(QPen(QColor(0,0, 0)));

    this->addSeries(exact);
    this->addSeries(euler);
    this->addSeries(heun);
    this->addSeries(rungeKutta);
    this->addSeries(x);
    this->addSeries(y);

    x->attachAxis(xAxis), x->attachAxis(yAxis);
    y->attachAxis(xAxis), y->attachAxis(yAxis);
    exact->attachAxis(xAxis), exact->attachAxis(yAxis);
    euler->attachAxis(xAxis), euler->attachAxis(yAxis);
    heun->attachAxis(xAxis), heun->attachAxis(yAxis);
    rungeKutta->attachAxis(xAxis), rungeKutta->attachAxis(yAxis);
}

SolutionChart::~SolutionChart() {
    delete xAxis;
    delete yAxis;
    delete exact;
    delete euler;
    delete heun;
    delete rungeKutta;
    delete x;
    delete y;
}

void SolutionChart::onDataChange(double x0, double y0, double h, int N) {
    Calculations calculator = Calculations::getInstance();
    calculator.updateValues(x0, y0, x0 + N * h, h, N);
    QVector<QPointF> exactV, eulerV, heunV, rungeKuttaV;
    for(int i = 0; i <= N; ++i) {
        auto e1 = calculator.getEuler()[i],
            e2 = calculator.getHeun()[i],
            e3 = calculator.getRungeKutta()[i];
        eulerV << QPointF(e1.first, e1.second);
        heunV << QPointF(e2.first, e2.second);
        rungeKuttaV << QPointF(e3.first, e3.second);
    }
    for(int i = 0; i <= 500; ++i) {
        auto e = calculator.getExact()[i];
        if(std::isnan(e.second))
            emit badValue();
        else exactV << QPointF(e.first, e.second);
    }
    exact->replace(exactV);
    euler->replace(eulerV);
    heun->replace(heunV);
    rungeKutta->replace(rungeKuttaV);
}

void SolutionChart::scaleAxes() {
    QVector<QPointF> newX, newY;
    newX << QPointF(xAxis->min(), 0) << QPointF(xAxis->max(), 0);
    newY << QPointF(0, yAxis->min()) << QPointF(0, yAxis->max());
    x->replace(newX);
    y->replace(newY);
}

QLineSeries *SolutionChart::getExact() {
    return exact;
}

QLineSeries *SolutionChart::getEuler() {
    return euler;
}

QLineSeries *SolutionChart::getHeun() {
    return heun;
}

QLineSeries *SolutionChart::getRungeKutta() {
    return rungeKutta;
}

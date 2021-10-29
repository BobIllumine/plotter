//
// Created by hered on 15.10.2021.
//

#include "GTEChart.h"

GTEChart::GTEChart(QGraphicsItem *parent) : QChart(parent),
                                            xAxis(new QValueAxis()),
                                            yAxis(new QValueAxis()),
                                            eulerGTE(new QLineSeries()),
                                            heunGTE(new QLineSeries),
                                            rungeKuttaGTE(new QLineSeries()),
                                            x(new QLineSeries()),
                                            y(new QLineSeries()) {

    xAxis->setRange(0, 100), xAxis->setTickCount(10);
    yAxis->setRange(0, 5e5), xAxis->setTickCount(10);

    yAxis->setLabelFormat("%.1e");

    this->addAxis(xAxis, Qt::AlignBottom);
    this->addAxis(yAxis, Qt::AlignLeft);

    *x << QPointF(xAxis->min(), 0) << QPointF(xAxis->max(), 0);
    *y << QPointF(0, yAxis->min()) << QPointF(0, yAxis->max());

    x->setPen(QPen(QColor(0, 0, 0)));
    y->setPen(QPen(QColor(0, 0, 0)));

    this->addSeries(eulerGTE);
    this->addSeries(heunGTE);
    this->addSeries(rungeKuttaGTE);
    this->addSeries(x);
    this->addSeries(y);

    x->attachAxis(xAxis), x->attachAxis(yAxis);
    y->attachAxis(xAxis), y->attachAxis(yAxis);
    eulerGTE->attachAxis(xAxis), eulerGTE->attachAxis(yAxis);
    heunGTE->attachAxis(xAxis), heunGTE->attachAxis(yAxis);
    rungeKuttaGTE->attachAxis(xAxis), rungeKuttaGTE->attachAxis(yAxis);
}

GTEChart::~GTEChart() {
    delete xAxis;
    delete yAxis;
    delete eulerGTE;
    delete heunGTE;
    delete rungeKuttaGTE;
    delete x;
    delete y;
}

void GTEChart::onDataChange(double x0, double y0, double h, int N) {
    Calculations calculator = Calculations::getInstance();
    calculator.updateValues(x0, y0, x0 + N * h, h, N);
    QVector<QPointF> eulerV, heunV, rungeKuttaV;
    for(int i = 1; i <= N; ++i) {
        auto e1 = calculator.getEulerGTE()[i],
                e2 = calculator.getHeunGTE()[i],
                e3 = calculator.getRungeKuttaGTE()[i];
        if(std::isnan(e1.second))
                emit badValue();
        else {
            eulerV << QPointF(e1.first, e1.second);
            heunV << QPointF(e2.first, e2.second);
            rungeKuttaV << QPointF(e3.first, e3.second);
        }
    }
    eulerGTE->replace(eulerV);
    heunGTE->replace(heunV);
    rungeKuttaGTE->replace(rungeKuttaV);
}

void GTEChart::scaleAxes() {
    QVector<QPointF> newX, newY;
    newX << QPointF(xAxis->min(), 0) << QPointF(xAxis->max(), 0);
    newY << QPointF(0, yAxis->min()) << QPointF(0, yAxis->max());
    x->replace(newX);
    y->replace(newY);
}

QLineSeries *GTEChart::getEulerGTE() {
    return eulerGTE;
}

QLineSeries *GTEChart::getHeunGTE() {
    return heunGTE;
}

QLineSeries *GTEChart::getRungeKuttaGTE() {
    return rungeKuttaGTE;
}
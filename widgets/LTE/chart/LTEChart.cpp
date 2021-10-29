//
// Created by hered on 15.10.2021.
//

#include "LTEChart.h"

LTEChart::LTEChart(QGraphicsItem *parent) : QChart(parent),
                                            xAxis(new QValueAxis()),
                                            yAxis(new QValueAxis()),
                                            eulerLTE(new QLineSeries()),
                                            heunLTE(new QLineSeries),
                                            rungeKuttaLTE(new QLineSeries()),
                                            x(new QLineSeries()),
                                            y(new QLineSeries()) {

    xAxis->setRange(0, 5), xAxis->setTickCount(10);
    yAxis->setRange(0, 5e5), xAxis->setTickCount(10);

    yAxis->setLabelFormat("%.1e");

    this->addAxis(xAxis, Qt::AlignBottom);
    this->addAxis(yAxis, Qt::AlignLeft);

    *x << QPointF(xAxis->min(), 0) << QPointF(xAxis->max(), 0);
    *y << QPointF(0, yAxis->min()) << QPointF(0, yAxis->max());

    x->setPen(QPen(QColor(0, 0, 0)));
    y->setPen(QPen(QColor(0, 0, 0)));

    this->addSeries(eulerLTE);
    this->addSeries(heunLTE);
    this->addSeries(rungeKuttaLTE);
    this->addSeries(x);
    this->addSeries(y);

    x->attachAxis(xAxis), x->attachAxis(yAxis);
    y->attachAxis(xAxis), y->attachAxis(yAxis);
    eulerLTE->attachAxis(xAxis), eulerLTE->attachAxis(yAxis);
    heunLTE->attachAxis(xAxis), heunLTE->attachAxis(yAxis);
    rungeKuttaLTE->attachAxis(xAxis), rungeKuttaLTE->attachAxis(yAxis);
}

LTEChart::~LTEChart() {
    delete xAxis;
    delete yAxis;
    delete eulerLTE;
    delete heunLTE;
    delete rungeKuttaLTE;
    delete x;
    delete y;
}

void LTEChart::onDataChange(double x0, double y0, double h, int N) {
    Calculations calculator = Calculations::getInstance();
    calculator.updateValues(x0, y0, x0 + N * h, h, N);
    QVector<QPointF> eulerV, heunV, rungeKuttaV;
    for(int i = 0; i <= N; ++i) {
        auto e1 = calculator.getEulerLTE()[i],
                e2 = calculator.getHeunLTE()[i],
                e3 = calculator.getRungeKuttaLTE()[i];
        if(std::isnan(e1.second))
            emit badValue();
        else {
            eulerV << QPointF(e1.first, e1.second);
            heunV << QPointF(e2.first, e2.second);
            rungeKuttaV << QPointF(e3.first, e3.second);
        }
    }
    eulerLTE->replace(eulerV);
    heunLTE->replace(heunV);
    rungeKuttaLTE->replace(rungeKuttaV);
}

void LTEChart::scaleAxes() {
    QVector<QPointF> newX, newY;
    newX << QPointF(xAxis->min(), 0) << QPointF(xAxis->max(), 0);
    newY << QPointF(0, yAxis->min()) << QPointF(0, yAxis->max());
    x->replace(newX);
    y->replace(newY);
}

QLineSeries *LTEChart::getEulerLTE() {
    return eulerLTE;
}

QLineSeries *LTEChart::getHeunLTE() {
    return heunLTE;
}

QLineSeries *LTEChart::getRungeKuttaLTE() {
    return rungeKuttaLTE;
}

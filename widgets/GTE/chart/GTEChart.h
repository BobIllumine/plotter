//
// Created by hered on 15.10.2021.
//

#ifndef GRAPH_PLOTTER_GTECHART_H
#define GRAPH_PLOTTER_GTECHART_H

#include <QtCharts>
#include "../../Calculations.h"


class GTEChart : public QChart {
Q_OBJECT
public:
    explicit GTEChart(QGraphicsItem *parent = nullptr);
    ~GTEChart() override;
    void scaleAxes();
    QLineSeries* getEulerGTE();
    QLineSeries* getHeunGTE();
    QLineSeries* getRungeKuttaGTE();

public slots:
    void onDataChange(double x0, double y0, double h, int N);

signals:
    void badValue();
    void showWarning();

private:
    QValueAxis *xAxis, *yAxis;
    QLineSeries *eulerGTE, *heunGTE, *rungeKuttaGTE, *x, *y;
};

#endif //GRAPH_PLOTTER_GTECHART_H

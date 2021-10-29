//
// Created by hered on 15.10.2021.
//

#ifndef GRAPH_PLOTTER_SOLUTIONCHART_H
#define GRAPH_PLOTTER_SOLUTIONCHART_H

#include <QtCharts>
#include "../../Calculations.h"

class SolutionChart : public QChart {

    Q_OBJECT

public:
    explicit SolutionChart(QGraphicsItem *parent = nullptr);
    ~SolutionChart() override;
    void scaleAxes();
    QLineSeries* getExact();
    QLineSeries* getEuler();
    QLineSeries* getHeun();
    QLineSeries* getRungeKutta();

public slots:
    void onDataChange(double x0, double y0, double h, int N);

signals:
    void badValue();


private:
    QValueAxis *xAxis;
    QValueAxis *yAxis;
    QLineSeries *exact;
    QLineSeries *euler, *heun, *rungeKutta, *x, *y;
};


#endif //GRAPH_PLOTTER_SOLUTIONCHART_H

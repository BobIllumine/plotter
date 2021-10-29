//
// Created by hered on 15.10.2021.
//

#ifndef GRAPH_PLOTTER_LTECHART_H
#define GRAPH_PLOTTER_LTECHART_H
#include <QtCharts>
#include "../../Calculations.h"


class LTEChart : public QChart {
    Q_OBJECT
public:
    explicit LTEChart(QGraphicsItem *parent = nullptr);
    ~LTEChart() override;
    void scaleAxes();
    QLineSeries* getEulerLTE();
    QLineSeries* getHeunLTE();
    QLineSeries* getRungeKuttaLTE();

public slots:
    void onDataChange(double x0, double y0, double h, int N);

signals:
    void badValue();
    void showWarning();

private:
    QValueAxis *xAxis, *yAxis;
    QLineSeries *eulerLTE, *heunLTE, *rungeKuttaLTE, *x, *y;
};


#endif //GRAPH_PLOTTER_LTECHART_H

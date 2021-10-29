//
// Created by hered on 15.10.2021.
//

#ifndef GRAPH_PLOTTER_LTECHARTVIEW_H
#define GRAPH_PLOTTER_LTECHARTVIEW_H

#include <QChartView>
#include <QSplineSeries>
#include <QLineSeries>
#include <QtAlgorithms>
#include "../chart/LTEChart.h"

class LTEChartView : public QChartView {

Q_OBJECT

public:
    explicit LTEChartView(QWidget *parent = nullptr);
    ~LTEChartView() override;

public slots:
    void onInputUpdate(double x0, double y0, double h, int N);
    void toggleEulerLTE(int state);
    void toggleHeunLTE(int state);
    void toggleRungeKuttaLTE(int state);
    void onZoom(int factor);
    void onBadValue();

signals:
    void dataChanged(double x0, double y0, double h, int N);
    void showWarning();

private:
    bool moving = false;
    QPoint pos;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif //GRAPH_PLOTTER_LTECHARTVIEW_H

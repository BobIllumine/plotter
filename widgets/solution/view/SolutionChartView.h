//
// Created by hered on 15.10.2021.
//

#ifndef GRAPH_PLOTTER_SOLUTIONCHARTVIEW_H
#define GRAPH_PLOTTER_SOLUTIONCHARTVIEW_H
#include <QChartView>
#include <QSplineSeries>
#include <QLineSeries>
#include <QtAlgorithms>
#include "../chart/SolutionChart.h"

class SolutionChartView : public QChartView {

    Q_OBJECT

public:
    explicit SolutionChartView(QWidget *parent = nullptr);
    ~SolutionChartView() override;

public slots:
    void onInputUpdate(double x0, double y0, double h, int N);
    void toggleExact(int state);
    void toggleEuler(int state);
    void toggleHeun(int state);
    void toggleRungeKutta(int state);
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


#endif //GRAPH_PLOTTER_SOLUTIONCHARTVIEW_H

//
// Created by hered on 15.10.2021.
//

#include <QValueAxis>
#include <QLogValueAxis>
#include "SolutionChartView.h"

SolutionChartView::SolutionChartView(QWidget *parent): QChartView(parent) {
    SolutionChart *init = new SolutionChart();
    setChart(init);
//    chart()->setTheme(QChart::ChartThemeBlueIcy);
    chart()->setAnimationOptions(QChart::NoAnimation);
    chart()->legend()->hide();
    connect(this, &SolutionChartView::dataChanged, init, &SolutionChart::onDataChange);
    connect(init, &SolutionChart::badValue, this, &SolutionChartView::onBadValue);
}

SolutionChartView::~SolutionChartView() { }

void SolutionChartView::onInputUpdate(double x0, double y0, double h, int N) {
    emit dataChanged(x0, y0, h, N);
}

void SolutionChartView::toggleExact(int state) {
    if(state == Qt::Checked)
        dynamic_cast<SolutionChart*>(chart())->getExact()->show();
    else
        dynamic_cast<SolutionChart*>(chart())->getExact()->hide();
}

void SolutionChartView::toggleEuler(int state) {
    if(state == Qt::Checked)
        dynamic_cast<SolutionChart*>(chart())->getEuler()->show();
    else
        dynamic_cast<SolutionChart*>(chart())->getEuler()->hide();
}

void SolutionChartView::toggleHeun(int state) {
    if(state == Qt::Checked)
        dynamic_cast<SolutionChart*>(chart())->getHeun()->show();
    else
        dynamic_cast<SolutionChart*>(chart())->getHeun()->hide();
}

void SolutionChartView::toggleRungeKutta(int state) {
    if(state == Qt::Checked)
        dynamic_cast<SolutionChart*>(chart())->getRungeKutta()->show();
    else
        dynamic_cast<SolutionChart*>(chart())->getRungeKutta()->hide();
}

void SolutionChartView::onZoom(int factor) {
    chart()->zoomReset();
    chart()->zoom(double(factor)/double(100));
    qDebug() << factor << ' ' << double(factor)/double(100) << Qt::endl;
    dynamic_cast<SolutionChart*>(chart())->scaleAxes();
}

void SolutionChartView::onBadValue() {
    emit showWarning();
}

void SolutionChartView::mousePressEvent(QMouseEvent *event) {
    moving = true;
    pos = event->pos();
}

void SolutionChartView::mouseMoveEvent(QMouseEvent *event) {
    if(moving) {
        chart()->scroll(-(double(event->pos().x() - pos.x()) / 10), (double(event->pos().y() - pos.y()) / 10));
        dynamic_cast<SolutionChart*>(chart())->scaleAxes();
    }
}

void SolutionChartView::mouseReleaseEvent(QMouseEvent *event) {
    moving = false;
}
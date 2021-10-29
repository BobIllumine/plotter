//
// Created by hered on 15.10.2021.
//

#include "GTEChartView.h"

GTEChartView::GTEChartView(QWidget *parent): QChartView(parent) {
    GTEChart *init = new GTEChart();
    setChart(init);
    chart()->setTheme(QChart::ChartThemeLight);
    chart()->setAnimationOptions(QChart::NoAnimation);
    chart()->legend()->hide();
    setRubberBand(QChartView::RectangleRubberBand);
    connect(this, &GTEChartView::dataChanged, init, &GTEChart::onDataChange);
    connect(init, &GTEChart::badValue, this, &GTEChartView::onBadValue);

}

GTEChartView::~GTEChartView() { }

void GTEChartView::onInputUpdate(double x0, double y0, double h, int N) {
    emit dataChanged(x0, y0, h, N);
}


void GTEChartView::toggleEulerGTE(int state) {
    if(state == Qt::Checked)
        dynamic_cast<GTEChart*>(chart())->getEulerGTE()->show();
    else
        dynamic_cast<GTEChart*>(chart())->getEulerGTE()->hide();
}

void GTEChartView::toggleHeunGTE(int state) {
    if(state == Qt::Checked)
        dynamic_cast<GTEChart*>(chart())->getHeunGTE()->show();
    else
        dynamic_cast<GTEChart*>(chart())->getHeunGTE()->hide();
}

void GTEChartView::toggleRungeKuttaGTE(int state) {
    if(state == Qt::Checked)
        dynamic_cast<GTEChart*>(chart())->getRungeKuttaGTE()->show();
    else
        dynamic_cast<GTEChart*>(chart())->getRungeKuttaGTE()->hide();
}

void GTEChartView::onZoom(int factor) {
    chart()->zoomReset();
    chart()->zoom(double(factor)/double(100));
    qDebug() << factor << ' ' << double(factor)/double(100) << Qt::endl;
    dynamic_cast<GTEChart*>(chart())->scaleAxes();
}

void GTEChartView::onBadValue() {
    emit showWarning();
}

void GTEChartView::mousePressEvent(QMouseEvent *event) {
    moving = true;
    pos = event->pos();
}

void GTEChartView::mouseMoveEvent(QMouseEvent *event) {
    if(moving) {
        chart()->scroll(-(double(event->pos().x() - pos.x()) / 10), (double(event->pos().y() - pos.y()) / 10));
        dynamic_cast<GTEChart*>(chart())->scaleAxes();
    }
}

void GTEChartView::mouseReleaseEvent(QMouseEvent *event) {
    moving = false;
}
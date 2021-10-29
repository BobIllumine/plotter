//
// Created by hered on 15.10.2021.
//

#include "LTEChartView.h"

LTEChartView::LTEChartView(QWidget *parent): QChartView(parent) {
    LTEChart *init = new LTEChart();
    setChart(init);
    chart()->setTheme(QChart::ChartThemeLight);
    chart()->setAnimationOptions(QChart::NoAnimation);
    chart()->legend()->hide();
    setRubberBand(QChartView::RectangleRubberBand);
    connect(this, &LTEChartView::dataChanged, init, &LTEChart::onDataChange);
    connect(init, &LTEChart::badValue, this, &LTEChartView::onBadValue);

}

LTEChartView::~LTEChartView() { }

void LTEChartView::onInputUpdate(double x0, double y0, double h, int N) {
    emit dataChanged(x0, y0, h, N);
}


void LTEChartView::toggleEulerLTE(int state) {
    if(state == Qt::Checked)
        dynamic_cast<LTEChart*>(chart())->getEulerLTE()->show();
    else
        dynamic_cast<LTEChart*>(chart())->getEulerLTE()->hide();
}

void LTEChartView::toggleHeunLTE(int state) {
    if(state == Qt::Checked)
        dynamic_cast<LTEChart*>(chart())->getHeunLTE()->show();
    else
        dynamic_cast<LTEChart*>(chart())->getHeunLTE()->hide();
}

void LTEChartView::toggleRungeKuttaLTE(int state) {
    if(state == Qt::Checked)
        dynamic_cast<LTEChart*>(chart())->getRungeKuttaLTE()->show();
    else
        dynamic_cast<LTEChart*>(chart())->getRungeKuttaLTE()->hide();
}

void LTEChartView::onZoom(int factor) {
    chart()->zoomReset();
    chart()->zoom(double(factor)/double(100));
    qDebug() << factor << ' ' << double(factor)/double(100) << Qt::endl;
    dynamic_cast<LTEChart*>(chart())->scaleAxes();
}

void LTEChartView::onBadValue() {
    emit showWarning();
}

void LTEChartView::mousePressEvent(QMouseEvent *event) {
    moving = true;
    pos = event->pos();
}

void LTEChartView::mouseMoveEvent(QMouseEvent *event) {
    if(moving) {
        chart()->scroll(-(double(event->pos().x() - pos.x()) / 10), (double(event->pos().y() - pos.y()) / 10));
        dynamic_cast<LTEChart*>(chart())->scaleAxes();
    }
}

void LTEChartView::mouseReleaseEvent(QMouseEvent *event) {
    moving = false;
}
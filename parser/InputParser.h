//
// Created by hered on 15.10.2021.
//

#ifndef GRAPH_PLOTTER_INPUTPARSER_H
#define GRAPH_PLOTTER_INPUTPARSER_H
#include <QStatusBar>
#include <QMainWindow>
#include <QSplineSeries>

class InputParser : public QStatusBar {
    Q_OBJECT
public:
    explicit InputParser(QMainWindow *parent = nullptr);
    ~InputParser() override;
private slots:
    void onx0Change(double value);
    void ony0Change(double value);
    void onXChange(double value);
    void onNChange(double value);

signals:
    void setLineSeries(double x0, double y0, double h, int N);
    void setN(double val);

private:
    void dataChange(const QString& arg, double value);
    double x0 = 0, y0 = 0, X = 0, h;
    int N = 1;
};


#endif //GRAPH_PLOTTER_INPUTPARSER_H

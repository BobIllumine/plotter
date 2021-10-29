//
// Created by hered on 15.10.2021.
//

#ifndef GRAPH_PLOTTER_STEPLABEL_H
#define GRAPH_PLOTTER_STEPLABEL_H
#include <QLabel>

class StepLabel : public QLabel {
    Q_OBJECT
public:
    explicit StepLabel(QWidget *parent = nullptr);
    ~StepLabel() override;
public slots:
    void setx0(double value);
    void setX(double value);
    void setN(double value);
private:
    double x0 = 0, X = 1;
    int N = 1;
};


#endif //GRAPH_PLOTTER_STEPLABEL_H

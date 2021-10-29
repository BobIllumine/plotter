//
// Created by hered on 22.10.2021.
//

#ifndef GRAPH_PLOTTER_CALCULATIONS_H
#define GRAPH_PLOTTER_CALCULATIONS_H
#include <vector>
#include <cmath>
#include <iostream>

class Calculations {
public:
    static Calculations& getInstance();
    void updateValues(double x_0, double y_0, double x, double h, int n);
    const std::vector<std::pair<double, double> >& getExact();
    const std::vector<std::pair<double, double> >& getEuler();
    const std::vector<std::pair<double, double> >& getHeun();
    const std::vector<std::pair<double, double> >& getRungeKutta();
    const std::vector<std::pair<double, double> >& getEulerLTE();
    const std::vector<std::pair<double, double> >& getHeunLTE();
    const std::vector<std::pair<double, double> >& getRungeKuttaLTE();
    const std::vector<std::pair<double, double> >& getEulerGTE();
    const std::vector<std::pair<double, double> >& getHeunGTE();
    const std::vector<std::pair<double, double> >& getRungeKuttaGTE();
private:
    Calculations() = default;
    double f(const double& x, const double &y);
    double y_x(const double& x) const;
    void buildExact();
    double buildEulerGTE(int step);
    double buildHeunGTE(int step);
    double buildRungeKuttaGTE(int step);


    double y0{};
    double x0{};
    double X{};
    int N{};

    std::vector<std::pair<double, double> > exact = std::vector<std::pair<double, double> >(1000, {0, 0});
    std::vector<std::pair<double, double> > euler = std::vector<std::pair<double, double> >(1000, {0, 0});
    std::vector<std::pair<double, double> > heun = std::vector<std::pair<double, double> >(1000, {0, 0});
    std::vector<std::pair<double, double> > rungeKutta = std::vector<std::pair<double, double> >(1000, {0, 0});

    std::vector<std::pair<double, double> > eulerLTE = std::vector<std::pair<double, double> >(1000, {0, 0});
    std::vector<std::pair<double, double> > heunLTE = std::vector<std::pair<double, double> >(1000, {0, 0});
    std::vector<std::pair<double, double> > rungeKuttaLTE = std::vector<std::pair<double, double> >(1000, {0, 0});


    std::vector<std::pair<double, double> > eulerGTE = std::vector<std::pair<double, double> >(1000, {0, 0});
    std::vector<std::pair<double, double> > heunGTE = std::vector<std::pair<double, double> >(1000, {0, 0});
    std::vector<std::pair<double, double> > rungeKuttaGTE = std::vector<std::pair<double, double> >(1000, {0, 0});
};


#endif //GRAPH_PLOTTER_CALCULATIONS_H

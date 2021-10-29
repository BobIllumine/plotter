//
// Created by hered on 22.10.2021.
//

#include "Calculations.h"

Calculations& Calculations::getInstance() {
    static Calculations calc;
    return calc;
}

double Calculations::f(const double &x, const double &y) {
    return (3 * y - x * std::cbrt(y));
}

double Calculations::y_x(const double &x) const {
    double c = (std::cbrt(y0 * y0) - (x0 / 3) - ((double)(1) / (double)(6))) / std::exp(2 * x0);
    return std::sqrt(std::pow(c * std::exp(2 * x) + (x / 3) + ((double)(1) / (double)(6)), 3));
}

void Calculations::updateValues(double x_0, double y_0, double x, double h, int n) {
    y0 = y_0; x0 = x_0; X = x; N = n;
    buildExact();
    double eulerPrevX = x0, eulerPrevY = y0,
            heunPrevX = x0, heunPrevY = y0,
            rungeKuttaPrevX = x0, rungeKuttaPrevY = y0;

    euler[0] = heun[0] = rungeKutta[0] = {x0, y0};
    eulerLTE[0] = heunLTE[0] = rungeKuttaLTE[0] = {0, 0};
    eulerGTE[0] = heunGTE[0] = rungeKuttaGTE[0] = {0, 0};

    for(int i = 1; i <= N; ++i) {
        double eulerK = h * f(eulerPrevX, eulerPrevY),
                heunK1 = h * f(heunPrevX, heunPrevY), heunK2 = h * f(heunPrevX + h, heunPrevY + heunK1),
                rungeKuttaK1 = h * f(rungeKuttaPrevX, rungeKuttaPrevY),
                rungeKuttaK2 = h * f(rungeKuttaPrevX + (h / 2), rungeKuttaPrevY + (rungeKuttaK1 / 2)),
                rungeKuttaK3 = h * f(rungeKuttaPrevX + (h / 2), rungeKuttaPrevY + (rungeKuttaK2 / 2)),
                rungeKuttaK4 = h * f(rungeKuttaPrevX + h, rungeKuttaPrevY + rungeKuttaK3);

            euler[i] = {eulerPrevX + h,eulerPrevY + eulerK};
            heun[i] = {heunPrevX + h,heunPrevY + (heunK1 + heunK2) / 2};
            rungeKutta[i] = {rungeKuttaPrevX + h, rungeKuttaPrevY + (rungeKuttaK1 + 2 * rungeKuttaK2 + 2 * rungeKuttaK3 + rungeKuttaK4) / 6};

            eulerLTE[i] = {eulerPrevX + h, std::abs(y_x(eulerPrevX + h) - euler[i].second)};
            heunLTE[i] = {heunPrevX + h, std::abs(y_x(heunPrevX + h) - heun[i].second)};
            rungeKuttaLTE[i] = {rungeKuttaPrevX + h, std::abs(y_x(rungeKuttaPrevX + h) - rungeKutta[i].second)};

            eulerGTE[i] = {i, buildEulerGTE(i)};
            heunGTE[i] = {i, buildHeunGTE(i)};
            rungeKuttaGTE[i] = {i, buildRungeKuttaGTE(i)};

        eulerPrevX += h; eulerPrevY += eulerK;
        heunPrevX += h; heunPrevY += (heunK1 + heunK2) / 2;
        rungeKuttaPrevX += h; rungeKuttaPrevY += (rungeKuttaK1 + 2 * rungeKuttaK2 + 2 * rungeKuttaK3 + rungeKuttaK4) / 6;
    }
}

void Calculations::buildExact() {
    exact[0] = {x0, y0};
    double step = x0;
    for(int i = 1; i <= 500; ++i) {
        exact[i] = {step, y_x(step)};
        step += std::abs(X - x0) / 500;
    }
}

double Calculations::buildEulerGTE(int step) {
    double x = x0, y = y0,
        h = std::abs(X - x0) / step,
        mx = std::numeric_limits<double>::min();
    for(int i = 1; i <= step; ++i) {
        double eulerK = h * f(x, y);
        x += h, y += eulerK;
        mx = std::max(mx, std::abs(y_x(x) - y));
    }
    return mx;
}

double Calculations::buildHeunGTE(int step) {
    double x = x0, y = y0,
        h = std::abs(X - x0) / step,
        mx = std::numeric_limits<double>::min();
    for(int i = 1; i <= step; ++i) {
        double heunK1 = h * f(x, y),
                heunK2 = h * f(x + h, y + heunK1);
        x += h, y += (heunK1 + heunK2) / 2;
        mx = std::max(mx, std::abs(y_x(x) - y));
    }
    return mx;
}

double Calculations::buildRungeKuttaGTE(int step) {
    double x = x0, y = y0,
        h = std::abs(X - x0) / step,
        mx = std::numeric_limits<double>::min();
    for(int i = 1; i <= step; ++i) {
        double rungeKuttaK1 = h * f(x, y),
                rungeKuttaK2 = h * f(x + (h / 2), y + (rungeKuttaK1 / 2)),
                rungeKuttaK3 = h * f(x + (h / 2), y + (rungeKuttaK2 / 2)),
                rungeKuttaK4 = h * f(x + h, y + rungeKuttaK3);
        x += h, y += (rungeKuttaK1 + 2 * rungeKuttaK2 + 2 * rungeKuttaK3 + rungeKuttaK4) / 6;
        mx = std::max(mx, std::abs(y_x(x) - y));
    }
    return mx;
}

const std::vector<std::pair<double, double> > &Calculations::getExact() {
    return exact;
}

const std::vector<std::pair<double, double> > &Calculations::getEuler() {
    return euler;
}

const std::vector<std::pair<double, double> > &Calculations::getHeun() {
    return heun;
}

const std::vector<std::pair<double, double> > &Calculations::getRungeKutta() {
    return rungeKutta;
}

const std::vector<std::pair<double, double> > &Calculations::getEulerLTE() {
    return eulerLTE;
}

const std::vector<std::pair<double, double> > &Calculations::getHeunLTE() {
    return heunLTE;
}

const std::vector<std::pair<double, double> > &Calculations::getRungeKuttaLTE() {
    return rungeKuttaLTE;
}

const std::vector<std::pair<double, double> > &Calculations::getEulerGTE() {
    return eulerGTE;
}

const std::vector<std::pair<double, double> > &Calculations::getHeunGTE() {
    return heunGTE;
}

const std::vector<std::pair<double, double> > &Calculations::getRungeKuttaGTE() {
    return rungeKuttaGTE;
}

//
// Created by hered on 10.10.2021.
//

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include "ui/AppUI.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    AppUI ui;
    ui.show();
    return QApplication::exec();
}

//
// Created by hered on 14.10.2021.
//

#ifndef GRAPH_PLOTTER_APPUI_H
#define GRAPH_PLOTTER_APPUI_H

#include <QMainWindow>
#include <QDockWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class AppUI; }
QT_END_NAMESPACE

class AppUI : public QMainWindow {
Q_OBJECT

public:
    explicit AppUI(QWidget *parent = nullptr);

    ~AppUI() override;

private:
    Ui::AppUI *ui;
};


#endif //GRAPH_PLOTTER_APPUI_H

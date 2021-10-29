//
// Created by hered on 14.10.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AppUI.h" resolved

#include "AppUI.h"
#include "ui_AppUI.h"
#include "../widgets/Calculations.h"

AppUI::AppUI(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::AppUI) {
    Calculations calc = Calculations::getInstance();
    ui->setupUi(this);
    connect(ui->statusBar, &InputParser::setN, ui->NInput, [=](double val){
        ui->NInput->setMinimum(val);
    });
    connect(ui->solutionChartView, &SolutionChartView::showWarning, ui->statusBar, [=](){
        ui->statusBar->showMessage("Exact solution cannot be found at this point");
    });
    connect(ui->lteChartView, &LTEChartView::showWarning, ui->statusBar, [=](){
        ui->statusBar->showMessage("Exact solution cannot be found at this point");
    });
}

AppUI::~AppUI() {
    delete ui;
}


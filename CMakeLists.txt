cmake_minimum_required(VERSION 3.20)
project(graph_plotter)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.0\\mingw81_64\\lib\\cmake")
set(QT_QMAKE_EXECUTABLE "C:\\Qt\\6.2.0\\mingw81_64\\bin\\qmake6.exe")

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Quick REQUIRED)
find_package(Qt6Charts REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(graph_plotter
        main.cpp
        ui/AppUI.cpp
        ui/AppUI.h
        ui/AppUI.ui
        widgets/solution/chart/SolutionChart.cpp
        widgets/solution/chart/SolutionChart.h
        widgets/solution/view/SolutionChartView.cpp
        widgets/solution/view/SolutionChartView.h
        parser/InputParser.cpp
        parser/InputParser.h widgets/GTE/chart/GTEChart.cpp widgets/GTE/chart/GTEChart.h widgets/LTE/chart/LTEChart.cpp widgets/LTE/chart/LTEChart.h widgets/GTE/view/GTEChartView.cpp widgets/GTE/view/GTEChartView.h widgets/LTE/view/LTEChartView.cpp widgets/LTE/view/LTEChartView.h widgets/step/StepLabel.cpp widgets/step/StepLabel.h widgets/Calculations.cpp widgets/Calculations.h)

target_link_libraries(graph_plotter Qt::Core Qt::Widgets Qt::Quick Qt::Charts)
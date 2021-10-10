cmake_minimum_required(VERSION 3.20)
project(graph_plotter)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.0\\mingw81_64\\lib\\cmake")
set(QT_QMAKE_EXECUTABLE "C:\\Qt\\6.2.0\\mingw81_64\\bin\\qmake6.exe")

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Quick REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(graph_plotter main.cpp main.cpp)

target_link_libraries(graph_plotter Qt::Core Qt::Widgets Qt::Quick)
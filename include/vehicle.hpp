#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "graph.hpp"
#include "qpainter.h"
#include "qpropertyanimation.h"
#include "qwidget.h"

class Vehicle : QWidget{
public:
    Graph<char>& graph;
    int id;
    char from;
    char to;
    QPropertyAnimation* animation;   
    Vehicle(Graph<char>& graph, int id, char from, char to) : graph(graph), id(id), from(from), to(to){
        animation = new QPropertyAnimation(this);
        
    }
protected:
    void paintEvent(QPaintEvent* event) override{
        QPainter painter(this);
    }
};

#endif // VEHICLE_HPP
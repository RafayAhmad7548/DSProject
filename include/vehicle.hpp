#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "graph.hpp"
#include "linklist.hpp"
#include "qabstractanimation.h"
#include "qdebug.h"
#include "qnamespace.h"
#include "qsequentialanimationgroup.h"
#include "qpainter.h"
#include "qpropertyanimation.h"
#include "qwidget.h"

class Vehicle : public QWidget{
    Graph<char>& graph;
    int id;
    char from;
    char to;
    std::string path;
    QSequentialAnimationGroup* animations;

    void initAnimations(){
        for(size_t i=0;i<path.length()-1;i++){
            QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
            QPoint p(10, 10);
            animation->setStartValue(graph.adjList.get(path[i])->center-p);
            animation->setEndValue(graph.adjList.get(path[i+1])->center-p);
            NodeList<Edge<char>>* temp = graph.adjList.get(path[i])->value.head;
            while(temp != nullptr && temp->value.to != path[i+1]){
                temp = temp->next;
            }
            if(temp != nullptr){
                animation->setDuration(temp->value.weight * 1000);
            }
            animations->addAnimation(animation);
        }
    }

public:
    Vehicle(Graph<char>& graph, int id, char from, char to, QWidget* parent=nullptr) : QWidget(parent), graph(graph), id(id), from(from), to(to){
        this->setGeometry(0, 0, 20, 20);
        animations = new QSequentialAnimationGroup(this);
        path = "AHI";
        this->move(graph.adjList.get(path[0])->center);
        if(!path.empty()){
            initAnimations();
            animations->start();
        }
    }

protected:
    void paintEvent(QPaintEvent* event) override{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setBrush(Qt::darkGreen);
        painter.drawEllipse(0, 0, 20, 20);
        painter.drawText(rect(), Qt::AlignCenter, QString::number(id));
    }
};

#endif // VEHICLE_HPP
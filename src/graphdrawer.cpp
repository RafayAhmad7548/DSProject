#include "qaction.h"
#include "qapplication.h"
#include "qdebug.h"
#include "qevent.h"
#include "qinputdialog.h"
#include "qlineedit.h"
#include "qlogging.h"
#include "qnamespace.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qpushbutton.h"
#include "qtimer.h"
#include "qwidget.h"
#include "qmenu.h"
#include "graph.hpp"
#include "hash_table.hpp"
#include "linklist.hpp"

#include <climits>
#include <cstdio>
#include <string>

class GraphDrawer : public QWidget{
    Graph<char>& graph;
    char* keys;
    char* firstPressedKey;

     void drawArrow(QPainter& painter, QPointF start, QPointF end, int weight){
        QLineF line(start, end);
        QPointF mid(line.pointAt(0.5));
        painter.drawLine(line);

        double angle = std::atan2(line.dy(), -line.dx());
        double arrowSize = 10;

        QPointF arrowP1 = mid + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = mid + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);

        QPolygonF arrowHead;
        arrowHead << mid << arrowP1 << arrowP2;
        painter.drawPolygon(arrowHead);

        QPointF textPos = mid + QPointF(10 * cos(angle), 10 * sin(angle));
        painter.drawText(textPos, QString::number(weight));
    }

    void Timer(){
        for(int i=0;i<graph.adjList.count;i++){
            graph.adjList.get(keys[i])->curSignalTime--;
        }
        repaint();
    }

protected:
    void paintEvent(QPaintEvent* event) override{
        QPainter painter(this);

        for(int i=0;i<graph.adjList.count;i++){
            LinkList<Edge<char>> edges = graph.adjList.get(keys[i])->value;
            NodeList<Edge<char>>* temp = edges.head;
            while(temp != nullptr){
                painter.setBrush(Qt::black);
                if(temp->value.blocked){
                    painter.setBrush(Qt::red);
                    painter.setPen(Qt::red);
                }
                drawArrow(painter, graph.adjList.get(keys[i])->center, graph.adjList.get(temp->value.to)->center, temp->value.weight);
                temp = temp->next;
                painter.setBrush(Qt::transparent);
                painter.setPen(Qt::black);
            }
        }

        for(int i=0;i<graph.adjList.count;i++){
            painter.setBrush(Qt::gray);
            QPoint center = graph.adjList.get(keys[i])->center;
            painter.drawEllipse(center, 20, 20);
            painter.drawText(center, QString(keys[i]));

            HashNode<char, LinkList<Edge<char>>>*& node = graph.adjList.get(keys[i]);
            int time = node->curSignalTime;
            if(time == 0){
                node->signalState = !node->signalState;
                node->curSignalTime = node->signalTime;
            }
            if(node->signalState) painter.setBrush(Qt::green);
            else painter.setBrush(Qt::red);
            
            painter.drawEllipse(center+QPoint(20, -20), 10, 10);
            painter.drawText(center+QPoint(15, -15), QString::number(time));
        }

    }

    void mousePressEvent(QMouseEvent* event) override{
        qDebug()<<event->pos();
        if(event->button() == Qt::LeftButton){
            for(int i=0;i<graph.adjList.count;i++){
                QPoint center = graph.adjList.get(keys[i])->center;
                if(QPoint(event->pos() - center).manhattanLength() <= 20){
                    qDebug()<<"[LOG]: ADDING EDGE:"<<keys[i];
                    if(firstPressedKey == nullptr) firstPressedKey = &keys[i];
                    else{
                        bool ok;
                        int weight = QInputDialog::getInt(nullptr, "", "Enter weight for edge", 0, INT_MIN, INT_MAX, 1, &ok);
                        if(ok) graph.addEdge(*firstPressedKey, keys[i], weight);
                        firstPressedKey = nullptr;
                        repaint();
                    }
                }
            }
        }
    }

    void contextMenuEvent(QContextMenuEvent* event) override{
        char clicked = '\0';
        for(int i=0;i<graph.adjList.count;i++){
            QPoint center = graph.adjList.get(keys[i])->center;
            if(QPoint(event->pos() - center).manhattanLength() <= 20){
                clicked = keys[i];
            }
        }

        QMenu menu(this);

        QAction* addVertex = menu.addAction("Add Vertex");
        QAction* removeVertex = nullptr;
        QAction* removeEdge = nullptr;
        QAction* addBlock = nullptr;

        if(clicked != '\0'){
            removeVertex = menu.addAction("Remove Vertex");
            removeEdge = menu.addAction("Remove Edge");
            addBlock = menu.addAction("Add Block");
        }

        QAction* selected = menu.exec(event->globalPos());
        if(selected == nullptr) return;
        if(selected == addVertex){
            bool ok;
            std::string vertex = QInputDialog::getText(nullptr, "", "Enter Vertex char", QLineEdit::Normal, "", &ok).trimmed().toStdString();
            if(ok && !vertex.empty()){
                graph.addVertex(vertex[0]);
                init();
                repaint();
            }
        }
        else if(selected == removeVertex){
            graph.removeVertex(clicked);
            init();
            repaint();
        }
        else if(selected == removeEdge){
            bool ok;
            std::string vertex = QInputDialog::getText(nullptr, "", "Enter Edge char", QLineEdit::Normal, "", &ok).trimmed().toStdString();
            if(ok && !vertex.empty()){
                graph.removeEdge(clicked, vertex[0]);
                init();
                repaint();
            }
        }
        else if(selected == addBlock){
            bool ok;
            std::string vertex = QInputDialog::getText(nullptr, "", "Enter Edge char", QLineEdit::Normal, "", &ok).trimmed().toStdString();
            if(ok && !vertex.empty()){
                NodeList<Edge<char>>* temp = graph.adjList.get(clicked)->value.head;
                while(temp != nullptr && temp->value.to != vertex[0]){
                    temp = temp->next;
                }
                if(temp != nullptr){
                    temp->value.blocked = true;
                }
                repaint();
            }
        }
        
    }

    void resizeEvent(QResizeEvent* event) override{
        init();
        QWidget::resizeEvent(event);
    }

  public:
    GraphDrawer(Graph<char>& graph, QWidget* parent=nullptr) : QWidget(parent), graph(graph){
        this->setFixedSize(1000, 1000);
        keys = nullptr;

        QTimer* timer = new QTimer(this);
        QObject::connect(timer, &QTimer::timeout, this, &GraphDrawer::Timer);
        timer->start(1000);
        init();
    }
    ~GraphDrawer(){
        delete[] keys;
    }

    void init(){
        delete[] keys;
        keys = graph.adjList.getKeySet();
        firstPressedKey = nullptr;
        int radius = 400;
        int centerX = width()/2;
        int centerY = height()/2;

        for(int i=0;i<graph.adjList.count;i++){
            double angle = 2 * M_PI * i / graph.adjList.count;
            int x = centerX + radius * cos(angle);
            int y = centerY + radius * sin(angle);
            graph.adjList.get(keys[i])->center = QPoint(x, y);
        }
    }
};
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QPushButton>
#include <climits>

#include "graph.hpp"
#include "linklist.hpp"
#include "qboxlayout.h"
#include "qdebug.h"
#include "qdialog.h"
#include "qevent.h"
#include "qinputdialog.h"
#include "qlineedit.h"
#include "qlogging.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qwidget.h"
using namespace std;

class GraphDrawer : public QWidget{
    Graph<char>& graph;
    char* keys = nullptr;
    char* firstPressedKey;
protected:
    void paintEvent(QPaintEvent* event) override{
        QPainter painter(this);

        for(int i=0;i<graph.adjList.count;i++){
            LinkList<char> edges = graph.adjList.get(keys[i])->value;
            NodeList<char>* temp = edges.head;
            while(temp != nullptr){
                drawArrow(painter, graph.adjList.get(keys[i])->center, graph.adjList.get(temp->value)->center, temp->weight);
                temp = temp->next;
            }
        }

        painter.setBrush(Qt::transparent);
        for(int i=0;i<graph.adjList.count;i++){
            painter.drawEllipse(graph.adjList.get(keys[i])->center, 20, 20);
            painter.drawText(graph.adjList.get(keys[i])->center, QString(keys[i]));
        }
    }

    void mousePressEvent(QMouseEvent* event) override{
        for(int i=0;i<graph.adjList.count;i++){
            QPoint center = graph.adjList.get(keys[i])->center;
            if(QPoint(event->pos() - center).manhattanLength() <= 20){
                qDebug()<<keys[i];
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

    void resizeEvent(QResizeEvent* event) override{
        init();
        QWidget::resizeEvent(event);
    }

    void drawArrow(QPainter& painter, QPointF start, QPointF end, int weight){
        QLineF line(start, end);
        QPointF mid(line.pointAt(0.5));
        painter.drawLine(line);

        double angle = std::atan2(line.dy(), -line.dx());
        double arrowSize = 10;

        QPointF arrowP1 = mid + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = mid + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);

        painter.setBrush(Qt::black);
        QPolygonF arrowHead;
        arrowHead << mid << arrowP1 << arrowP2;
        painter.drawPolygon(arrowHead);

        QPointF textPos = mid + QPointF(10 * cos(angle), 10 * sin(angle));
        painter.drawText(textPos, QString::number(weight));
    }

  public:
    GraphDrawer(Graph<char>& graph, QWidget* parent=nullptr) : QWidget(parent), graph(graph){
        init();
    }
    ~GraphDrawer(){
        delete[] keys;
    }

    void init(){
        delete[] keys;
        keys = graph.adjList.getKeySet();
        firstPressedKey = nullptr;
        int radius = 200;
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

int main(int argc, char **argv){

    
    Graph<char> graph;
    graph.addVertex('A');
    graph.addVertex('B');
    graph.addVertex('C');
    graph.addVertex('D');
    graph.addVertex('E');

    graph.addEdge('A', 'B', 5);
    graph.addEdge('B', 'C', 10);
    graph.addEdge('A', 'C', 15);
    graph.addEdge('C', 'D', 7);
    graph.addEdge('D', 'E', 3);
    graph.addEdge('B', 'D', 9);
    

    QApplication app(argc, argv);
    QWidget window;

    GraphDrawer drawer(graph);
    QPushButton button("add vertex");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(&drawer);
    layout->addWidget(&button);

    QObject::connect(&button, &QPushButton::clicked, [&graph, &drawer](){
        bool ok;
        string vertex = QInputDialog::getText(nullptr, "", "Enter Vertex char", QLineEdit::Normal, "", &ok).toStdString();
        if(ok && !vertex.empty()){
            graph.addVertex(vertex[0]);
            drawer.init();
            drawer.repaint();
        }
    });

    window.setLayout(layout);
    window.show();

    return app.exec();
}
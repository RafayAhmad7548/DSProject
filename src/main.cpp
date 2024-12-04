#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
// #include <iostream>

#include "graph.hpp"
#include "linklist.hpp"
using namespace std;

class GraphDrawer : public QWidget{
    Graph<char>& graph;
protected:
    void paintEvent(QPaintEvent* event) override{
        QPainter painter(this);
        char* keys = graph.adjList.getKeySet();

        for(int i=0;i<graph.adjList.count;i++){
            LinkList<char> edges = graph.adjList.get(keys[i])->value;
            NodeList<char>* temp = edges.head;
            while(temp != nullptr){
                painter.drawLine(graph.adjList.get(keys[i])->center, graph.adjList.get(temp->value)->center);
                temp = temp->next;
            }
        }

        for(int i=0;i<graph.adjList.count;i++){
            painter.drawEllipse(graph.adjList.get(keys[i])->center, 20, 20);
            painter.drawText(graph.adjList.get(keys[i])->center, QString(keys[i]));
        }
        delete[] keys;
    }

  public:
    GraphDrawer(Graph<char> &graph, QWidget* parent=nullptr) : QWidget(parent), graph(graph){
        char* keys = graph.adjList.getKeySet();
        int radius = 200;
        int centerX = width()/2;
        int centerY = height()/2;

        for(int i=0;i<graph.adjList.count;i++){
            double angle = 2 * M_PI * i / graph.adjList.count;
            int x = centerX + radius * cos(angle);
            int y = centerY + radius * sin(angle);
            graph.adjList.get(keys[i])->center = QPoint(x, y);
        }
        delete[] keys;
    }
};

int main(int argc, char **argv){

    
    Graph<char> graph;
    graph.addVertex('A');
    graph.addVertex('B');
    graph.addVertex('C');
    graph.addVertex('D');
    graph.addVertex('E');

    graph.addEdge('A', 'B');
    graph.addEdge('B', 'C');
    graph.addEdge('A', 'C');
    graph.addEdge('C', 'D');
    graph.addEdge('D', 'E');
    graph.addEdge('B', 'D');
    

    QApplication app(argc, argv);
    GraphDrawer drawer(graph);
    drawer.show();


    return app.exec();
}
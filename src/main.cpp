#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
// #include <iostream>

#include "graph.hpp"
using namespace std;

class GraphDrawer : public QWidget{
    Graph<char>& graph;
    QPoint* centers;
protected:
    void paintEvent(QPaintEvent* event) override{
        QPainter painter(this);
        for(int i=0;i<graph.adjList.count;i++){
            painter.drawEllipse(centers[i], 20, 20);
            // painter.drawText(centers[i], QString());
        }
    }

  public:
    GraphDrawer(Graph<char> &graph, QWidget* parent=nullptr) : QWidget(parent), graph(graph){
        centers = new QPoint[graph.adjList.count];
        int radius = 200;
        int centerX = width()/2;
        int centerY = height()/2;

        for(int i=0;i<graph.adjList.count;i++){
            double angle = 2 * M_PI * i / graph.adjList.count;
            int x = centerX + radius * cos(angle);
            int y = centerY + radius * sin(angle);
            centers[i] = QPoint(x, y);
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
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
// #include <iostream>
using namespace std;

class ShapeDrawer : public QWidget{
protected:
    void paintEvent(QPaintEvent* event) override{
        QPainter painter(this);
        // painter.setPen(Qt::black);
        painter.drawLine(50, 150, 300, 150);
        painter.drawEllipse(100, 100, 25, 25);
    }
};

int main(int argc, char **argv){

    QApplication app(argc, argv);
    ShapeDrawer drawer;
    drawer.resize(200, 300);
    drawer.show();
    

    return app.exec();
}
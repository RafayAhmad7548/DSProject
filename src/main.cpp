#include <fstream>
#include <string>

#include "linklist.hpp"
#include "qapplication.h"
#include "graph.hpp"
#include "graphdrawer.cpp"
#include "vehicle.hpp"

using namespace std;

int main(int argc, char **argv){
    QApplication app(argc, argv);
    QWidget window;
    window.setFixedSize(1000, 1000);

    Graph<char> graph;
    for(int i=0;i<26;i++) graph.addVertex('A'+i);

    ifstream roadNetwork("road_network.csv");
    string line;
    getline(roadNetwork, line);
    while(getline(roadNetwork, line)){
        graph.addEdge(line[0], line[2], stoi(line.substr(4, line.length())));
    }
    roadNetwork.close();

    ifstream traffic("traffic_signals.csv");
    getline(traffic, line);
    while(getline(traffic, line)){
        graph.adjList.get(line[0])->signalTime = stoi(line.substr(2, line.length()));
        graph.adjList.get(line[0])->curSignalTime = stoi(line.substr(2, line.length()));
    }
    traffic.close();

    ifstream blocks("road_closures.csv");
    getline(blocks, line);
    while(getline(blocks, line)){
        string status = line.substr(line.find_last_of(',')+1, line.length());
        if(status == "Blocked" || status == "Under Repair"){
            NodeList<Edge<char>>* temp = graph.adjList.get(line[0])->value.head;
            while(temp != nullptr && temp->value.to == line[2]){
                temp = temp->next;
            }
            if(temp != nullptr){
                temp->value.blocked = true;
            }
        }
    }
    blocks.close();

    // LinkList<Vehicle*> vehicles;
    // ifstream vehicleFile("vehicles.csv");
    // getline(vehicleFile, line);
    // while(getline(vehicleFile, line)){
    //     Vehicle* vehicle = new Vehicle(graph, stoi(line.substr(1, line.find_first_of(','))), line[line.length()-3], line[line.length()-1], &window);
    //     vehicles.insert(vehicle);
    // }

    GraphDrawer drawer(graph, &window);
    drawer.setGeometry(0, 0, 1000, 1000);

    Vehicle vehicle(graph, 1, 'A', 'B', &window);
    vehicle.setGeometry(0, 0, 20, 20);

    window.show();

    return app.exec();
}
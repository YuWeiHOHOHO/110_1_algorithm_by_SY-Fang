#pragma once
#include <vector>

using namespace std;

class Point;
class Edge;
class Vertex;
class Graph;
class Wire;



class Point {
public:
    int x;
    int y;
};

class Wire
{
public:
    int index;
    Point start;
    Point end;
};

class Edge {
public:
    Vertex* otherVertex;
    int w=1; //Weight
    int wire = 0;
};

class Vertex
{
public:
    //variable
    int index, minWeight= 2000000000;
    int x, y; //座標
    vector<Vertex*> p;//parents
    vector<Edge> edge; //相鄰的vertex , weight
    bool found = false;
    bool inFindingList = false;
    //function
    void clear() {
        minWeight = 2000000000;
        p.clear();
        found = false;
        inFindingList = false;
    };
};

class Graph
{
public:
    //veriable
    vector<vector<Vertex>> map;
    int n;
    //function
    Graph(int grid);
    bool isAllFound();
    void clear();
};

Graph::Graph(int grid)
{
    //initialization
        //build map
    map.resize(grid);
    for (int i = 0; i < grid; i++) {
        map.at(i).resize(grid);
    }
    n = grid;

    //build vertex and edge
    for (int i = 0; i < grid; i++) {
        for (int j = 0; j < grid; j++) {
            //init vertex
            map.at(i).at(j).index = i * grid + j;
            map.at(i).at(j).x = i;
            map.at(i).at(j).y = j;
            //init edge
            Edge tempEdge;
            if (i > 0) {//建立左邊的邊
                tempEdge.otherVertex = &map.at(i - 1).at(j);
                map.at(i).at(j).edge.push_back(tempEdge);
            }
            if (i < grid-1) {//建立右邊的邊
                tempEdge.otherVertex = &map.at(i+1).at(j);
                map.at(i).at(j).edge.push_back(tempEdge);
            }
            if (j > 0) {//建立上面的邊
                tempEdge.otherVertex = &map.at(i).at(j-1);
                map.at(i).at(j).edge.push_back(tempEdge);
            } 
            if (j < grid - 1) {//建立下面的邊
                tempEdge.otherVertex = &map.at(i).at(j+1);
                map.at(i).at(j).edge.push_back(tempEdge);
            }
        }
    }
}

inline bool Graph::isAllFound() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!map.at(i).at(j).found)return false;
        }
    }
    return true;
}

inline void Graph::clear() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            map.at(i).at(j).clear();
        }    
    }
}

#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include "graph.h"

using namespace std;

void addVertexIntoMST(Graph& graph, vector<Vertex*> &VertexAround, Vertex &v) {
    
    v.found = true;
    v.inFindingList = false;
    for (int i = 0; i < v.edge.size(); i++) {
        if (!v.edge.at(i).otherVertex->found) {
            //add around vertex into VertexAround
            if (!v.edge.at(i).otherVertex->inFindingList) {
                v.edge.at(i).otherVertex->inFindingList = true;
                VertexAround.push_back(v.edge.at(i).otherVertex);
            }
            //relax
            if (v.minWeight + v.edge.at(i).w < v.edge.at(i).otherVertex->minWeight) {
                v.edge.at(i).otherVertex->minWeight = v.minWeight + v.edge.at(i).w;
                v.edge.at(i).otherVertex->p.clear();
                v.edge.at(i).otherVertex->p=v.p;
                v.edge.at(i).otherVertex->p.push_back(&v);
            }
        }
    }
}

string str(int i) {
    stringstream ss;
    string s;
    ss << i;
    ss >> s;
    return s;
}

void wireWeightUpdate(Edge &e, int capacity) {
    e.w++;
    if (e.wire >= capacity)e.w = 2000000;
}

void findpath_Dijkstra(Graph& graph,Wire w, vector<string> &output, int capacity) {

    Vertex *startVertex = &graph.map.at(w.start.x).at(w.start.y);
    Vertex *endVertex = &graph.map.at(w.end.x).at(w.end.y);
    vector<Vertex*> VertexAround;
    int edgeCount = 0;
    
    graph.clear();

    //start point init
    startVertex->minWeight = 0;
    addVertexIntoMST(graph,VertexAround, *startVertex);

    while (!graph.isAllFound())
    {
        //fin min cost
        Vertex *minVertex = new Vertex;
        int minIndex;
        minVertex->minWeight = 2000000000;
        for (int i = 0; i < VertexAround.size(); i++) {
            if (VertexAround.at(i)->minWeight < minVertex->minWeight) {
                minVertex = VertexAround.at(i);
                minIndex = i;
            }
        }

        VertexAround.erase(VertexAround.begin()+ minIndex);
        addVertexIntoMST(graph, VertexAround, *minVertex);

        if (minVertex->x == w.end.x && minVertex->y == w.end.y)break;
    }
    
   //put into output list
   
   // cout << w.index << " " << endVertex->p.size() << endl;
   output.push_back(str(w.index) + " " + str(endVertex->p.size()));
    for (int i = 1; i < endVertex->p.size(); i++) {
       // cout << endVertex->p.at(i-1)->x << " " << endVertex->p.at(i-1)->y <<" " << endVertex->p.at(i)->x << " " << endVertex->p.at(i)->y << endl;
        output.push_back(str(endVertex->p.at(i - 1)->x) + " " + str(endVertex->p.at(i - 1)->y)+ " "+str(endVertex->p.at(i)->x)+ " " +str(endVertex->p.at(i)->y));
    }
    //cout << endVertex->p.back()->x << " " << endVertex->p.back()->y << " " << w.end.x << " " << w.end.y << endl;
    output.push_back(str(endVertex->p.back()->x)+" "+str(endVertex->p.back()->y)+" "+ str(w.end.x)+ " " + str(w.end.y));

    //update weight
    for (int i = 1; i < endVertex->p.size(); i++)
    {
        for (int j = 0; j < endVertex->p.at(i-1)->edge.size(); j++)
        {
            if (endVertex->p.at(i - 1)->edge.at(j).otherVertex->index == endVertex->p.at(i)->index) {
                endVertex->p.at(i - 1)->edge.at(j).wire++;
                wireWeightUpdate(endVertex->p.at(i - 1)->edge.at(j), capacity);
            }
        }
    }
    for (int j = 0; j < endVertex->edge.size(); j++)
    {
        if (endVertex->edge.at(j).otherVertex->index == endVertex->p.back()->index) {
            endVertex->edge.at(j).wire++;
            wireWeightUpdate(endVertex->edge.at(j), capacity);
        }
    }
    for (int i = 1; i < endVertex->p.size(); i++)
    {
        for (int j = 0; j < endVertex->p.at(i)->edge.size(); j++)
        {
            if (endVertex->p.at(i)->edge.at(j).otherVertex->index == endVertex->p.at(i-1)->index) {
                endVertex->p.at(i)->edge.at(j).wire++;
                wireWeightUpdate(endVertex->p.at(i)->edge.at(j), capacity);
            }
        }
    }
    for (int j = 0; j < endVertex->p.back()->edge.size(); j++)
    {
        if (endVertex->p.back()->edge.at(j).otherVertex->index == endVertex->index) {
            endVertex->p.back()->edge.at(j).wire++;
            wireWeightUpdate(endVertex->p.back()->edge.at(j), capacity);
        }
    }
    cout << "";
}

int main(int argc, char** argv)
{
    //////////////////////////initialization///////////////////////////////////
    int n, capacity = 0, netNum = 0;
    fstream fin;
    vector<Wire> wireList;
    vector<string> output;
    //////////////////////////parser///////////////////////////////////////////
    cout << "start!!" << endl;
     if (argc != 3)
     {
         cout << "Usage: ./[exe] [input file] [output file]" << endl;
         //    system("pause");
         exit(1);
     }

     // open the input file

     fin.open(argv[1], fstream::in);
     if (!fin.is_open())
     {
         cout << "Error: the input file is not opened!!" << endl;
         exit(1);
     }

     string tempStr;

     fin >> tempStr; //n
     fin >> n;
     fin >> n; //範圍
     Graph graph(n);

     fin >> tempStr; //capacity
     fin >> capacity;

     fin >> tempStr; //num
     fin >> tempStr; //net
     fin >> netNum;

     for (int i = 0; i < netNum; i++)
     {
         Wire tempWire;
         fin >> tempWire.index;
         fin >> tempWire.start.x;
         fin >> tempWire.start.y;
         fin >> tempWire.end.x;
         fin >> tempWire.end.y;
         wireList.push_back(tempWire);
         findpath_Dijkstra(graph, tempWire, output, capacity);
     }

     //output
     fstream fout;
     fout.open(argv[2], fstream::out);
     if (!fout.is_open())
     {
         cout << "Error: the output file is not opened!!" << endl;
         exit(1);
     }
     
     for (int i = 0; i < output.size(); i++)
     {
         fout << output.at(i) << endl;
     }

     cout << "finished!!" << endl;
    return 0;
}
#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <iostream>
/*
    @author Ýbrahim Taha Aksu
    id:21401946
    section:2
 */
using namespace std;
#include"LinkedList.h"


class Graph
{
    public:
        Graph(int vertice);
        virtual ~Graph();
        void addVertice(int id, string name,int arr[],string strarr[],int size);
        void List();
        void rangedTraverse(string name, int cost);// for listCommunicationsLowerThan ++
        void listCommunications(string name);//++
        void connectedComponents();//++
        void mostcentralHost();
        void AverageClusteringCoefficients();//++

    private:
        void findComponents(int** L,int& componentNum,int* arr1);
        double averageClustering(int id);
        void findAllShortestPaths(int**& dArr,int sourceID,int targetID,int& pathNum,int& pathLength);
        double betweennessCentrality(int* arr,int size,int id);
        int GetIndex(int id);
        LinkedList** vertices;//Holding the vertices i.e head nodes of all linked lists
        int numberOfVertices;
        bool has(int* arr,int id,int size);





};

#endif // GRAPH_H

#include "HostNet.h"
#include <iostream>
#include <fstream>
/*
    @author Ýbrahim Taha Aksu
    id:21401946
    section:2
 */
HostNet::HostNet(const string hName)
{
    ifstream infile;
    infile.open(hName);

    int verticeNum;
    infile>>verticeNum;
    g= new Graph(verticeNum);

    int firstColumn[verticeNum];
    string secondColumn[verticeNum];
    int thirdColumn[verticeNum];
    int allEdges[(verticeNum-1)*(verticeNum-1)];//it can at most have this many edges
    int edgeIndex=0;
    for(int i=0;i<verticeNum;i++)
    {
        infile>>firstColumn[i];
        infile>>secondColumn[i];
        infile>>thirdColumn[i];
        for(int j=0;j<thirdColumn[i];j++)
            infile>>allEdges[edgeIndex++];
    }
    edgeIndex=0;//We will start iterating starting from scratch
    for(int i=0;i<verticeNum;i++)
    {
        int adjacents[thirdColumn[i]];//it has thirdColumn[i] many adjacent nodes
        for(int j=0;j<thirdColumn[i];j++)
            adjacents[j]=allEdges[edgeIndex++];
        string adjacentNames[thirdColumn[i]];

        for(int j=0;j<thirdColumn[i];j++)//loop to fill adjacentNames
        {
            int id=adjacents[j];//Find this id's name
            //To finds it's id find its index and the name is seconcColumn[index]

            int index;
            for(int k=0;k<verticeNum;k++)
            {
                if(firstColumn[k]==id)
                {
                    index=k;
                    break;
                }
            }

            //Now we have the index to id
            adjacentNames[j]=secondColumn[index];
        }
        g->addVertice(firstColumn[i],secondColumn[i],adjacents,adjacentNames,thirdColumn[i]);
    }
}

HostNet::HostNet(const HostNet& hNet)
{

}

HostNet::~HostNet()
{

}

void HostNet::listCommunicationsLowerThan(const string aname, const int cost)
{
    g->rangedTraverse(aname,cost);
}

void HostNet::listCommunicationsOnHubHost(const string hname)
{
    g->listCommunications(hname);
}

void HostNet::findConnectedComponents()
{
    g->connectedComponents();
}

void HostNet::displayMostCentralHosts()
{
    g->mostcentralHost();
}

void HostNet::displayAverageClusteringCoefficients()
{
    g->AverageClusteringCoefficients();
}

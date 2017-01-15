#include <iostream>
#include "Graph.h"
#include <string>
#include"HostNet.h"
/*
    @author ibrahim Taha Aksu
    id:21401946
    section:2
 */
using namespace std;

int main()
{
    HostNet h("hostlar.txt");
    h.listCommunicationsLowerThan("m3",2);
    h.listCommunicationsLowerThan("m4",4);
    h.listCommunicationsLowerThan("m23",2);
    cout<<endl;
    h.listCommunicationsOnHubHost("m1");
    cout<<endl;

    h.findConnectedComponents();
    cout<<endl;

    h.displayMostCentralHosts();

    cout<<endl;

    h.displayAverageClusteringCoefficients();
    cout<<endl;



    /*
    Graph g(5);
    int arr[3]={2,3,5};
    string strarr[3]={"m2","m3","m5"};
    g.addVertice(1,"m1",arr,strarr,3);
    int arr2[2]={1,3};
    string strarr2[2]={"m1","m3"};
    g.addVertice(2,"m2",arr2,strarr2,2);
    int arr3[3]={1,2,4};
    string strarr3[3]={"m1","m2","m4"};
    g.addVertice(3,"m3",arr3,strarr3,3);
    int arr4[2]={3,5};
    string strarr4[2]={"m3","m5"};
    g.addVertice(4,"m4",arr4,strarr4,2);
    int arr5[2]={1,4};
    string strarr5[2]={"m1","m4"};
    g.addVertice(5,"m5",arr5,strarr5,2);
    g.listCommunications("m1");
/*
    int** darr;
    int pathNum;
    int pathLength;
    g.findAllShortestPaths(darr,1,2,pathNum,pathLength);
    for(int i=0;i<pathNum;i++)
    {
        cout<<"first path: ";
        for(int j=0;j<pathLength;j++)
        {
            cout<<darr[i][j]<<"     ";
        }
        cout<<endl;
    }

    Graph g(3);
    int arr[0]={};
    string strarr[0]={};
    g.addVertice(1,"a",arr,strarr,0);
    int arr2[1]={3};
    string strarr2[1]={"c"};
    g.addVertice(2,"b",arr2,strarr2,1);
    int arr3[1]={2};
    string strarr3[1]={"b"};
    g.addVertice(3,"c",arr3,strarr3,1);
    g.AverageClusteringCoefficients();
    //g.mostcentralHost();
    //g.connectedComponents();
    //g.listCommunications("b");
    //g.rangedTraverse("b",2);
    g.mostcentralHost();*/


    return 0;
}

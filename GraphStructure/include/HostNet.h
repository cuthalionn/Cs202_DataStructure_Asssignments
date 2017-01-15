#ifndef HOSTNET_H
#define HOSTNET_H
#include <string>
#include"Graph.h"

using namespace std;
/*
    @author Ýbrahim Taha Aksu
    id:21401946
    section:2
 */


class HostNet
{
    public:
    HostNet(const string hName);
    HostNet(const HostNet& hNet); // copy constructor
    ~HostNet(); // destructor
    void listCommunicationsLowerThan(const string aname, const int cost);
    void listCommunicationsOnHubHost(const string hname);
    void findConnectedComponents();
    void displayMostCentralHosts();
    void displayAverageClusteringCoefficients();
    // ...
    // define other public member functions here,
    // if you have any
    private:
        Graph* g;
    // ...
    // define your data members here
    // define private member functions here, if you have any
};

#endif // HOSTNET_H

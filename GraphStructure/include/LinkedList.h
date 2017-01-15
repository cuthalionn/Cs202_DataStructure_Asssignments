#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include <queue>
/*
    @author Ýbrahim Taha Aksu
    id:21401946
    section:2
 */
using namespace std;
struct Node{
    int id;
    string name;
    Node* next;
};
class LinkedList
{
    public:
        LinkedList();
        virtual ~LinkedList();
        void addNode(int id,string name);
        void List(queue<int>* q,int* arr,int& size);
        void ListCount(queue<int>* q,int* arr,int& size);
        void ListQueue(queue<int>* q,int* arr,int& size,int* branches,int& branchSize);
        Node* getRoot();
        void fillArray(int* arr,int& numOfElements);
        void fillArrayName(string* arr);
        bool has(int id);
        void print();
        int NumberOfElements();

    private:
        bool has(int* arr,int id,int size);
        Node* root;
};

#endif // LINKEDLIST_H

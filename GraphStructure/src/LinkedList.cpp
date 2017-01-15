#include "LinkedList.h"
#include <string>
#include <iostream>
/*
    @author Ýbrahim Taha Aksu
    id:21401946
    section:2
 */
using namespace std;
LinkedList::LinkedList()
{
    root=NULL;
}

LinkedList::~LinkedList()
{
    //dtor
}
void LinkedList::addNode(int id, string name)
{
    Node* newNode= new Node;
    newNode->id=id;
    newNode->name=name;
    newNode->next=NULL;
    if(root==NULL){
        root=newNode;
        return;
    }
    newNode->next=root->next;
    root->next=newNode;

}
void LinkedList::List(queue<int>* q,int* arr,int& size)
{
    Node*cur=root->next;//We do not care about the root for this very implementation
    while(cur!=NULL)
    {
        if(!has(arr,cur->id,size)){
        cout<<cur->name;
        cout<<",";
        q->push(cur->id);
        arr[size++]=cur->id;
        }
        cur=cur->next;
    }

}
bool LinkedList::has(int* arr, int id, int size)
{
    for(int i=0;i<size;i++)
        if(arr[i]==id)
            return true;
    return false;
}

Node* LinkedList::getRoot()
{
    return root;
}
void LinkedList::fillArray(int* arr,int& numOfElements)
{
    Node* cur= root->next;
    numOfElements=0;
    while(cur!= NULL)
    {
        arr[numOfElements++]=cur->id;
        cur=cur->next;
    }

}
void LinkedList::fillArrayName(string* arr)
{
    Node* cur= root->next;
    int numOfElements=0;
    while(cur!= NULL)
    {
        arr[numOfElements++]=cur->name;
        cur=cur->next;
    }
}

bool LinkedList::has(int id)
{
    Node* cur= root;
    while(cur!=NULL)
    {
        if(cur->id==id)
            return true;
        cur=cur->next;
    }
    return false;
}
void LinkedList::ListCount(queue<int>* q, int* arr, int& size)
{
    Node*cur=root->next;//We do not care about the root for this very implementation
    while(cur!=NULL)
    {
        if(!has(arr,cur->id,size)){
        q->push(cur->id);
        arr[size++]=cur->id;
        }
        cur=cur->next;
    }
}
void LinkedList::ListQueue(queue<int>* q, int* arr, int& size,int* branches,int& currentIndex)
{
    Node*cur=root->next;//We do not care about the root for this very implementation
    //arr[size++]=q->front();
    currentIndex=0;
    while(cur!=NULL)
    {
        if(!has(arr,cur->id,size)){
        q->push(cur->id);
        branches[currentIndex++]=cur->id;
        }
        cur=cur->next;
    }
}

void LinkedList::print()
{
    Node* cur=root;
    while(cur!=NULL){
        cout<<cur->name<<",";
        cur=cur->next;
    }
    cout<<endl;
}
int LinkedList::NumberOfElements()
{
    Node* cur= root;
    int count=0;
    while(cur!=NULL)
    {
        count++;
        cur=cur->next;
    }
    return count;
}

#include "AVL.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;
void height(Node* start,int &num);
AVL::AVL()
{
    root = NULL;
}

AVL::~AVL()
{
    //dtor
}
void AVL::insert(string str)
{
    Node* org = new Node();
    org->left=NULL;
    org->right=NULL;
    org->str=str;
    if(root== NULL)
    {
        root=org;
        return;
    }

    Node* cur= root;
    Node* parent;
    bool right;
    while(cur!=NULL)
    {
        parent = cur;
        if(cur->str.compare(str)==1)
        {
            cur=cur->left;
            right=false;
        }
        else
        {
            cur=cur->right;
            right=true;
        }
    }
    if(right)
        parent->right=org;
    else
        parent->left=org;


    Node* current= root;
    Node* rotPlace=NULL;
    int count=0;
    bool subtree;//TRUE for right
    bool child;
    parent=root;
    bool parentDir;
    Node* rotParent=NULL;
    while(current!=NULL)
    {


        if(!checkBalance(current))
        {
            rotParent=parent;
            rotPlace=current;
            parentDir=right;
            count=0;
        }
        parent=current;
         if(current->str.compare(str)==1)
        {
            current=current->left;
            if(count==0)
                child=false;
            if(count==1)
                subtree=false;
             right=false;
        }
        else
        {
            current=current->right;
            if(count==0)
                child=true;
            if(count==1)
                subtree=true;
            right=true;
        }
        count++;
    }
    if(rotPlace==NULL)
        return;
    //Insertion is in left subtree of left child
    else if(child==false && subtree==false)
    {
        if(rotPlace==root)
        {
            rotateRight(rotPlace);
            root = rotPlace;
        }
        else
        {
            rotateRight(rotPlace);
            if(parentDir)
                rotParent->right=rotPlace;
            else
            rotParent->left=rotPlace;
        }
    }
    //Insertion is in right subtree of right child
    else if(child==true && subtree==true)
    {
        if(rotPlace==root)
        {
            rotateLeft(rotPlace);
            root=rotPlace;
        }
        else
        {
            rotateLeft(rotPlace);
            if(parentDir)
                rotParent->right=rotPlace;
            else
                rotParent->left=rotPlace;
        }

    }
    //Insertion is in right subtree of left child
    else if(child==false && subtree==true)
    {
        if(rotPlace==root)
        {
            //left rotation
            rotateLeft(rotPlace->left);
            //right rotation
            rotateRight(rotPlace);
            root=rotPlace;
        }
        else
        {
            //left rotation
            rotateLeft(rotPlace->left);
            //rightRotation
            rotateRight(rotPlace);
            if(parentDir)
                rotParent->right=rotPlace;
            else
                rotParent->left=rotPlace;
        }

    }
    //Insertion is in left subtree of right child
    else
    {
        if(rotPlace==root)
        {
            //right rotation
            rotateRight(rotPlace->right);
            //left rotation
            rotateLeft(rotPlace);
            root=rotPlace;
        }
        else
        {
            //right rotation
            rotateRight(rotPlace->right);
            //left rotation
            rotateLeft(rotPlace);
            if(parentDir)
                rotParent->right=rotPlace;
            else
                rotParent->left=rotPlace;
        }
    }

}
void AVL::rotateRight(Node* &node)
{
        Node* node1 = node->left;
        node->left = node1->right;
        node1->right = node;
        node =node1;
}

void AVL::rotateLeft(Node* &node)
{
    Node* node1 = node->right;
    node->right = node1->left;
    node1->left = node;
    node= node1;
}
void preorder(Node* current)
{
    if(current==NULL)
        return;
    cout<<current->str<<endl;
    preorder(current->left);
    preorder(current->right);
}
void AVL::Preorder()
{
    Node* current=root;
    preorder(current);
}
void height(Node* start,int &num)
 {
    if(start == NULL)
        return;
    if(start->left==NULL && start->right == NULL)
        num+=1;
    else{
    int num1=0,num2=0;
    height(start->left,num1);
    height(start->right,num2);
    num = (num1>num2) ? num1:num2;
    num++;
    }
    return;
 }

bool AVL::checkBalance(Node* cur)
{
    if(cur== NULL)
		return true;
	int num=0;
    height(cur->left,num);
	int num2 =0;
	height(cur->right,num2);
	bool result=(abs(num-num2)<=1) ? 1:0 ;// if the absolute value of height difference is less than 1 result gets 1 otherwise gets 0.
	return( result&&checkBalance(cur-> left)&&checkBalance(cur->right));
}

bool AVL::search(string str)
{
    Node* cur = root;
    while(cur!=NULL && cur->str.compare(str)!=0)
    {
        if(cur->str.compare(str)==1)
            cur=cur->left;
        else
            cur=cur->right;
    }
    if(cur==NULL)
        return false;
    else
        return true;
}
void findSim(Node* cur,string prefix,string& result)
{
    if(cur==NULL)
        return;
    findSim(cur->left,prefix,result);
    if(cur->str.find(prefix)==0)//means it has the prefix
        result+=" "+cur->str;
    findSim(cur->right,prefix,result);
}
void AVL::findSimilar(string prefix, string& result)
{
    Node* firstInclude=root;
    while(firstInclude->str.find(prefix)!=0)
    {
        if(firstInclude->str.compare(prefix)==1)
            firstInclude=firstInclude->left;
        else
            firstInclude=firstInclude->right;

        if(firstInclude==NULL)
            return;//means no words with that prefix exist
    }
    //handle the non existing case!
    findSim(firstInclude,prefix,result);
}


#include "Graph.h"
#include <string>
#include <queue>          // std::queue
using namespace std;
/*
    @author Ýbrahim Taha Aksu
    id:21401946
    section:2
 */
Graph::Graph (int vertice)
{
    vertices = new LinkedList*[vertice];
    numberOfVertices=0;
}

Graph::~Graph()
{
    //dtor
}

void Graph::addVertice(int id, string name, int arr[], string strarr[], int size)
{

    LinkedList* L = new LinkedList;
    L->addNode(id,name);//being the root
    int count=0;
    for(int i=0;i<size;i++)
    {
        L->addNode(arr[count],strarr[count]);
        count++;
    }
    vertices[numberOfVertices]=L;
    numberOfVertices++;
}
/*void Graph::List()
{
    for(int i=0;i<numberOfVertices;i++)
    {
        vertices[i]->List();
        cout<<endl;
    }

}*/
void Graph::rangedTraverse(string name, int cost)
{
    int rangeSoFar=1;
    int id;
    for(int i=0;i<numberOfVertices;i++)
    {
        if(vertices[i]->getRoot()->name==name)
        {
            id=vertices[i]->getRoot()->id;
            break;
        }//vertices[something] is a pointer to a linkedlist
        if(i==numberOfVertices-1)
        {
            cout<<name<<" does not exist in the host network"<<endl;
            return;
        }
    }
    //so id is the id of the node provided
    queue<int> q;
    q.push(id);
    queue<int>* p=&q;
    int* marked = new int[numberOfVertices];
    marked[0]=id;
    int markedSize=1;
    int index;
    while(rangeSoFar<cost && !q.empty())
    {
        int size= q.size();
        for(int i=0;i<size;i++){
            index = GetIndex(q.front());
            //we should get the index correspondence of id because index is the id.
            vertices[index]->List(p,marked,markedSize);//prints every adjacent node to current node and pushes them to queue
            q.pop();
        }

        rangeSoFar++;
    }
    cout<<endl;
    delete[] marked;
}
int Graph::GetIndex(int id)
{
    int res;
     for(int i=0;i<numberOfVertices;i++)
    {
        if(vertices[i]->getRoot()->id==id)
        {
            res=i;
            break;
        }//vertices[something] is a pointer to a linkedlist
    }
    return res;
}

void Graph::listCommunications(string name)
{
    /*TO DO:
        take the given node's all adjacent nodes
        compare them 1 by 1 print any 2 node that does
        not have an edge between them
     */
    int index;
    for(int i=0;i<numberOfVertices;i++)
    {
        if(vertices[i]->getRoot()->name==name)
        {
            index=i;
            break;
        }//vertices[something] is a pointer to a linkedlist
    }

    int* adjacentsId = new int[numberOfVertices];
    string* adjacentsName = new string[numberOfVertices];
    int numOfElements;
    vertices[index]->fillArray(adjacentsId,numOfElements);// So now adjacentsId is filled with the linked list elements' ids
    vertices[index]->fillArrayName(adjacentsName);
    cout<<"If "<<name<<" is considered as hub these routes are possible: "<<endl;
    for(int i=0;i<numOfElements;i++){
        for(int j=i+1;j<numOfElements;j++)
        {
            int nodeIndex=GetIndex(adjacentsId[i]);//NodeIndex is the index of the linked list that belonges to the node with id adjacentsId[i]
            if(!vertices[nodeIndex]->has(adjacentsId[j]))//Checking if the linked list at nodeIndex has the id adjacentsId[j]
            {
                cout<<"<"<<adjacentsName[i]<<","<<adjacentsName[j]<<">"<<endl;
            }
        }
    }
    delete[] adjacentsId;
    adjacentsId=NULL;

    delete[] adjacentsName;
    adjacentsName=NULL;

}

void Graph::connectedComponents()
{
    /*TO DO:
        put all vertices in an array called not traversed
        start traversing from the very first element take every element out
        from the array that is traversed. If the traversal finished but the array is not empty
        keep doing it with the next element in the array. Every additional traversal is a new component
        and the number of steps in traversal is the nodes in that particular traversal
    */

     int** components;
     components = new int*[numberOfVertices];//max size is eq to vertice number
     int numberOfComponents=0;
     int* sizes= new int[numberOfVertices];
     findComponents(components,numberOfComponents,sizes);

     cout<<"There are "<<numberOfComponents<<" components:"<<endl;
     for(int i=0;i<numberOfComponents;i++)
        cout<<"For component "<<i<<": "<<sizes[i]<<" nodes"<<endl;
     //Deleting the arrays
     for(int i=0;i<numberOfComponents;i++){
            delete[] components[i];
            components[i]=NULL;
     }
     delete[] components;
     components=NULL;

     delete[] sizes;
     sizes=NULL;
}

void Graph::mostcentralHost()
{
    /*
        TO DO
        use the algorithm from previous method to find components.Put the set of pointers in an double sized linkedlist where every row corresponds
        to a component and columns to included nodes.
        For example for 1-2 and 3 you have two rows. 1st row having ids 1 and 2. Second only 3
        For every component find betweenness of each node take the biggest one and print it.
     */

     int** components;
     components = new int*[numberOfVertices];//max size is eq to vertice number
     int numberOfComponents=0;
     int* sizes= new int[numberOfVertices];
     findComponents(components,numberOfComponents,sizes);

     int* arr;
     double maxBetweenness;
     int maxID;
     for(int i=0;i<numberOfComponents;i++)
     {

         arr=components[i];
         maxBetweenness=betweennessCentrality(arr,sizes[i],components[i][0]);
         maxID=components[i][0];
         for(int j=0;j<sizes[i];j++)
         {

             double value= betweennessCentrality(arr,sizes[i], components[i][j]);
             if(value>maxBetweenness)
             {
                 maxBetweenness=value;
                 maxID=components[i][j];
             }
         }
         cout<<"Most central node in component "<<i+1<<": "<<vertices[GetIndex(maxID)]->getRoot()->name<<endl;
     }


     //Deleting the arrays
     for(int i=0;i<numberOfComponents;i++){
            delete[] components[i];
            components[i]=NULL;
     }
     delete[] components;
     components=NULL;

     delete[] sizes;
     sizes=NULL;
}
double Graph::betweennessCentrality(int* arr,int size,int id)
{
    /*  TO DO
        given the particular id in the connected component
        put all other elements in an array, pair them 1by1
        find shortest paths between these pairs. The betweenness is
        equal to number of total shortest paths that include the
        node with id over the number of total shortest paths
     */

    int others[size-1];
    int curIndex=0;
    double pathsWithID=0;
    double totalPaths=0;
    int** dArr;
    for(int i=0;i<size;i++)
    {
        if(arr[i]!=id){
            others[curIndex++]=arr[i];
        }
    }
    size=size-1;//size of others

    for(int i=0;i<size;i++)
    {
        for(int j=i+1;j<size;j++)
        {
            int pathNum=0;
            int pathLength=0;
            findAllShortestPaths(dArr,others[i],others[j],pathNum,pathLength);
            for(int k=0;k<pathNum;k++)
            {
                if(dArr[k][pathLength-1]==others[j])//If true it is one of the shortest paths
                {
                    for(int m=0;m<pathLength;m++)
                        if(dArr[k][m]==id){
                            pathsWithID++;
                            break;
                        }
                    totalPaths++;
                }

            }
        }
    }
    for(int i=0;i<totalPaths;i++)
        delete[] dArr[i];
    delete[] dArr;
     /*
        About finding the paths:
        after you choose a pair start from one of the nodes a breath first traversal for every path hold
        a linked list having all the nodes passed through in that node. When one of the nodes reaches the target
        delete others which already have the same number of nodes with the min one but not reached yet.
        So in this step you have all of the shortest paths now find how many of them have the node with id. Add these numbers to
        corresponding counters and continue with the next pair.
     */
    return pathsWithID/totalPaths;
}
void Graph::findAllShortestPaths(int**& dArr, int sourceID, int targetID,int& pathNum,int& pathLength)
{
    dArr = new int*[numberOfVertices*numberOfVertices];//Pointers to the paths
    pathNum=0;//will be index to dArr
    queue<int> q;
    q.push(sourceID);
    queue<int>* p=&q;
    int* marked=new int[numberOfVertices];
    int markedSize=0;
    int* branched = new int[numberOfVertices];
    int branchIndex=0;
    pathLength=0;
    while(!q.empty())
    {
        if(has(branched,q.front(),branchIndex))
        {
            q.pop();
            continue;
        }
        bool done=false;
        int size= q.size();
        bool PatternsChanged=false;
        queue<int> toBeAddedToMarked;//addition
        for(int i=0;i<size;i++){
            branched[branchIndex++]=q.front();
            int index = GetIndex(q.front());
            int* branches = new int[numberOfVertices];
            int branchesSize;
            vertices[index]->ListQueue(p,marked,markedSize,branches,branchesSize);
            if(branchesSize>0){
                PatternsChanged=true;
            }
            else
                continue;
            if(pathNum==0)
            {
                for(int j=0;j<branchesSize;j++)
                {
                    dArr[pathNum++]=new int[numberOfVertices];//dArr[number] is an int pointer
                    dArr[j][pathLength]= branches[j];
                    if(branches[j]==targetID)
                        done=true;
                }
            }
            else{
                int changingPaths[pathNum];
                int pathIndex=0;
                for(int j=0;j<pathNum;j++)//Find all path ending with the current id
                {
                    if(dArr[j][pathLength-1]==q.front())
                        changingPaths[pathIndex++]=j;
                }

                for(int i=0;i<pathIndex;i++)//Path index is the number of paths to be changed
                {
                    int m=1;
                    for(int j=0;j<branchesSize-1;j++)//The number of times we need to copy the path: incase if there are more than one branch we need create copies
                    {
                        dArr[pathNum++]=new int[numberOfVertices];
                        for(int k=0;k<pathLength;k++)
                        {
                            dArr[pathNum-1][k]=dArr[changingPaths[i]][k];
                        }//copy loop
                        dArr[pathNum-1][pathLength]=branches[m];
                        if(branches[m++]==targetID)
                            done=true;


                        //dArr[changingPaths[i]] the path where we need to add
                    }
                    dArr[changingPaths[i]][pathLength]=branches[0];
                    if(branches[0]==targetID)
                        done=true;


                }
            }

            //Check if done is true now
            //Create path arrays
            toBeAddedToMarked.push(q.front());//addition
            q.pop();
            delete[] branches;
            branches=NULL;
        }
       int size1=toBeAddedToMarked.size();//addition
        for(int i=0;i<size1;i++){//addition
            marked[markedSize++]=toBeAddedToMarked.front();//addition
            toBeAddedToMarked.pop();//addition
            }//addition
        if(PatternsChanged)
            pathLength++;//Double Check
        if(done)
            break;//If we reached the target

    }
    delete[] marked;
    marked=NULL;

    delete[] branched;
    branched=NULL;
}
bool Graph::has(int* arr, int id, int size)
{
    for(int i=0;i<size;i++)
        if(arr[i]==id)
            return true;
    return false;
}
void Graph::findComponents(int** L,int& componentNum,int* arr)
{
    int  traversed[numberOfVertices];
    for(int i=0;i<numberOfVertices;i++)
        traversed[i]=0;
    //0 means not traversed for the particular indexed id
    int componentIndex=0;
    componentNum=0;
    for(int i=0;i<numberOfVertices;i++)
    {
        if(traversed[i]==1)
            continue;
        componentNum++;
        //Do a breadth first traversal for every node you push to queue increment a counter which is the size of the current component
        int componentSize=0;
        queue<int> q;
        q.push(vertices[i]->getRoot()->id);
        queue<int>* p=&q;
        int* marked=new int[numberOfVertices];
        marked[0]=vertices[i]->getRoot()->id;
        int markedSize=1;
        int index;
        int indexInComponent=0;
        L[componentIndex]= new int[numberOfVertices];
        while(!q.empty())
        {
            int size= q.size();
            componentSize+=size;
            //Mark the corresponding indexes as one in the traversed array
            for(int i=0;i<size;i++){
                index = GetIndex(q.front());//this index corresponding to this one must be marked as one in traversed array
                L[componentIndex][indexInComponent++]=q.front();
                traversed[index]=1;
                //we should get the index correspondence of id because index is the id.
                vertices[index]->ListCount(p,marked,markedSize);//queues every adjacent node to current node
                q.pop();
            }
        }
        arr[componentIndex]=componentSize;//Component size of the ith component
        componentIndex++;

        delete[] marked;
        marked=NULL;
    }
}

void Graph::AverageClusteringCoefficients()
{
    /*TO DO
        use the same algorithm to find the components.
        Call the avarageClustering function separately for every vertex in a component. In the end take the mean of the values and print it.
        Repeat same process for every component.
    */

     int** components;
     components = new int*[numberOfVertices];//max size is eq to vertice number
     int numberOfComponents=0;
     int* sizes= new int[numberOfVertices];
     findComponents(components,numberOfComponents,sizes);
     double totAvClus=0;//Since av clustering cannot be a negative number assuming it is negative initially wont cause any problems
     for(int i=0;i<numberOfComponents;i++)
     {
         totAvClus=0;
         //int* currentComponent= components[i];
         double k=sizes[i];
         for(int j=0;j<sizes[i];j++)
         {
             double value=averageClustering(components[i][j]);
             totAvClus+=value;
         }
         cout<<"For component "<<i<<" the avarageClustering is: "<<(totAvClus/k)<<endl;
     }




     //Deleting the arrays
     for(int i=0;i<numberOfComponents;i++){
            delete[] components[i];
            components[i]=NULL;
     }
     delete[] components;
     components=NULL;

     delete[] sizes;
     sizes=NULL;
}
double Graph::averageClustering(int id)
{
    /*TO DO
    for the given component put all adjacent nodes of the given node in an array.
    Then for all nodes iterate their adjacent nodes and check if it is in the array.If it is increase the counter of edges.
    The size of the array is number of adjacent nodes. Knowing these just use the formula
    */
    int numberOfNeighbors=0;
    double edgesBetweenNeighbors=0;

    //Calculate number of neighbors
    int index=GetIndex(id);
    int* arr1 = new int[numberOfVertices];
    vertices[index]->fillArray(arr1,numberOfNeighbors);//Fill array fills the arr1 with adjacent node's ids and numberOfNeighbors is set to number of elements inserted
    if(numberOfNeighbors<=1)
        return 0;

    //Calculate edgesBetweenNeighbors
    for(int i=0;i<numberOfNeighbors;i++)
    {
        int ind= GetIndex(arr1[i]);
        int*arr2 = new int[numberOfVertices];
        int neighborCount=0;
        vertices[ind]->fillArray(arr2,neighborCount);
        for(int j=0;j<neighborCount;j++)
        {
            if(arr2[j]==id)
                continue;
            if(vertices[index]->has(arr2[j]))
                edgesBetweenNeighbors++;
        }

        delete[] arr2;
        arr2=NULL;//Think of changing it to a stack array
    }


    edgesBetweenNeighbors=edgesBetweenNeighbors/2;//every edge is counted twice
    delete[] arr1;
    arr1=NULL;
    return ((2*edgesBetweenNeighbors)/(numberOfNeighbors*(numberOfNeighbors-1)));
}


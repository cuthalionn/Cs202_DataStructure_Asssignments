#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include"AVL.h"
int main()
{
  AVL avl;
  string line;
  int count=0;
  ifstream myfile ("Dothraki.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      avl.insert(line);
      count++;
    }
    myfile.close();
  }
  //File is all read and all the words have been saved to the avl tree.
  string word;
  cout<<"Welcome to Dothraki Vocabulary!"<<endl;
  cout<<"This vocabulary contains "<<count<<" words.";
  do
  {
      cout<<"\nEnter a word: ";
      cin>>word;
      if(avl.search(word))
            cout<<"Found! The word is in vocabulary."<<endl;
      else
      {
          cout<<"Not found!"<<endl;
          cout<<"Some suggestions:";
          string suggestions="";
          double prefixSize=word.length();
          string prefix;
          while(suggestions=="" && prefixSize>=((word.length()/2.0)) )
          {
              prefix= word.substr(0,prefixSize);
              avl.findSimilar(prefix,suggestions);
              prefixSize--;
          }
          cout<<suggestions;
          if(suggestions=="")
            cout<<"There is no word starting with prefix " << prefix <<" in vocabulary!"<<endl;

      }

  }while(word!="quit");

    return 0;
}

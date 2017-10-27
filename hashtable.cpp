/*******************************************************************************
  Title          : hashtable.h
  Author         : Patrycja Krawczuk
  Created on     : May 5th, 2017
  Description    : Interface to the Disjointset class
  Purpose        : To provide methods for processing disjoint sets
  Usage          : 
  Build with     : 
  Modifications  : 

 
*******************************************************************************/


#include <iostream>
#include <string>
#include <list>

#include "hashtable.h"


using namespace std;



HashTable::HashTable()
{
    myHashTable = new HashEntry*[table_size];
    for (int i = 0; i < table_size; i++)
                  myHashTable[i] = NULL;
}


HashTable::~HashTable()
{   
  for (int i=0; i<table_size; i++)
  {
    delete myHashTable[i];
  }             
}


bool HashTable::find(string& phone_number,int& set_index)
{

  string phone_no_hypen=remove_hypens(phone_number);
  long long encoded_tel=encode(5, phone_no_hypen);
  int currentPos=findPos(encoded_tel, phone_number);
  
  if (myHashTable[currentPos] !=NULL)
  {
    set_index=myHashTable[currentPos]->index_in_set;
    return true;
  }
  else
  {
    set_index=-1;
    return false;
  }
}



void HashTable::insert(HashEntry*& new_entry) //SetNode*& set_link)
{
   
   //cout<<"New entry phone "<<new_entry->telephone<<endl;
   string phone_no_hypen=remove_hypens(new_entry->telephone);
   long long encoded_tel= encode(5, phone_no_hypen);
   //cout<<"The phone number is encoded as  "<< encoded_tel<<endl;
   int currentPos=findPos(encoded_tel, new_entry->telephone);
   if (myHashTable[currentPos] !=NULL)
   {
    return; //already in the table
   }
   myHashTable[currentPos]=new_entry;
   new_entry->index_in_set=counter;

   if (counter > (table_size/2 -1))
       rehash();

   counter++;
   
}

void HashTable::display_the_table()
{
  for (int i=0; i<table_size; i++)
  {
    //cout<<i<<" ";
    if(myHashTable[i]==NULL)
      cout<<"EMPTY"<<endl;
    else
      cout<<(myHashTable[i])->telephone<<endl;
  }

}


//return the hash table location where the key is located, or the first empty cell found
int HashTable::findPos(long long value, string new_phone)
{
  int collisionNum=0;
  int currentPos=hashing_function(value);
 // cout<<"Hashing Function gave me position "<<currentPos<<endl;
  while((myHashTable[currentPos] !=NULL) && (myHashTable[currentPos]->telephone != new_phone))
  {
    currentPos += 2* ++collisionNum -1; //probe
    //cout<<"Checking the index "<<currentPos<<endl;
    if(currentPos >=table_size)
      currentPos -=table_size;
  }

  return currentPos;
}


int HashTable::hashing_function(long long encoded_val)
{
  int key= encoded_val%table_size;

  return key;
}


long long HashTable::encode(int RADIX, const string & s)
{
  long long hashval=0;
  for (int i=0; i<s.length(); i++)
    {
      hashval=s[i]+ RADIX*hashval;
    }
  
  return hashval;
}

  

void HashTable::rehash()
{


  if(curPrimeIndx>=6)
  {
    cerr<<"The program is not able to rehash."<<endl;
    //break;
  }
  int old_size=table_size;
  
  //new size of the hash table from array of primes
  table_size=array_primes[curPrimeIndx];
  curPrimeIndx++;

  HashEntry** ReHashedTable= new HashEntry*[table_size];
    for (int i = 0; i < table_size; i++)
                  ReHashedTable[i] = NULL;


    for (int i = 0; i < old_size; ++i)
    {
        HashEntry *tmp = myHashTable[i];
        if(tmp != NULL)
        {
            
            string phone_no_hypen=remove_hypens(tmp->telephone);
            long long encoded_tel= encode(5, phone_no_hypen);
            int collisionNum=0;
            int currentPos=hashing_function(encoded_tel);

            while((ReHashedTable[currentPos] !=NULL) && (ReHashedTable[currentPos]->telephone != tmp->telephone))
            {
                currentPos += 2* ++collisionNum -1; //probe
                //cout<<"Checking the index "<<currentPos<<endl;
                if(currentPos >=table_size)
                  currentPos -=table_size;
            }
            if (ReHashedTable[currentPos] !=NULL)
              ;
            else
              ReHashedTable[currentPos]=tmp;

        }
    }

      delete [] myHashTable;
    myHashTable = ReHashedTable;
    ReHashedTable=NULL;

}


string HashTable::remove_hypens(string tel_num)
{
  tel_num.erase(tel_num.begin()+3);
  tel_num.erase(tel_num.begin()+6);
  return tel_num; 
}
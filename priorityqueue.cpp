/*******************************************************************************
  Title          : priorityqueue.cpp
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
#include <iomanip>
#include <vector>
using namespace std;

#include "priorityqueue.h"


PriorityQueue::PriorityQueue()
{
  
}

PriorityQueue::~PriorityQueue()
{

}

bool PriorityQueue::isEmpty()
{
	if(PQueue.size()==0)
		return true;
	else
		return false;
}

void PriorityQueue::insert(SetNode* root_node)
{
   PQueue.push_back(root_node);

}

void PriorityQueue::display_the_queue(ostream& output)
{
	for( int i=0; i<PQueue.size(); i++)
  {
    output<<(*PQueue.at(i)).get_parent()<<endl;
  }
}

void PriorityQueue::return_roots(vector<SetNode*>& v)
{
  update_the_queue();
  for (vector<SetNode*>::iterator it= PQueue.begin(); it!=PQueue.end();) 
  {
      v.push_back(*it);
      it++;     
  }
}


void PriorityQueue::update_the_queue()
{
  //The first problem with the queue is that it might have roots that are not longer roots
  for (vector<SetNode*>::iterator it= PQueue.begin(); it!=PQueue.end();) 
  {
      if( (*it)->get_parent() > 0) 
       it = PQueue.erase(it);
      else 
      ++it;
  }

}


void PriorityQueue::destroy()
{
  PQueue.clear(); 
}

void PriorityQueue::show_max_size(ostream& output)
{
  //cout<<"I am in show max size in PQ"<<endl;
  if(isEmpty())
  {
    output<<"There aren't any valid cohorts in the program"<<endl;
  }
  else
  {
      update_the_queue();
      heapify_size();
   
      int max=(*PQueue.at(0)).get_parent();
      int i=0;
      int missed=0;
      bool more_max=true;
      (*PQueue.at(i)).display_node(output);
      while( (more_max) && ( i<PQueue.size() ) )
      {
        i=2*i+1;
        if (  ( i<PQueue.size()) &&  (*PQueue.at(i)).get_parent()==max )
        (*PQueue.at(i)).display_node(output);
        else
          missed++;
        
        i++;

        if ( ( i<PQueue.size())  && (*PQueue.at(i)).get_parent()==max   )
        (*PQueue.at(i)).display_node(output);
        else
          missed++;

        i--;

        if (missed>=2)
          more_max=false;

      }
  }
    
}

void PriorityQueue::show_max_activity(ostream& output)
{
  if(isEmpty())
  {
    output<<"There aren't any valid cohorts in the program"<<endl;
  }
  else
  {
      update_the_queue();
      heapify_activity();
  
      
      int max=(*PQueue.at(0)).get_set_activity();
      int i=0;
      int missed=0;
      bool more_max=true;
      (*PQueue.at(i)).display_node(output);
      while( (more_max) && ( i<PQueue.size() ) )
      {
        i=2*i+1;
        if (  ( i<PQueue.size()) &&  (*PQueue.at(i)).get_set_activity()==max )
        (*PQueue.at(i)).display_node(output);
        else
          missed++;
        
        i++;

        if ( ( i<PQueue.size())  && (*PQueue.at(i)).get_set_activity()==max   )
        (*PQueue.at(i)).display_node(output);
        else
          missed++;

        i--;

        if (missed>=2)
          more_max=false;

       }
  }
    
}


void PriorityQueue::heapify_size()
{
  for (int i=(PQueue.size()/2)-1; i>=0; i--)
       percolateDown_size(i);

}

void PriorityQueue::percolateDown_size(int hole)
{
   int child;
   SetNode* tmp= PQueue[hole];

   for (; (hole*2+1) <= PQueue.size()-1; hole=child)
   {
    child = (2*hole+1);//right child

    if(  (child != PQueue.size()-1) && ((*PQueue.at(child+1)).get_parent() < (*PQueue.at(child)).get_parent()) )
        child++;
    if( (*PQueue.at(child)).get_parent() < (*tmp).get_parent())
         PQueue.at(hole)=PQueue.at(child);
    else
        break;   
   }
   PQueue.at(hole)=tmp;

}

void PriorityQueue::heapify_activity()
{
  for (int i=(PQueue.size()/2)-1; i>=0; i--)
       percolateDown_activity(i);

}


void PriorityQueue::percolateDown_activity(int hole)
{
  int child;
   SetNode* tmp= PQueue[hole];

   for (; (hole*2+1) <= PQueue.size()-1; hole=child)
   {
    child = (2*hole+1);//right child

    if(  (child != PQueue.size()-1) && ((*PQueue.at(child+1)).get_set_activity() > (*PQueue.at(child)).get_set_activity()) )
        child++;
    if( (*PQueue.at(child)).get_set_activity() > (*tmp).get_set_activity())
         PQueue.at(hole)=PQueue.at(child);
    else
        break;   
   }
   PQueue.at(hole)=tmp;

}
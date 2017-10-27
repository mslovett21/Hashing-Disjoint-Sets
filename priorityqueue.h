/*******************************************************************************
  Title          : priorityqueue.h
  Author         : Patrycja Krawczuk
  Created on     : May 5th, 2017
  Description    : Interface to the PriorityQueue class
  Purpose        : To provide methods for processing a PriorityQueue
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

 
*******************************************************************************/


#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <iostream>
#include <string>
#include <list>

#include "setnode.h"

using namespace std;



class PriorityQueue
{
public:

/** PriorityQueue() - default constructor for the class*/
PriorityQueue();

/** ~PriorityQueue() - default destructor for the class*/
~PriorityQueue();

/** insert() - insertion method, 
* This method adds another SetNode* into private member variable PQueue
* @param      SetNode*   [in]  root_node 
* @post       a pointer root_node is added to the  private PQueue vector
*/
void insert(SetNode* root_node);

/** destroy() - user defined destructor for the class*/
void destroy();

/** show_max_size() 
* This method displays the cohort_ID, activity, size and volume of the cohort having maximum size.
* If two or more have the same maximum size, then all that are maximal are displayed
* @param   ostream&    [inout]  output
* @pre    working open stream is provided
* @post  max-size cohorts are printed to the screen one per line
*/
void show_max_size(ostream& output);

/** show_max_activity() 
* This method displays the cohort_ID, activity, size and volume of the cohort having maximum activity.
* If two or more have the same maximum activity, then all that are maximal are displayed
* @param   ostream&    [inout]  output
* @pre    working open stream is provided
* @post  max-activity cohorts are printed to the screen one per line
*/
void show_max_activity(ostream& output);


/** return_roots() -method returns vector of current roots of sets
* It is used to provide Disjoint set with roots of sets (in case cohort_id is not corresponding to index in DisjointSet)
* This function can be ommited if cohort-ids are indecies of parents
* @param   vector<SetNode*>&     [inout]  v
*/
void return_roots(vector<SetNode*>& v);


private:


/** display_the_queue(ostream& output)
* Prints current state of the PQueue (value 'parent' variable of SetNode), used for debbugging
* Format: parent (one per line)
* @param   ostream&    [inout]  output
* @pre    working open stream is provided
* @post   value of 'parent' SetNode objects are printed to the screen
*/
void display_the_queue(ostream& output);
/** isEmpty() - , 
* This method return value of private variable parent for the calling object 
* @return       int value of parent
*/
bool isEmpty();


/** update_the_queue() 
* This method updates the PQueue vector ( makes sure priority order is maintain with valid data inside the vector)
* @pre  none
* @post PQueue is a valid priority queue (of type max-size or max-activity)
*/
void update_the_queue();

/** heapify_size()  moves the key up until the heap has the heap property (size==priority)
*  @pre  none
*  @post Every item in the heap has the property that its priority is
*        greater than that of each of its children in the heap.
*/
void heapify_size();

/** heapify_activity()  moves the key up until the heap has the heap property  (activity==priority)
*  @pre  none
*  @post Every item in the heap has the property that its priority is
*        greater than that of each of its children in the heap.
*/
void heapify_activity();

/** percolateDown_size -helper function of heapify_size()
* moves the hole down until the heap has the heap property 
* @param   int   [in]  hole - current index to heapify
*/
void percolateDown_size(int hole);

/** percolateDown_activity -helper function of heapify_activity()
* moves the hole down until the heap has the heap property 
* @param   int   [in]  hole - current index to heapify
*/
void percolateDown_activity(int hole);



vector<SetNode*> PQueue;//priority queue vector

};



#endif /* __PRIORITY_QUEUE_H__ */
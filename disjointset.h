/*******************************************************************************
  Title          : disjointset.h
  Author         : Patrycja Krawczuk
  Created on     : May 5th, 2017
  Description    : Interface to the Disjointset class
  Purpose        : To provide methods for processing disjoint sets
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

 
*******************************************************************************/


#ifndef __DISJOINTSET_H__
#define __DISJOINTSET_H__

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <unordered_set>


#include "priorityqueue.h"


using namespace std;



class DisjointSet
{
public:

/** DisjointSet() - default constructor for the class*/
DisjointSet();

/** ~DisjointSet() - default destructor for the class*/
~DisjointSet();

/** insert_new_data() - this methods adds pointer to the SetNode the private member variable Sets
* @param      SetNode*&   [inout]  new_set
* @post       new element is added to Sets
*/
void add(SetNode* & new_set);

/** union_of_sets() - this methods updates the relationship betwen two elements of the Sets vector,
* the elements become part of the same set (new parent is the set with bigger cardinality)- of they are not in the same set already
* @param      int     [in]  index_1
* @param      int     [in]  index_2
* @param      double  [in]  money_transfered
* @post       the relationship between data (phone numbers) are updated
*/
void union_of_sets(int& index1, int& index2, double money_transferred);

/** max_size() - this methods displays the cohort_id, activity, size, and volume of the cohort having maximum size.
* If two or more cohorts have the same size, then all that are maximal are displayed. If there is no cohorts in the program.
* The message: 'There aren't any valid cohorts in the program'- will be displayed
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       max size cohorts or the special message is/are displayed to the screen
*/
void max_size(ostream& output);

/** find_cohort() - this methods display the ID of cohort to which the phone-number belongs
* in the form tel_phone: cohort_id, if there is no such number, it displays: tel_phone: 0
* @param      string   [in]     tel_phone1
* @param      ostream& [inout]  output
* @pre  the stream is open and ready to write
* @post       the result of the find command are printed to the screen
*/
void find_cohort(int index_set, int& tel_ID);


/** display_ids() - this methods displays the cohort_ids in order of increasing id
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       the cohorts are diplayed on the screen
*/
void display_ids(ostream& output);

/** set_members() - this methods displays a list of all telephone numbers in the given cohort,
* one per line. If there is no cohort with given id, it should display a single blank line
* @param      int       [in]     cohort_id
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       the members of cohort are orinted to the screen
*/
void set_members(int cohort_id,ostream& output);

/** find_info() - this methods displays the cohort_id, activity, size, and volume of the cohort with provided id
* If cohort with given id does noe exists it displays an error message
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       info about specific cohort is printed to the screen
*/
void find_info(int cohort_id, ostream& output);

/** max_activity() - this methods displays the cohort_id, activity, size, and volume of the cohort having maximum activity.
* If two or more cohorts have the same activity, then all that are maximal are displayed. If there is no cohorts in the program.
* The message: 'There aren't any valid cohorts in the program'- will be displayed
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       max activity cohorts or the special message is/are displayed to the screen
*/
void max_activity(ostream& output);

private:
/** percolateDown_IDs -heap sort, helper function of heapify_IDs()
* moves the hole down until the heap has the heap property 
* @param   int   [in]  hole - current index to heapify
* @param   int   [in]  last- current last for heap sort
*/
void percolateDownIDs(int hole, int last);

/** heapify_IDs() heap sort, moves the key up until the heap has the heap property (higher id == higher priority )
*  @pre  none
*  @post Every item in the heap has the property that its priority is
*        greater than that of each of its children in the heap.
*/
void heapify_IDs();

/** find() find function of Disjoint Set data structure, with pathcompression
*  @pre  element is positive integer
*  @post path compression
*  @return index of the parent of the element 
*/
int find(int& element);


/** display (ostream& output)
* Prints current state of the Sets (value 'parent' variable of SetNode), used for debbugging
* @param   ostream&    [inout]  output
* @pre    working open stream is provided
*/
void display(ostream& output);

unordered_set<int> setOfRoots;// stores pointers to unique parent nodes

pair<unordered_set<int>::iterator, bool > result;//helper for unorder_set setOfRoots

vector<SetNode*> Sets;//vector where disjoint sets are stored and their relationships encoded

int set_ID=1;// ID numbers start from 100 

PriorityQueue MaxSize;// max priority== max size

PriorityQueue MaxActivity;//max priority== max activity

vector<SetNode*> roots_sets;//stores roots of current parents
 
};



#endif /* __DISJOINTSET_H__ */
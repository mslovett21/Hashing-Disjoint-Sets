/*******************************************************************************
  Title          : setnode.h
  Author         : Patrycja Krawczuk
  Created on     : May 5th, 2017
  Description    : Interface to the SetNode Class
  Purpose        : To provide methods for processing SetNodes
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

 
*******************************************************************************/

#ifndef __SETNODE_H__
#define __SETNODE_H__

#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "hashentry.h"



using namespace std;


class SetNode
{
  public:

  /** SetNode() - default constructor for the class*/
	SetNode();

  /** SetNode() - contructor with parameter, 
  * This method creates a new object of class SetNode with private member variable hash_table_link set to value of pointer_hash
  * @param      HashEntry*&   [inout]  pointer_hash 
  * @post       new object of the class with hash_table_link=pointer_hash is created
  */
	SetNode(HashEntry* & pointer_hash);

  /** ~SetNode() - default destructor for the class*/
  ~SetNode();


   /** get_parent() - a getter function, 
  * This method return value of private variable parent for the calling object 
  * @return       int value of parent
  */
  int get_parent();

   /** get_set_activity() - getter function
  * This method updates value of private variable activity and returns it
  * @return       double current value of private variable activity
  */
  double get_set_activity();
  
  /** get_ID() getter function
  * This method returns the value of private variable cohort_ID
  * @return       double current value of private variable activity
  */
  int get_ID();

  /** display_node(ostream& output)
  * Prints the SetNode object to the screen in the specified format.
  * Format:  cohort_ID, activity, -parent (size), money_cohort displayed on single line,
  * separated by tab characters
  * @param   ostream&    [inout]  output
  * @pre    working open stream is provided
  * @post   SetNode objects are printed to the screen
  */
  void display_node(ostream& output);


  /** get_phone_number() getter function
  * This method returns the phoone_number associated with the calling object
  * @return       string phone number
  */
  string get_phone_number();


	private:

  
	HashEntry* hash_table_link=NULL;// link to the HashEntry which contains associated with the node phone_number
	int cohort_ID=0; //cohort_ID of the set to which the node belongs
	int parent=-1; //if positive index of the parent node in DisjointSet class, if negative number of children (the node is a parent)
	int money_cohort=0;// aka volume amount of money transfered within cohort
	int index_in_set=0; //index where the node is in the DishointSet class vector
  double activity=0; // money_cohort (volume) divided by the total number of unordered pairs of distinct numbers in the cohort
	vector<SetNode*> kids; //list of pointers to kids if the node is a parent, EMPTY if the node is not a parent

	friend class DisjointSet;
  
};



#endif /* __SETNODE_H__ */
/*******************************************************************************
  Title          : command_manager.h
  Author         : Patrycja Krawczuk
  Created on     : May 5th, 2017
  Description    : Interface to the Disjointset class
  Purpose        : To provide methods for processing disjoint sets
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

 
*******************************************************************************/


#ifndef __COMMAND_MANAGER_H__
#define __COMMAND_MANAGER_H__

#include <iostream>
#include <string>
#include <list>


#include "hashtable.h"
#include "hashentry.h"
#include "disjointset.h"
#include "setnode.h"


using namespace std;




class Command_Manager
{
public:
/** Command_Manager() - default constructor for the class*/
Command_Manager();

/** ~Command_Manager() - default destructor for the class*/
~Command_Manager();

/** insert_new_data() - this methods checks if the given telephone numbers: tel_phone1, tel_phone2 are already
* in the program, if there are both not found: they are added to the data of the program and their relationship is updated,
* (both are new elements of the same set in Disjoint set class), if one of them in found and another not: the new tel_phone is added to
* the data of the program, the relationship is updates (new number is joined to the set of the tel number already in the set)
* if both numbers are already found in the program: their relationship is updated (they are members of the same set, money (volume) is updated )
* As for this version of the program cohort_ids given to elements are starting with id 1 and have no connection to index in disjoinset class
* @param      string   [in]  tel_phone1
* @param      string   [in]  tel_phone2
* @param      string   [in]  money 
* @post       the relationship between data (phone numbers) are updated
*/
bool insert_new_data(string tel_phone1, string tel_phone2, string money);

/** find_cohort() - this methods display the ID of cohort to which the phone-number belongs
* in the form tel_phone: cohort_id, if there is no such number, it displays: tel_phone: 0
* @param      string   [in]     tel_phone1
* @param      ostream& [inout]  output
* @pre  the stream is open and ready to write
* @post       the result of the find command are printed to the screen
*/
void find_cohort(string tel_phone, ostream& output);

/** display_members() - this methods displays a list of all telephone numbers in the given cohort,
* one per line. If there is no cohort with given id, it should display a single blank line
* @param      int   [in]     cohort_id
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       the members of cohort are orinted to the screen
*/
void display_members(int cohort_id, ostream& output);

/** display_max_size_cohort() - this methods displays the cohort_id, activity, size, and volume of the cohort having maximum size.
* If two or more cohorts have the same size, then all that are maximal are displayed. If there is no cohorts in the program.
* The message: 'There aren't any valid cohorts in the program'- will be displayed
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       max size cohorts or the special message is/are displayed to the screen
*/
void display_max_size_cohort(ostream& output);

/** display_max_activity_cohort() - this methods displays the cohort_id, activity, size, and volume of the cohort having maximum activity.
* If two or more cohorts have the same activity, then all that are maximal are displayed. If there is no cohorts in the program.
* The message: 'There aren't any valid cohorts in the program'- will be displayed
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       max activity cohorts or the special message is/are displayed to the screen
*/
void display_max_activity_cohort(ostream& output);

/** display_cohort_ids() - this methods displays the cohort_ids in order of increasing id
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       the cohorts are diplayed on the screen
*/
void display_cohort_ids(ostream& output);

/** display_info() - this methods displays the cohort_id, activity, size, and volume of the cohort with provided id
* If cohort with given id does noe exists it displays an error message
* @param      ostream& [inout]  output
* @pre        the stream is open and ready to write
* @post       info about specific cohort is printed to the screen
*/
void display_info(int cohort_id, ostream& output);



private:

bool flag=true;//flag to avoid rebuilding the PQ

HashTable Hash_map;// Hash Table for O(1) access to phone numbers in the program

DisjointSet Set_relations;// to keep track on relationships between phone numbers

int num_of_sets_created=0;//keeps track on how many unique phone numbers were provided to the program

};



#endif /* __COMMAND_MANAGER_H__ */
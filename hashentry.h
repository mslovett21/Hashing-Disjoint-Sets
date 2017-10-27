/*******************************************************************************
  Title          : hashentry.h
  Author         : Patrycja Krawczuk
  Created on     : May 5th, 2017
  Description    : Interface to the HashEntry class
  Purpose        : To provide methods for processing HashEntries
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

 
*******************************************************************************/

#ifndef __HASHENTRY_H__
#define __HASHENTRY_H__

#include <iostream>
#include <string>
#include <list>





using namespace std;



class HashEntry
{
   public:

  /** HashEntry() - default constructor for the class*/
	HashEntry();

	/** HashEntry() - contructor with parameter, 
  * This method creates a new object of class HashEntry with private member variable telephone set to value of tel_num
  * @param      string    [in]  tel_num 
  * @post       new object of the class with telephone=tel_num is created
  */
	HashEntry(string tel_num);

	/** ~HashEntry() - default destructor for the class*/
	~HashEntry();


  /** get_telephone() getter function
  * This method returns the phoone_number associated with the calling object
  * @return       string phone number
  */
	string get_telephone();
	

   

	private:

	string telephone;//valid phone number of form XXX-XXX-XXXX

	int index_in_set; //index where the associated SetNode will be stored in the DisjointSet Class

	friend class HashTable;

  
};



#endif /* __HASHENTRY_H__ */
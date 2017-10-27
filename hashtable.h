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


#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <iostream>
#include <string>
#include <list>



#include "hashentry.h"

class HashEntry;

using namespace std;


class HashTable
{
public:
/** HashTable() -default constructor for the class*/
HashTable();

/** ~HashTable() - default constructor for the class*/
~HashTable();

/** find() - search method, 
* This method searches the hash table for the provided phone_number
* if the phone number is found in the table it sets set_index to the index where this
* phone number's set node is stored in DisjointSet class, returns true
* if the phone number is not foud it sets set_index to -1 and returns false
* @param   string      [inout]  phone_number
* @param   int         [inout]  set_index 
* @post  NONE
  @returns true if phone found, false if phone not found
*/
bool find(string& phone_number, int& set_index);


/** insert() - insertion method, 
* This method inserts new HashEntry* into the HashTable, the method used: quadratic probing
* phone_number is first encode using radix 10 and then mapped to an index in the HT
* @param   HashEntry*&     [inout]  new_entry
* @pre  the phone_number associated with this HashEntry is not already in the TB
* @post HashEntry is added to the HT
*/
void insert(HashEntry* & new_entry);


private:

/*remove_hypens(string tel_num);
* This method removed hypend from specific positions in the string
*tel_num is a sting of the form XXX-XXX-XXXX where X is 0-9
* @param   string     [in]  tel_num
* @pre  tel_num is a sting of the form XXX-XXX-XXXX where X is 0-9
* @post return string without hypens XXXXXXXXXX
*/
string remove_hypens(string tel_num);

/** hashing fucntion() - quadratic hasing method, 
* @param   long long    [in]  phone_number
* @pre  phone_number was encoded into a long long type int
* @post unique position is found for the unique phone number
*/
int hashing_function(long long phone_number);

/** findPos() - helper method for hasing function, 
* This method check if calculated by hashing function position is avaible
* if not, it uses quadratic probing (adds squares) to find next avaiable postion
* @post index of position to which phone_number is hashed
*/
int findPos(long long value,string new_phone);

/* rehash()
This method is called when the load factor is high, the table is half full
In order to guarantee that quadratic probling will find positions for incoming phone numbers
the size of the table has to increase (next prime int array of primes)
*/
void rehash();

/** encode() - encoding strings method
* This method encoded string into long long int
* @param   int [in] RADIX  //number of characters in the alphabeth
* @param   const string& s //string to encode 
* @returns long long int (encoded sting s)
*/
long long encode(int RADIX, const string & s);


/** display_the_table()
* Prints current state of the HT (phone numbers mapped), used for debbugging only
*/
void display_the_table();

HashEntry** myHashTable;// the array of pointer to HashEntries

int table_size= 23;//size at start

int load_factor;//helps to determine when to rehash

int counter=0;//keeps track on how many elements in the array

int curPrimeIndx=0;// keeps track on which prime in array_primes to use

int array_primes[7]={373, 1023, 2137, 4093, 8311, 16319, 32999};

};



#endif /* __HASHFUNCTION_H__ */
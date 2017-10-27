/*******************************************************************************
  Title          : hashentry.h
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
  
#include "hashentry.h"
using namespace std;



HashEntry::HashEntry()
{

}

string HashEntry::get_telephone()
{
  return telephone;
}

HashEntry::HashEntry(string tel_num)
{
	telephone=tel_num;


}
HashEntry::~HashEntry()
{
}
    

	


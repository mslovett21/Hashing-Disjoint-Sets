/*******************************************************************************
  Title          : setnode.h
  Author         : Patrycja Krawczuk
  Created on     : May 8th, 2017
  Description    : Interface to the Disjointset class
  Purpose        : To provide methods for processing disjoint sets
  Usage          : 
  Build with     : 
  Modifications  : 

 
*******************************************************************************/


#include <iostream>
#include <string>
#include <list>
#include <iomanip>
  
#include "setnode.h"
using namespace std;



SetNode::SetNode()
{

}

SetNode::SetNode(HashEntry* & pointer_hash)
{
  hash_table_link=pointer_hash;
}

int SetNode::get_parent()
{
  return parent;
}

int SetNode::get_ID()
{
  return cohort_ID;
}

SetNode::~SetNode()
{ 
	
}

void SetNode::display_node(ostream& output)
{
  double size=-parent;
  double pairs= size*(size-1)/2; 

  activity=static_cast<double>(money_cohort/pairs);
 

  output<<cohort_ID<<"\t"<<fixed<<setprecision(2)<<activity<<"\t"<<-parent<<"\t"<<money_cohort<<endl;//index_in_set<<endl;
}


double SetNode::get_set_activity()
{
  if(parent<0)
  {
  double size=-parent;
  double pairs=(size*(size-1)/2); 
  activity=static_cast<double>(money_cohort/pairs);
  return activity;
  }
  else
    activity=0;
    return activity;
}


 

string SetNode::get_phone_number()
{
  return hash_table_link->get_telephone();
}
  

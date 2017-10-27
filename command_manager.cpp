/*******************************************************************************
  Title          : disjointset.h
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
#include <string>
using namespace std;


#include "command_manager.h"




Command_Manager::Command_Manager()
{
  
    
}

Command_Manager::~Command_Manager()
{

}

bool Command_Manager::insert_new_data(string tel_phone1, string tel_phone2, string money)
{
    //This part has 3 options:
    //OPTION 1: Both numbers are NEW, (not found in hash table)
    bool tel_found1, tel_found2;
    int index_set2;
    int index_set1;
    double money_transfered=stod(money);

    tel_found1=Hash_map.find(tel_phone1, index_set1);
    tel_found2=Hash_map.find(tel_phone2, index_set2);
 

    //OPTION 1 : Both already in
    if(tel_found1 && tel_found2)
    {
      //both numbers are already in HT and Set. We just need an update
    }
    //OPTION 2: Both numbers are NEW, (not found in hash table)
    else if((!tel_found1) && (!tel_found2))
    {
      //cout<<tel_phone1<<" and "<<tel_phone2<<" are NOT in"<<endl;
      
      //Taking care of first number
      HashEntry* new_entry1=new HashEntry(tel_phone1);
      Hash_map.insert(new_entry1);
      int money_transfered=stod(money);
      SetNode* new_set1= new SetNode(new_entry1); 

      //Taking care of second number
      HashEntry* new_entry2=new HashEntry(tel_phone2);
      Hash_map.insert(new_entry2);
      SetNode* new_set2= new SetNode(new_entry2);

      Set_relations.add(new_set1);
      index_set1=num_of_sets_created;
      num_of_sets_created++;

      Set_relations.add(new_set2);
      index_set2=num_of_sets_created;
      num_of_sets_created++;
    }
    //OPTION 3 one new
    else if(tel_found1 || tel_found2)
    {
      if(tel_found1)
      {
          //Taking care of second number
          HashEntry* new_entry2=new HashEntry(tel_phone2);
          Hash_map.insert(new_entry2);
          SetNode* new_set2= new SetNode(new_entry2);
          Set_relations.add(new_set2);
          index_set2=num_of_sets_created;
          num_of_sets_created++;
      }
      else
      {
          //Taking care of first number
          HashEntry* new_entry1=new HashEntry(tel_phone1);
          Hash_map.insert(new_entry1);
          SetNode* new_set1= new SetNode(new_entry1);
          Set_relations.add(new_set1);
          index_set1=num_of_sets_created;
          num_of_sets_created++;
      }
    }
    
    int root_index;

    Set_relations.union_of_sets(index_set1,index_set2, money_transfered);

   

	return true;

}

void Command_Manager::find_cohort(string tel_phone, ostream& output)
{
    bool tel_found;
    int index_set;

    tel_found=Hash_map.find(tel_phone, index_set);
    if (tel_found)
    {
      int id_tel;
      Set_relations.find_cohort(index_set, id_tel);
      output<<tel_phone<<": "<<id_tel<<endl;
    }
    else
      output<<tel_phone<<": 0"<<endl;
   
}

void Command_Manager::display_members(int cohort_id, ostream& output)
{
    Set_relations.set_members(cohort_id, output);
}

void Command_Manager::display_max_size_cohort(ostream& output)
{
  Set_relations.max_size(output);
}

void Command_Manager::display_max_activity_cohort(ostream& output)
{
   Set_relations.max_activity(output);
}

void Command_Manager::display_cohort_ids(ostream& output)
{
  Set_relations.display_ids(output);
}

void Command_Manager::display_info(int cohort_id, ostream& output)
{
  Set_relations.find_info(cohort_id, output);
   
}

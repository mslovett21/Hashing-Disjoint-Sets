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
#include <vector>

using namespace std;

#include "disjointset.h"


DisjointSet::DisjointSet()
{


}

DisjointSet::~DisjointSet()
{
	//Avoid dangling pointers in the queue
	MaxSize.destroy();
	MaxActivity.destroy();
	for (int i=0; i<Sets.size(); i++)
	{
		delete Sets.at(i);
	}
}

void DisjointSet::add(SetNode*& new_set )
{
	
	Sets.push_back(new_set);
	new_set->parent=-1;
	new_set->cohort_ID=set_ID;
	new_set->index_in_set=Sets.size()-1;
	set_ID++;
	int i=Sets.size()-1;

	//cout<<Sets.at(i)->parent<<" "<<Sets.at(i)->cohort_ID<<" "<<Sets.at(i)->money_cohort<<endl;


}

void DisjointSet::find_cohort(int index_set, int& tel_ID)
{
   tel_ID=Sets.at(index_set)->cohort_ID;
}



void DisjointSet::union_of_sets(int& index1, int& index2, double money_transferred)
{


	//Find parents of the sets in index1 and index2
	int index_parent1=find(index1);
	int index_parent2=find(index2);

    //cout<<"My cohort IDS "<<Sets.at(index_parent1)->cohort_ID<<" and "<<Sets.at(index_parent2)->cohort_ID<<endl;
	if ( Sets.at(index_parent1)->cohort_ID == Sets.at(index_parent2)->cohort_ID)
	{
		//The elements are already in the same set, we just need to update the money.
		Sets.at(index_parent2)->money_cohort = Sets.at(index_parent2)->money_cohort + money_transferred;
	}//
	else//the elements are in the collection but their are elements of different sets
	{
		//we need to join the sets and update the money
		if(Sets.at(index_parent1)->parent <= Sets.at(index_parent2)->parent)
		{
			//element at index index_root_elem1 has more children so it will be a parent of the union
			//Update on the size of the new union
			Sets.at(index_parent1)->parent=Sets.at(index_parent1)->parent+Sets.at(index_parent2)->parent;
			//Update that set 2 becomes joins set 1
			Sets.at(index_parent2)->parent=Sets.at(index_parent1)->index_in_set;
			//Update the money in cohort
			Sets.at(index_parent1)->money_cohort=Sets.at(index_parent1)->money_cohort + Sets.at(index_parent2)->money_cohort + money_transferred;
			//I set it to zero to prevent double counting of money (only root of the set has the money for the cohort)
			Sets.at(index_parent2)->money_cohort=0;
			//Since set of elem 2 is now joined to set 1, update cohort_ID;
			Sets.at(index_parent2)->cohort_ID=Sets.at(index_parent1)->cohort_ID;
			(Sets.at(index_parent1)->kids).push_back(Sets.at(index_parent2));
			//Now it would be time to go to kids of set 2 (index_parent2) and update the cohort_ID for them
			
			for(int i=0; i<Sets.at(index_parent2)->kids.size(); i++ )
			{
				Sets.at(index_parent2)->kids.at(i)->cohort_ID=Sets.at(index_parent1)->cohort_ID;
			}
			for (vector<SetNode*>::iterator it= (Sets.at(index_parent2)->kids).begin(); it!=(Sets.at(index_parent2)->kids).end();) 
            {
                (Sets.at(index_parent1)->kids).push_back(*it);
                it++;     
            }
            Sets.at(index_parent2)->kids.clear();

            result = setOfRoots.insert(index_parent1);
 	        // Check if element inserted or not
	        if (result.second == true)
		    {
			  MaxSize.insert(Sets.at(index_parent1));
			  MaxActivity.insert(Sets.at(index_parent1));

			}
		}
		else
		{   //As described above but other way around
		    Sets.at(index_parent2)->parent=Sets.at(index_parent2)->parent + Sets.at(index_parent1)->parent;
			Sets.at(index_parent1)->parent=Sets.at(index_parent2)->index_in_set;
			Sets.at(index_parent2)->money_cohort=Sets.at(index_parent1)->money_cohort + Sets.at(index_parent2)->money_cohort + money_transferred;
			Sets.at(index_parent1)->money_cohort=0;
			Sets.at(index_parent1)->cohort_ID=Sets.at(index_parent2)->cohort_ID;
            (Sets.at(index_parent2)->kids).push_back(Sets.at(index_parent1));

    
		    for(int i=0; i<Sets.at(index_parent1)->kids.size(); i++ )
			{
				Sets.at(index_parent1)->kids.at(i)->cohort_ID=Sets.at(index_parent2)->cohort_ID;
			}
			for (vector<SetNode*>::iterator it= (Sets.at(index_parent1)->kids).begin(); it!=(Sets.at(index_parent1)->kids).end();) 
            {
                (Sets.at(index_parent2)->kids).push_back(*it);
                it++;     
            }
            Sets.at(index_parent1)->kids.clear();

			result = setOfRoots.insert(index_parent2);

		    // Check if element inserted or not
	        if (result.second == true)
		    {
			  MaxSize.insert(Sets.at(index_parent2));
			  MaxActivity.insert(Sets.at(index_parent2));

			}
            
		}
	}
}

int DisjointSet::find(int& element)
{
   if(Sets.at(element)->parent <0)
   	return Sets.at(element)->index_in_set;
   else
   	return Sets.at(element)->parent=find(Sets.at(element)->parent);
}

void DisjointSet::max_activity(ostream& output)
{

   MaxActivity.show_max_activity(output);
}


void DisjointSet::find_info(int cohort_find, ostream& output)
{
	roots_sets.clear();
	MaxSize.return_roots(roots_sets);

    bool found_cohort=false;
    if(cohort_find==0)
    {
    	heapify_IDs();
			for(int i=0; i<roots_sets.size(); i++)
		        roots_sets.at(i)->display_node(output);

	found_cohort=true;
    }//cohort id is 0 print all
    else
    {
    		for(int i=0; i<roots_sets.size(); i++)
			{
				if(roots_sets.at(i)->cohort_ID==cohort_find)
				{
		            roots_sets.at(i)->display_node(output);

					found_cohort=true;
				}
			}
    }

	if(!found_cohort)
	{
		output<<endl;
	}
}

void DisjointSet::max_size(ostream& output)
{
	MaxSize.show_max_size(output);
}

//used for debbugging
void DisjointSet::display(ostream& output)
{
	for (int i=0;i<Sets.size(); i++)
	{
	  cout<<Sets.at(i)->parent<<" "<<Sets.at(i)->cohort_ID<<" "<<Sets.at(i)->money_cohort<<endl;
	}

	//MaxSize.display_the_queue(output);

}




void DisjointSet::display_ids(ostream& output)
{
	
	roots_sets.clear();
	MaxSize.return_roots(roots_sets);
	heapify_IDs();
    for(int i=0;i<roots_sets.size(); i++)
	output<<roots_sets.at(i)->cohort_ID<<endl;
}


void DisjointSet::set_members(int cohort_find, ostream& output)
{
   //flag if root_sets are current 

    roots_sets.clear();
	MaxSize.return_roots(roots_sets);

    bool found_cohort=false;
	for(int i=0; i<roots_sets.size(); i++)
	{
		if(roots_sets.at(i)->cohort_ID==cohort_find)
		{
            output<<roots_sets.at(i)->get_phone_number()<<endl;
			for(int j=0; j<roots_sets.at(i)->kids.size(); j++)
			{
				cout<<roots_sets.at(i)->kids.at(j)->get_phone_number()<<endl;
			}
			found_cohort=true;
		}
	}
	if(!found_cohort)
	{
		output<<endl;
	}
}


void DisjointSet::heapify_IDs()
{
  
  int last_buildheap=roots_sets.size()-1;
  for (int i=roots_sets.size()/2-1; i>=0; i--)
       percolateDownIDs(i, last_buildheap );
}



void DisjointSet::percolateDownIDs(int hole, int last)
{
   int child;
   SetNode* tmp= roots_sets[hole];

   for (; (hole*2) <= last; hole=child)
   {
    child = (2*hole);//right child

    if(  (child != last) && roots_sets.at(child+1)->cohort_ID < roots_sets.at(child)->cohort_ID) 
        child++;
    if( roots_sets.at(child)->cohort_ID < tmp->cohort_ID)
         roots_sets.at(hole)=roots_sets.at(child);
    else
        break;   
   }
   roots_sets.at(hole)=tmp;
}
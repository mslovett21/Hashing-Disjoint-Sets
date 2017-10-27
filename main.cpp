/*******************************************************************************
  Title          : main.cpp
  Author         : Patrycja Krawczuk
  Created on     : May 5th, 2017
  Description    : Main for the program
  Purpose        :
  Usage          : 
  Build with     : 
  Modifications  : 

 
*******************************************************************************/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

#include "command_manager.h"

using namespace std;



/*delete_whitespaces()
* This method removes additional whitespaces (tabs, multiple blanks and so on) between words.
* It separates words of a string with single blank character ASCII (20)
* @param  string     [inout]  line_from_file;
* @returns string in which words are separated by one blank (no other whitesaces)
*/
string delete_whitespace(string line_from_file);

bool telephone_number_validation(string phone_number);

int main(int argc, char* argv[])
{

// Check the number of parameters
  if (argc < 2) 
  {   // Tell the user how to run the program- The program needs 2 arguments: name_of_program, commands_file
        cerr << "Usage (2 arguments): " << argv[0] << " command_file "<<endl;
  return 1;
  }
   
  ifstream data_file (argv[1]);
  //check if command file opens succesfully;
  if (data_file.is_open())
  {   
    cout<<"The command file with data was open succesfully!"<<endl;
  }
  else
  {
    cerr<<"File 1 "<<argv[1]<<" cannot be opened!"<<endl;
    return 1;
  }
  

  istringstream myiss;
  string temp_line;
  string line_no_wspace;
  string temp_string;
  ostream &screen_stream =cout;

  Command_Manager Program_manager;
 

  //*********************************************************
  //* READ THE DATA FROM THE FILE                            *
  //*********************************************************
  while(getline(data_file, temp_line))
  {
    vector<string> temp_vector;
    line_no_wspace=delete_whitespace(temp_line);
   // cout<<"Current command line:"<<line_no_wspace<<endl;
    myiss.str(line_no_wspace);
         
      
         while(getline(myiss,temp_string,' '))
         {
    
           temp_vector.push_back(temp_string);
         }
         myiss.clear();

        //Make sure that it was not an empty line
        if(temp_vector.size()>0)
        {
    
         //INPUT: DATA
         if (temp_vector[0] == "data")
         {
          
            //This type of command 
            if(temp_vector.size()>3)
              {
                if (telephone_number_validation(temp_vector[1]))
                {
                  if (telephone_number_validation(temp_vector[2]))
                  {
                      //cout<<"The numbers are correct"<<endl;

                    if(temp_vector[1]!=temp_vector[2])
                    {
                      //Amount of money is a positive integer
                      bool flag=true;
                      for (int i=0; i<temp_vector[3].size(); i++)
                      {
                          if((temp_vector[3][i]<58) && (temp_vector[3][i]>47))
                           ;
                          else
                            flag=false;
                      }//end of for loop 

                      if (flag==true)
                      {
                        //call special function and pass arguments the line is valid
                      
                        bool success;
                        success=Program_manager.insert_new_data(temp_vector[1],temp_vector[2],temp_vector[3]);

                      }
                      else
                        cerr<<"Error: Amount of money is not a positive integer."<<endl;
                    }//phone numbers are not indentical
                    else{
                        cerr<<"Error: Two phone number on this line are identical."<<endl;}

                   }//second phone number is valid
                   else{
                   cerr<<"Error: Invalid phone number."<<endl;}
                  }
                  else
                   cerr<<"Error: Invalid phone number."<<endl;
              }//end else data command needs 3 arguments
            
           }//end of DATA
         //COMMAND: FIND
         else if (temp_vector[0] == "find")
         {
          if(temp_vector.size()>1)
          {
            if (telephone_number_validation(temp_vector[1]))
            {
              //cout<<"Results of the 'find' command with phone_number: "<<temp_vector[1]<<endl;
              Program_manager.find_cohort(temp_vector[1],cout);
            }
            else
              cerr<<"Error: Invalid phone_number"<<endl;

          }//check size
          else
            cerr<<"Not enough arguments for find command: find phone-number"<<endl;
 
         }//end of if else FIND
         else if (temp_vector[0] == "members")
         {
          if (temp_vector.size()<2)
            cerr<<"Not enough arguments for members command: members cohort-id"<<endl;
          else 
           { 

            int cohort_id= stoi(temp_vector[1]);
            cout<<"Results of the 'members' command with cohort-id: "<<cohort_id<<endl;
            Program_manager.display_members( cohort_id, cout);
           }
         }
         else if(temp_vector[0] == "max-size")
         {
           cout<<"Results of the 'max-size' command:"<<endl;
           Program_manager.display_max_size_cohort(cout);
         }
         else if(temp_vector[0] == "max-activity")
         {
           cout<<"Results of the 'max-activity' command:"<<endl;
           Program_manager.display_max_activity_cohort(cout);
         }

         else if (temp_vector[0] == "cohort-ids")
         {
           cout<<"Results of the 'cohort-ids' command:"<<endl;
           Program_manager.display_cohort_ids(cout);

         }
         else if(temp_vector[0] == "info")
         {
            if (temp_vector.size()<2)
            cerr<<"Not enough arguments for info command: info cohort_id"<<endl;
            else 
            {
              
              int cohort_id= stoi(temp_vector[1]);
              cout<<"Results of the 'info' command with argument "<<cohort_id<<" :"<<endl;
              Program_manager.display_info( cohort_id, cout);
            }
         }
         else
         {
          cout<<"Undefined instruction. Proceeding to the next instruction."<<endl;
         }
        
       
   
       }//end of if vector size is at least 1 
      }

   data_file.close();
  
	
	return 0;
}




bool telephone_number_validation(string phone_number)
{
  //cout<<"The phone number is  :"<<phone_number<<endl;
  //Check if the number is 12 character longs (2 hypens and 10 digits)
  if(phone_number.length() != 12)
    return false;
  //Make sure position 4th and 8th character are hypens
  if(phone_number[3] != char(45) || phone_number[7] != char(45))
    return false;
  //Make sure all the other characters are digits [0:9]
  for (int i=0; i<3; i++)
  {
    if ((phone_number[i]<58) && (phone_number[i]>47))
      ;
    else
      return false;
  }
    for (int i=4; i<7; i++)
  {
    if ((phone_number[i]<58) && (phone_number[i]>47))
      ;
    else
      return false;
  }
    for (int i=8; i<12; i++)
  {
    if ((phone_number[i]<58) && (phone_number[i]>47))
      ;
    else
      return false;
  }

  return true;
  

}
string delete_whitespace(string line_from_file)
{

  int i=0;
  string result=""; 
  while(i<line_from_file.size())
  {
    string temp="";
    while((isspace(line_from_file[i])==false) && (i<line_from_file.size()))//while not a whitespace
    {

      temp=temp+line_from_file[i];
      i++;
    }
    if(temp.size()>0)//I actually found some valid content
    {
      transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
      if(result=="")
      {
        result=temp;
      }
      else
      {
        result=result+" "+temp;
      }
    }
    i++;
  }
  return result;

}
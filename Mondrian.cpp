/*
 * File:   Mondrian.cpp
 * Author: george
 *
 * Created on June 6, 2014, 12:08 PM
 */

#include "Mondrian.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <map>
#include <math.h>
#include <unistd.h>
#include <sstream>
#include <stdlib.h>
using namespace std;

Mondrian::Mondrian(map<int,string> d,int kay) {
         k = kay;
         data = d;
         for (std::map<int,string>::iterator it=data.begin(); it!=data.end(); ++it){
    }
}

void Mondrian::Anonymize(vector<vector <int> > R2data){

   if(data.empty() || R2data.empty()){
    cout<< "\nDATA IS NULL\n";
        exit(0);
    }
     int max;
     int selectedRow;
     int median;
    //-------------------------------------1st step , choose the attribute/column
     map<int,int> temple;                //with the more different values
      max = 0;
     int Crow = 0;
     for(int i=0;i<R2data.size();i++){
        for(int j=0;j<R2data.at(i).size();j++){
            temple[R2data[i][j]];
        }
         if(max<temple.size()){
            max = temple.size();
            selectedRow = i;
         }
          temple.clear();
     }
     //-----------------------------------------------------------end of 1st step
     //---------------------------------------------------------2nd step : check the requirements,
     if(R2data[selectedRow].size() >= 2*k){
             R2data = BubbleSort(R2data,selectedRow);
             vector<vector<int> > temp1;
             vector<vector<int> > temp2;
			 
             if(R2data[selectedRow].size()%2 == 0){  // Check if the number of the column is odd or even and separate
                                                     // to 2 data sets accordingly
                         for(int i=0;i<R2data.size();i++){
                           vector<int> tmp;
                           for(int j=0;j<R2data[i].size()/2;j++){
                               tmp.push_back(R2data[i][j]);
                           }
                           temp1.push_back(tmp) ;
                           tmp.clear();
						   
                           for(int j=R2data[i].size()/2;j<R2data[i].size();j++){
                               tmp.push_back(R2data[i][j]);
                           }
                           temp2.push_back(tmp) ;
                        }
            }
            else{
                         for(int i=0;i<R2data.size();i++){
                           vector<int> tmp;
                           for(int j=0;j<(R2data[i].size()-1)/2;j++){
                               tmp.push_back(R2data[i][j]);
                           }

                           temp1.push_back(tmp) ;
                           tmp.clear();

                           for(int j=(R2data[i].size()-1)/2;j<R2data[i].size();j++){
                               tmp.push_back(R2data[i][j]);
                           }
                           temp2.push_back(tmp) ;
                        }
            }
                Anonymize(temp1);   //3rd step : the two new datasets are inserted into the Anonymize function recursively
                Anonymize(temp2);
     }
     else{  //if the size of the columns isnt bigger than 2*k , then we group the elemnts of each column accodint to the min and the max
            // and print them to a file as anonymized.

                ofstream myfile;

                myfile.open ("anonymizedData.txt",std::ios_base::app);
               // myfile << "Writing this to a file.\n";

               int minf1,maxf1;
                total_classes++;
                total_eq = total_eq+R2data[0].size();

                for(int j=0;j<R2data[0].size();j++){
                          for(int i = 0;i<R2data.size();i++){
                             minf1 = minf(R2data[i]);
                             maxf1 = maxf(R2data[i]);

                           if(minf1 == maxf1){
                                   if(i!=R2data.size()-1){
                                       myfile<<minf1<<",";
                                       if(j==0)
                                           cout<<minf1<<",";
                                    }
                                    else{
                                        myfile<<minf1;

                                        if(j==0)
                                           cout<<minf1<<" : "<<R2data[0].size()<<endl;
                                    }

                           } else{
                                  if(i!=R2data.size()-1){
                                   myfile<<"["<<minf1<<":"<<maxf1<<"],";

                                  if(j==0)
                                     cout<<"["<<minf1<<":"<<maxf1<<"],";
                                   }
                                   else{
                                     myfile<<"["<<minf1<<":"<<maxf1<<"]";

                                     if(j==0)
                                       cout<<"["<<minf1<<":"<<maxf1<<"]"<<" : "<<R2data[0].size()<<endl;
                                   }
                            }
                           }
                           myfile<<endl;
                           }
                     myfile.close();
           }
     }

//finds the minimum element of a column
int Mondrian::minf(vector<int> tmp){
   int min = tmp[0];
    for(int i=0;i<tmp.size();i++){
      if(tmp[i]<min)
        min = tmp[i];
    }
    return min;
}

void Mondrian::print_meanAverage(){

    cout<<"\nNumber of Equivalence Classes : "<<total_classes<<endl;
    cout<<"Average Size of Equivalence Class :"<<total_eq/total_classes<<endl;

}


//finds the maximum element of a column
int Mondrian::maxf(vector<int> tmp){
   int max = tmp[0];
    for(int i=0;i<tmp.size();i++){
      if(tmp[i]>max){
        max = tmp[i];
        }
    }
    return max;
}

//Sorts the data of all columns according to the selected column(the one who has the most different elements)
vector< vector<int> > Mondrian::BubbleSort(vector<vector <int> > dt,int selectedRow)
{

      int i, j, flag = 1;    // set flag to 1 to start first pass
      int temp;             // holding variable
      int SRlength = dt[selectedRow].size();
      for(i = 1; (i <= SRlength) && flag; i++)
     {
          flag = 0;
          for (j=0; j < (SRlength -1); j++)
         {
               if (dt[selectedRow][j+1] > dt[selectedRow][j])      // ascending order simply changes to <
              {
                      for(int i = 0;i<dt.size();i++){

                          temp = dt[i][j];             // swap elements
                          dt[i][j] = dt[i][j+1];
                          dt[i][j+1] = temp;
                      }
                        flag = 1;               // indicates that a swap occurred.
               }
          }
     }
     return dt;   //arrays are passed to functions by address; nothing is returned
}

vector<vector<int> > Mondrian::InitiateArrays() {
		int sizeX = data.size();
		int sizeY = 0;
		string input;

                for (std::map<int,string>::iterator it=data.begin(); it!=data.end(); ++it){
                        input = it->second;
                        break;
                 }
		istringstream ss(input);
		string token;
		while (getline(ss, token, ',')) {
			sizeY++;
		}

	     int i = 0;
	     int j=0;
             for (map<int, string>::iterator it = data.begin(); it != data.end(); ++it) {
                input = it->second;
                istringstream os(input);
                string temp;

                j=0;
		        while(getline(os,temp,',')){

					if(i==0){
					 vector <int> tmpdata; //----------------------------------------
					 tmpdata.push_back(atoi(temp.c_str()));
					 Rdata.push_back(tmpdata);
					 j++;
					 }
					 else{
							Rdata[j].push_back(atoi(temp.c_str()));
					 j++;
					 }
		        }
		        j=0;
		        i++;
               }

	      return Rdata;
}




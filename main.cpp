/*
 * File:   main.cpp
 * Author: george
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <stdlib.h>

#include "Mondrian.h"
using namespace std;

map<int,string> read(){
  string line;
  int i = 1;
  map<int,string> data;

  ifstream myFile("data.txt");

  if(myFile.is_open()){
	while(getline(myFile,line)){ //! myFile.eof()

            data[i] = line;
	    i++;
	}
  }

  myFile.close();

   return data;

}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		cerr<<"Usage: "<<argv[0]<< " k"<<endl;
		exit(-1);
	}

	
  map<int ,string> data;
  vector< vector<int> > R2data;
	int k=atoi(argv[1]);
	cout<<"K: "<<k<<endl;

 data = read(); //reads the data from the file
 Mondrian m1(data,k); //creates a mondrian object with inputs the data and the k.
 R2data = m1.InitiateArrays(); //from the data map<int,string> is created a structure vector<vector<int> >
 m1.Anonymize(R2data); //we anonymize the data and print them in a file
 m1.print_meanAverage();

  return 0;

}

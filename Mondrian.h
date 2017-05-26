/*
 * File:   Mondrian.h
 * Author: george
 *
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
#ifndef MONDRIAN_H

#define	MONDRIAN_H

class Mondrian {
public:
    Mondrian(map<int,string> data,int k);
    vector< vector<int> > InitiateArrays();
    void Anonymize(vector<vector<int> > R2data);
    float find_median(vector< vector<int> > dt,int selectedRow);
    vector< vector<int> > BubbleSort(vector< vector<int> > dt,int selectedRow);
    int minf(vector<int> tmp);
    int maxf(vector<int> tmp);
    void print_meanAverage();
private:
     int k;
     map<int,string> data;
     vector< vector<int> > Rdata;
     float total_eq = 0;
     int total_classes = 0;
};

#endif	/* MONDRIAN_H */


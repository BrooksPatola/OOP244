

#include "tools.h"
#include "graph.h"
#include <iostream>
using namespace std;

void getSamples(int samples[], int noOfSamples){
   int i;
     for (i = 0; i < noOfSamples; i++){
         cout << (i + 1) << "/" << noOfSamples << ": ";
             samples[i] = getInt(1, 1000000);
               }
  }


int findMax(int samples[], int noOfSamples){
	  int max = samples[0];
	    int i;
	      for (i = 1; i < noOfSamples; i++){
		          if (max < samples[i]) max = samples[i];
			    }
	        return max < 70 ? 70 : max;
}

void printBar(int val, int max){
	  int i;
	    for (i = 0; i < 70 * val / max; i++){
		        cout << "*";
			  }
	      cout << " " << val << endl;
}


void printGraph(int samples[], int noOfSamples){
	  int max = findMax(samples, noOfSamples);
	    cout << "Graph:" << endl;
	      for (int i = 0; i < noOfSamples; i++){
		          printBar(samples[i], max);
			    }
}

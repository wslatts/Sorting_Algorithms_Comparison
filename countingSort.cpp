/*
 * countingSort.cpp
 *
 * COP 4531, Project 1
 * Wendy Slattery
 * 2/29/20
 *
 * compile: g++ -o countingSort.exe countingSort.cpp
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <sys/time.h>

using namespace std;

/* Global Variables */
vector<vector<unsigned int> > inputs(11);

ofstream outfile;

/* Helpers */
void buildElevenInputsOfRandoms() {
    unsigned int lengths[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };

    for(unsigned int i = 0; i < 11 ; i++){
        for(unsigned int j= 0; j < lengths[i]; j++){
            inputs[i].push_back(rand() % 65536);
        }
    }
}

/* Algorithm Specific Functions */
vector<unsigned int> countingSort( vector<unsigned int>& input, unsigned int size){

    /* create a map structure to store the frequency of input elements */
    map<int, int> frequencyMap;

    /* for every element in unsorted list, add to map */
    for(unsigned int i = 0; i < size; i++){
        frequencyMap[ input[i] ]++;
    }


    /* while traversing map, overwrite the values in input
     * with the sorted order of values which map structure does */
    int i = 0;
    map<int, int>::iterator it;
    for(it = frequencyMap.begin(); it != frequencyMap.end(); ++it){
        int value = it->first;
        int frequency = it->second;

        while(frequency--){
            input[i++]= value;
        }
    }

    return input;
}

int main() {

    srand(time(0));
    outfile.open("resultsCounting.txt", ios::out);
    struct timeval start, end;

    buildElevenInputsOfRandoms();

    outfile << "\nTime Results for Counting Sort\n" << endl;
    outfile << "=======================================" << endl;


    for(int i = 0; i < 11; i++){
        int sizeI = inputs[i].size();
        vector<unsigned int> sorted;
        vector<unsigned int>::iterator itr;

        //print unsorted list to outfile
        outfile << "\n" << sizeI << " random numbers\n" << endl;
        outfile << "** I ** input values unsorted size: " << sizeI << endl;
        for(itr = inputs[i].begin(); itr < inputs[i].end(); itr++){
            outfile << *itr << " ";
        }
        outfile << endl << endl;

        /* start timer */
        gettimeofday (&start, NULL);
        ios_base::sync_with_stdio(false);

        //run algorithm
        sorted = countingSort(inputs[i], sizeI);

        // stop timer and calculate sort function
        gettimeofday(&end, NULL);
        double time_taken;
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

        //print sorted list to outfile
        outfile << "\n** S ** sorted list size: " << sorted.size() << endl;
        for(unsigned int i = 0; i < sorted.size(); i++){
            outfile << sorted[i] << " ";
        }
        outfile << "\n" << endl;
        cout << "\n" << endl;

        // output results to screen and outfile
        outfile << "Process time: " << fixed << time_taken << setprecision(6) << " sec" << endl;
        outfile << "vector size: " << sizeI << endl;
        cout << "Process time: " << fixed << time_taken << setprecision(6) << " sec" << endl;
        cout << "vector size: " << sizeI << endl;
        outfile << "\n\n*************************" << endl;


    }
    outfile << "=======================================" << endl;
    outfile << "=======================================" << endl;
    outfile << "\n Counting Sort is complete" << endl;
    outfile.close();

    return 0;
}


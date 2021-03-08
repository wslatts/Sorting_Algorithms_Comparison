/*
 *bucketSort.cpp
 *
 * COP 4531, Project 1
 * Wendy Slattery
 * 3/5/20
 *
 * compile: g++ -o bucketSort.exe bucketSort.cpp
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sys/time.h>
#include <algorithm>

using namespace std;


/* Global Variables */
vector<vector<double> > doubleInputs(11);
ofstream outfile;

void buildElevenDoublesOfRandoms() {
    int lengths[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    for(int i = 0; i < 11 ; i++){
        for(int j= 0; j < lengths[i]; j++) {
            double random = ((double)(rand()) / (double)RAND_MAX);
            if (random == 1.0) {
                doubleInputs[i].push_back(random - .11);
            }
            doubleInputs[i].push_back(random);
        }
    }
}

vector<double> bucketSort( vector<double>& input, int size){

    vector<vector<double> > buckets(size);

    for(int i = 0; i < size; i++){
        int bucketIndex = size * input[i];
        buckets[bucketIndex].push_back(input[i]);
    }

    for (int i = 0; i < size; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    int index = 0;
    for(int i = 0; i < size; ++i){
        for(unsigned int j = 0; j < buckets[i].size(); ++j){
            input[index++] = buckets[i][j];
        }
    }

    return input;
}

int main() {

    srand(time(0));
    outfile.open("resultsBucket.txt", ios::out);
    struct timeval start, end;

    buildElevenDoublesOfRandoms();

    outfile << "\nTime Results for Bucket Sort\n" << endl;
    outfile << "=======================================" << endl;


    for(int i = 0; i < 11; i++){
        int sizeI = doubleInputs[i].size();
        vector<double> sorted(sizeI);
        vector<double>::iterator itr;

        //print unsorted list to outfile
        outfile << "\n" << sizeI << " random numbers\n" << endl;
        outfile << "** I ** input values unsorted size: " << sizeI << endl;
        for(itr = doubleInputs[i].begin(); itr < doubleInputs[i].end(); itr++){
            outfile << *itr << " ";
        }
        outfile << endl << endl;

        /* start timer */
        gettimeofday (&start, NULL);
        ios_base::sync_with_stdio(false);

        //run algorithm
        sorted = bucketSort(doubleInputs[i], sizeI);

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
    outfile << "\n Bucket Sort is complete" << endl;
    outfile.close();

    return 0;
}



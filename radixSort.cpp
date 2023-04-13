/*
 * radixSort.cpp
 *
 * Data Structures & Algorithms, Project 1
 * Wendy Slattery
 * 2/29/20
 *
 *  compile: g++ radixSort.exe radixSort.cpp
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
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


int calculateMax(vector<unsigned int>& V, int size){

    unsigned int max = V.at(0);
    for(int i = 1; i < size; i++){
        if( V.at(i) > max ){
            max = V.at(i);
        }
    }
    return max;
}

void countSort( vector<unsigned int>& V, int size, int exp ){

    // Count[i] array will be counting the number of array values having that 'i' digit at their (exp)th place.
    int output[size];
    int count[10] = {0};

    /* increment count indices with the input values/exp mod 10 */
    for( int i = 0; i < size; i++ ){
        unsigned int atRemainder = (V[i] / exp) % 10;
        count[atRemainder]++;
    }

    /* convert i to its actual position in output array
     * calculating their cumulative count */
    for( int i = 1; i < 10; i++){
        count[i] += count[i-1];
    }

    /* build output array */
    for ( int i = size - 1; i >= 0; i-- ){
        unsigned int remainder = (V[i] / exp) % 10;

        output[ count[remainder] -1 ] = V[i];
        count[remainder]--;
    }

    /* rewrite input vector with the sorted output */
    for( int i = 0; i < size; i++){
        V[i] = output[i];
    }
}

vector<unsigned int> radixSort( vector<unsigned int>& input, int size){

    /* max will reveal number of places in digits to sort */
    int max = calculateMax(input, size);


    /* perform countSort on each digit's place passing the exponent instead of
     * digit number.  exp is 10^i where i is current digit number */
    for (int exp = 1; max/exp > 0; exp *= 10){
        countSort(input, size, exp);
    }

    return input;
}

int main() {

    srand(time(0));
    outfile.open("resultsRadix.txt", ios::out);
    struct timeval start, end;

    buildElevenInputsOfRandoms();

    outfile << "\nTime Results for Radix Sort\n" << endl;
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
        sorted = radixSort(inputs[i], sizeI);

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
    outfile << "\n Radix Sort is complete" << endl;
    outfile.close();

    return 0;
}

/*
 * heapSort.cpp
 *
 * Data Structures & Algorithms, Project 1
 * Wendy Slattery
 * 2/29/20
 *
 * compile: g++ -o heapSort.exe heapSort.cpp
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
void heapify( vector<unsigned int>& V, int i, int size){

    /* define parent position as index i and left/right children
     * max value starts at value of i, then compare children
     * to parent
     * */
    int maxAtItr = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    /* if value at left child > maxAtItr */
    if(left < size && (V[left] > (V[maxAtItr]))){
        maxAtItr = left;
    }
    /* if value at right child > max */
    if(right < size && V[right] > V[maxAtItr]){
        maxAtItr = right;
    }
    /* if max is not parent, then it's a child who needs to swap up */
    if(maxAtItr != i){
        swap(V[i], V[maxAtItr]);
        heapify(V, maxAtItr, size);
    }
}

void buildHeap( vector<unsigned int>& V, int size){

    /* going bottom up */
    for(int i = (size / 2) - 1; i >= 0; i-- ){
        heapify(V, i, size);
    }
}

vector<unsigned int> heapSort( vector<unsigned int>& input, int size){

    buildHeap(input, size);

    /* pull one element at a time from vector end/right child
     * and swap with root */
    for(int i = size - 1; i >= 0; i--){
        swap(input[0], input[i]);
        heapify(input, 0, i);
    }

    return input;
}

int main() {

    srand(time(0));
    outfile.open("resultsHeap.txt", ios::out);
    struct timeval start, end;

    buildElevenInputsOfRandoms();

    outfile << "\nTime Results for Heap Sort\n" << endl;
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
        sorted = heapSort(inputs[i], sizeI);

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
    outfile << "\n Heap Sort is complete" << endl;
    outfile.close();

    return 0;
}


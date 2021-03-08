/*
 *quickSort.cpp
 *
 * COP 4531, Project 1
 * Wendy Slattery
 * 2/29/20
 *
 * compile: g++ -o quickSort.exe quickSort.cpp
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
    unsigned int lengths[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    for(unsigned int i = 0; i < 11 ; i++){
        for(unsigned int j= 0; j < lengths[i]; j++){
            inputs[i].push_back(rand() % 65536);
        }
    }
}


int partition(vector<unsigned int>& V, int left, int right){
    unsigned int pivot = left + (right - left) / 2;
    unsigned int pValue = V[pivot];

    while( left <= right ){
        while(V[left] < pValue){
            left++;
        }
        while(V[right] > pValue){
            right--;
        }
        if( left <= right ){
            swap ( V[left], V[right] );
            left++;
            right--;
        }
    }
    return left;
}

void qsort(vector<unsigned int>& V, int left, int right){
    if(left < right) {
        int pivot = partition(V, left, right);
        qsort(V, left, pivot - 1);
        qsort(V, pivot, right);
    }
}

vector<unsigned int> quickSort( vector<unsigned int>& input, int size){

    /* break list in two sizes, ideally in center and recursively sort */
    qsort(input, 0, size - 1);

    return input;
}




int main() {

    srand(time(0));
    outfile.open("resultsQuick.txt", ios::out);
    struct timeval start, end;

    buildElevenInputsOfRandoms();

    outfile << "\nTime Results for Quick Sort\n" << endl;
    outfile << "=======================================" << endl;


    for(int i = 0; i < 11; i++){
        int sizeI = inputs[i].size();
        vector<unsigned int> sorted(sizeI);
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
        sorted = quickSort(inputs[i], sizeI);

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
    outfile << "\n Quick Sort is complete" << endl;
    outfile.close();

    return 0;
}


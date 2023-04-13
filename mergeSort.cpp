/*
 * mergeSort.cpp
 *
 * Data Structures & Algorithms, Project 1
 * Wendy Slattery
 * 2/29/20
 *
 *  compile: g++ -o mergeSort.exe mergeSort.cpp
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


void merge(vector<int>& input, vector<int>& left, vector<int>& right){
    int sizeLft = left.size();
    int sizeRgt = right.size();

    // indices of each vector
    int itrInput = 0;
    int itrLft = 0;
    int itrRgt = 0;

    // halve and copy input to each subhalf
    while (itrLft < sizeLft && itrRgt < sizeRgt){
        if (left[itrLft] < right[itrRgt]) {
            input[itrInput] = left[itrLft];
            ++itrLft;
        }
        else {
            input[itrInput] = right[itrRgt];
            ++itrRgt;
        }
        ++itrInput;
    }

    while (itrLft < sizeLft){
        input[itrInput] = left[itrLft];
        ++itrLft;
        ++itrInput;
    }

    while (itrRgt < sizeRgt){
        input[itrInput] = right[itrRgt];
        ++itrRgt;
        ++itrInput;
    }
}


void mergeSort(vector<int> &input) {
    if (input.size() <= 1) {
        return;
    }

    vector<int> leftHalf;
    vector<int> rightHalf;
    int midPoint = input.size() / 2;

    for (int i = 0; i < midPoint; i++) {
        leftHalf.push_back(input[i]);
    }
    for (unsigned int i = 0; i < input.size() - midPoint; i++){
        rightHalf.push_back(input[midPoint + i]);
    }

    mergeSort(leftHalf);
    mergeSort(rightHalf);
    merge(input, leftHalf, rightHalf);

}

int main() {

    srand(time(0));
    outfile.open("resultsMerge.txt", ios::out);
    struct timeval start, end;

    buildElevenInputsOfRandoms();

    outfile << "\nTime Results for Merge Sort\n" << endl;
    outfile << "=======================================" << endl;


    for(int i = 0; i < 11; i++){
        int sizeI = inputs[i].size();
        //vector<int> sorted(sizeI);
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
        mergeSort(reinterpret_cast<vector<int> &>(inputs[i]));

        // stop timer and calculate sort function
        gettimeofday(&end, NULL);
        double time_taken;
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

        //print sorted list to outfile
        outfile << "** S ** sorted values size: " << sizeI << endl;
        for(itr = inputs[i].begin(); itr < inputs[i].end(); itr++){
            outfile << *itr << " ";
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
    outfile << "\n Merge Sort is complete" << endl;
    outfile.close();

    return 0;
}



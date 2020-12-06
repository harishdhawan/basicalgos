/**
 * TEST CODE
 * */
#include "bsearch.h"
#include <iostream>
#include <stdlib.h>
#include <chrono>
using namespace std;
#define NUMELEMS(arr) (sizeof(arr)/sizeof(arr[0]))

int lsearch(int arr[], int val, int f, int l) {
    for(;f<=l;++f){
        if(arr[f] >= val) return f;
    }
    return l+1;
}

int main(){
    static const int arraySize = 20000;
    int arr[arraySize] = {0};

    // fill with random increamenting numbers to keep it sorted
    srand((unsigned) time(0));
    arr[0] = rand() % 10 + 1;
    for(int i = 1; i < arraySize; ++i) {
        int incr = rand() % 10 + 1;
        arr[i] = arr[i-1] + incr;
    }
    std::cout<<"Generated random arr within range "<<arr[0]<<" and "<<arr[arraySize-1]<<std::endl;

    // Fill the search array with random search values
    static const int searchArraySize = 5000;
    int searchedArr[searchArraySize] = {0};
    //srand(5678);
    for(int i = 0; i < searchArraySize; ++i) {
        searchedArr[i] = rand() % (arr[arraySize-1] + 100) - 50;
    }

    auto test_perf = [&]()->double{
        auto startTime = chrono::steady_clock::now();
        for(int i = 0; i<searchArraySize; ++i) {
            int bsearchResult = bsearch(arr, searchedArr[i], 0, arraySize);
        }
        chrono::duration<double, std::micro> elapsed_microseconds = chrono::steady_clock::now() - startTime;
        return elapsed_microseconds.count();
    };

    // test perf
    
    double avg_time = 0.0L;
    double numcases = 500;
    for(int i = 0; i<numcases; ++i){
        auto t = test_perf();
        avg_time += test_perf() / numcases;
    }
    cout<<"Time taken for "<<searchArraySize<<" searches in sorted array of size "<<arraySize << ": "<<avg_time<<". Time per search: "<<avg_time*1.0/searchArraySize;

    // test correctness
    int failCount = 0;
    for(int i = 0; i<searchArraySize; ++i) {
        auto bsearchResult = bsearch<int>(arr, searchedArr[i], 0L, static_cast<long>(arraySize-1));
        int lsearchResult = lsearch(arr, searchedArr[i], 0, arraySize-1);
        if(bsearchResult!=lsearchResult){
            ++failCount;
            cout<<endl<<searchedArr[i]<<" : "<<bsearchResult<<" X FAILED. ("<<lsearchResult<<")";
        }
    }
    cout<<endl<<failCount<<" test cases failed "<<endl;

}
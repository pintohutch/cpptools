// merge_sort.cpp
//
// Author: Daniel Clark, 2015

// Headers
#include <iostream>

// Namespace
using namespace std;

// Print the array to screen
void print_array(int *arr, int size) {
    // For each element in the array, print to cout
    for (int idx = 0; idx < size; idx++) {
        cout << arr[idx];
        if (idx != size-1) {
            cout << ", ";
        }
        else {
            cout << '\n';
        }
    }
}


// Merge sort function
void merge_sort(int *arr, int size) {

}


// Main function
int main() {

    // Declare/init variables
    int unsorted_array[] = { 5, 4, 1, 8, 7, 2, 6, 3, 4, 1 };

    // Get length of array
    int array_size = sizeof(unsorted_array) / sizeof(*unsorted_array);

    // Print unsorted values
    cout << "Unsorted array elements:\n";
    print_array(unsorted_array, array_size);

    //

    return 0;
}

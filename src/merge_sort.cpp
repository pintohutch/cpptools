// merge_sort.cpp
//
// Author: Daniel Clark, 2015

// Headers
#include <iostream>

// Namespace
using namespace std;

// Print the array to screen
void print_array(int * arr, int size) {
    cout << "{";
    // For each element in the array, print to cout
    for (int idx = 0; idx < size; idx++) {
        cout << arr[idx];
        if (idx != size-1) {
            cout << ", ";
        }
        else {
            cout << "}\n";
        }
    }
}


// Function to do the sorting and merging of arrays
void merge(int * arr, const int low, const int mid, const int high)
{
    /*
    Function to actually merge and sort the array elements

    Parameters
    ----------
    arr : integer ptr
        pointer to the head of an integer array to sort
    low : constant integer
        the low index of the array to start evaluation at
    mid : constant integer
        the mid point (mid+1 for odd lengths)
    high : constant integer
        the high index of the array to end evaluation at
    */

    // Init variables
    int * work_arr = new int[high+1-low];
    int work_idx = 0;
    int fhalf_idx = low;
    int lhalf_idx = mid+1;

    // Merges the two array's into work_arr[]
    // until we've gone through one of them
    while((fhalf_idx <= mid) && (lhalf_idx <= high))
    {
        // If first half idx val is <= last half idx val
        if(arr[fhalf_idx] <= arr[lhalf_idx])
        {
            // Put first half idx val in worker array
            work_arr[work_idx] = arr[fhalf_idx];
            // Increment first half idx
            fhalf_idx++;
        }
        // Otherwise, last half idx val is > first half idx val
        else
        {
            // Put last half idx val in worker array
            work_arr[work_idx] = arr[lhalf_idx];
            // Icrement last half idx
            lhalf_idx++;
        }
        // Index worker array idx
        work_idx++;
    }

    // If first half idx made it past mid, then first half is sorted
    if(fhalf_idx > mid)
    {
        for(int k = lhalf_idx; k <= high; k++)
        {
            work_arr[work_idx] = arr[k];
            work_idx++;
        }
    }
    else
    {
        for(int k = fhalf_idx; k <= mid; k++)
        {
            work_arr[work_idx] = arr[k];
            work_idx++;
        }
    }

    // Prints into the original array
    for(int k=0; k <= high-low; k++)
    {
        arr[k+low] = work_arr[k];
    }
    delete[] work_arr;
}


// Merge sort function
void merge_sort(int * arr, const int low, const int high)
{
    /*
    Function to perform top-down merge sort

    Parameters
    ----------
    arr : integer ptr
        pointer to integer (array)
    low : constant int
        the low (first) index of the array
    high : constant int
        the high (last) index of the array

    Returns
    -------

    */

    // Declare mid point index integer
    int mid;
    int arr_size = (high-low)+1;

    // If there is more than one element in array, split it recursively
    if( low < high ) {
        cout << "Splitting array: ";
        print_array(arr, arr_size);

        // Get halfway point
        mid = (low+high)/2;

        // Split left half recursively until only two elements
        cout << "Splitting left side\n";
        merge_sort(arr, low, mid);

        // Split right half - first time with only two elements
        cout << "Splitting right side\n";
        merge_sort(arr, mid+1, high);

        // Merge the array
        cout << "Merging/sorting array: ";
        print_array(arr, arr_size);
        merge(arr, low, mid, high);

        // Print full array so far...
        cout << "Array now: ";
        print_array(arr, 10);
    }
}


// Main function
int main()
{
    // Declare/init variawork_arrles
    int input_arr[] = {5, 4, 1, 8, 7, 2, 6, 3, 4, 1};

    // Get length of array - size (work_arrytes) of variable / size of element
    int array_size = sizeof(input_arr) / sizeof(*input_arr);

    // Print unsorted values
    cout << "Unsorted array elements:\n";
    print_array(input_arr, array_size);

    // Merge-sort the array
    merge_sort(input_arr, 0, (array_size-1) );

    // Print sorted values
    cout << "Sorted array elements:\n";
    print_array(input_arr, array_size);

    return 0;
}

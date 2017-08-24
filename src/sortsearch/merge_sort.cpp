// merge_sort.cpp
//
// Author: Daniel Clark, 2015

// Headers
#include <iostream>

// Namespace
using namespace std;

// Print the array to screen
void print_array(int * arr, int size)
{
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

    // First part of array is all sorted
    // Sorted all we can so far, re-populate array with leftovers
    if(fhalf_idx > mid)
    {
        for(int k = lhalf_idx; k <= high; k++)
        {
            work_arr[work_idx] = arr[k];
            work_idx++;
        }
    }
    // Sorted from mid to end and reached end of array
    // Sorted all we can so far, re-populate array with leftovers
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

    // Free up memory for working array via delete[]
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
    */

    // Declare mid point index integer
    int mid;
    int arr_size = (high-low)+1;

    // If there is more than one element in array, split it recursively
    if( low < high ) {
        // Print integer ptr + low index for new array start
        cout << "Splitting array: ";
        print_array(arr+low, arr_size);

        // Get halfway point
        mid = (low+high)/2;

        // Split left half recursively until only two elements
        // Then right half will call this to recursively split right
        cout << "Splitting left side\n";
        merge_sort(arr, low, mid);

        // Split right half recursively of left half, then of right half
        cout << "Splitting right side\n";
        merge_sort(arr, mid+1, high);

        // Merge and sort the original array within passed indices
        cout << "Merging/sorting array: ";
        print_array(arr+low, arr_size);
        merge(arr, low, mid, high);

        // Print full array so far...
        cout << "Array now: ";
        print_array(arr, 10);
    }
    // Return when low >= high
    cout << "Returning from recursion one level...\n";
}


// Main function
int main2()
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

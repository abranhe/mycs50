/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    
    // binary search
    int divider_index = n / 2;
    
    
    if (value == values[divider_index])
    {
        return true;
    }
    // stop if value is not found
    else if (n == 1)
    {
        return false;
    }
    // search left and throw right
    else if (value < values[divider_index])
    {
        int left_array[divider_index];
        for (int i = 0; i < divider_index; i++)
        {
            left_array[i] = values[i];
        }
        return search(value, left_array, divider_index);
    }
    // search right and throw left
    else if (value > values[divider_index])
    {
        if (n == 2)
        {
            return false;
        }
        int right_n = n - divider_index - 1;
        int right_array[right_n];
        for (int i = 0; i < right_n; i++)
        {
            right_array[i] = values[i + divider_index + 1];
        }
        return search(value, right_array, right_n);
    }
    
    // linear search
    // for (int i = 0; i < n; i++)
    // {
    //     if (values[i] == value)
    //     {
    //         return true;
    //     }
    // }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // counting sort O(n)
    int max_value = 0;
    for (int i = 0; i < n; i++)
    {
        if (max_value < values[i])
        {
            max_value = values[i];
        }
    }
    
    int counting_sort[max_value + 1];
    for (int i = 0; i <= max_value; i++)
    {
        counting_sort[i] = 0;
    }
    
    for (int i = 0; i < n; i++)
    {
        counting_sort[values[i]] += 1;
    }
    
    int counting_index = 0;
    for (int i = 0; i <= max_value; i++)
    {
        for (int j = counting_sort[i]; j > 0; j--)
        {
            values[counting_index] = i;
            counting_index += 1;
        }
    }
    
    // TODO: implement an O(n^2) sorting algorithm
    
    // selection sort
    // int smallest_value;
    // int smallest_index;
    
    // for (int i = 0; i < n; i++)
    // {
    //     int smallest_value = values[i];
    //     int smallest_index = i;
    //     for (int j = i; j < n; j++)
    //     {
    //         if (smallest_value > values[j])
    //         {
    //             smallest_value = values[j];
    //             smallest_index = j;
    //         }
    //     }
        
    //     values[smallest_index] = values[i];
    //     values[i] = smallest_value;
    // }
    
    // insertion sort
    // int temp_value;
    
    // for (int i = 1; i < n; i++)
    // {
    //     for (int j = i - 1, k = i; j >= 0; j--, k--)
    //     {
    //         if (values[k] < values[j])
    //         {
    //             temp_value = values[k];
    //             values[k] = values[j];
    //             values[j] = temp_value;
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }
    // }
    
    // bubble sort
    // int temp_value;
    
    // for (int i = (n - 1); i > 0; i--)
    // {
    //     int recurrence = 0;
    //     for (int j = 0; j < i; j++)
    //     {
    //         if (values[j] > values[j + 1])
    //         {
    //             temp_value = values[j + 1];
    //             values[j + 1] = values[j];
    //             values[j] = temp_value;
    //             recurrence += 1;
    //         }
    //     }
    //     if (recurrence == 0)
    //     {
    //         return;
    //     }
    // }
    
    // merge sort
    // if (n < 2)
    // {
    //     return;
    // }
    // else
    // {
    //     // sorting left part
    //     int left_n = n / 2;
    //     int left_array[left_n];
        
    //     for (int i = 0; i < left_n; i++)
    //     {
    //         left_array[i] = values[i];
    //     }
        
    //     sort(left_array, left_n);
        
    //     // sorting right part
    //     int right_n = (n % 2 == 0) ? left_n : left_n + 1;
    //     int right_array[right_n];
        
    //     for (int i = 0; i < right_n; i++)
    //     {
    //         right_array[i] = values[i + left_n];
    //     }
        
    //     sort(right_array, right_n);
        
    //     // merge the sorted parts
    //     int left_index = 0;
    //     int right_index = 0;
        
    //     for (int i = 0; i < n; i++)
    //     {
    //         if (left_index == left_n)
    //         {
    //             values[i] = right_array[right_index];
    //             right_index += 1;
    //         }
    //         else if (right_index == right_n)
    //         {
    //             values[i] = left_array[left_index];
    //             left_index += 1;
    //         }
    //         else if (left_array[left_index] > right_array[right_index])
    //         {
    //             values[i] = right_array[right_index];
    //             right_index += 1;
    //         }
    //         else if (left_array[left_index] <= right_array[right_index])
    //         {
    //             values[i] = left_array[left_index];
    //             left_index += 1;
    //         }
    //     }
    // }
    
    return;
}

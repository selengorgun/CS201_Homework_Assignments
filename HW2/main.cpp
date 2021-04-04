#include <stdio.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string>


using namespace std;

/* Selen Görgün
 * 21802674
 */

void sortedArray(const int* arr1, const int* arr2, int*& arr3, const int size);
void sortedArray2(const int* arr1, const int* arr2, int*& arr3, const int size);

int main(){
    srand(time(NULL));
    // First algorithm's limits are 10000 to 100000
    // Second algorithm's limits are 1000000 to 10000000
    for(int size = 10000; size <= 100000; size = size + 10000){
        int* arr1 = new int[size];
        int* arr2 = new int[size];
        int* arr3 = new int[size*2];
        
        for(int a = 1; a < 4; a++){
        //Case(i): All numbers in arr1 are smaller than arr2.
        if(a == 1){
            for (int i = 0; i < size; i++) {
                int randomNumber = (rand() % (size/2));
                arr1[i] = randomNumber;
            }
            sort(arr1, arr1 + size);
            
            for (int i = 0; i < size; i++) {
                int randomNumber = (rand() % (size/2)) + size/2;
                arr2[i] = randomNumber;
            }
            sort(arr2, arr2 + size);
        }
        //Case(ii): All numbers in arr2 are smaller than arr1.
        if(a == 2){
            for (int i = 0; i < size; i++) {
                int randomNumber = (rand() % (size/2));
                arr2[i] = randomNumber;
            }
            sort(arr2, arr2 + size);
        
            for (int i = 0; i < size; i++) {
                int randomNumber = (rand() % (size/2)) + size/2;
                arr1[i] = randomNumber;
            }
            sort(arr1, arr1 + size);
        }
        //Case(iii): No ordering between the arrays.
        if(a == 3){
            for (int i = 0; i < size; i++) {
                int randomNumber = (rand() % size);
                arr1[i] = randomNumber;
            }
            sort(arr1, arr1 + size);
        
            for (int i = 0; i < size; i++) {
                int randomNumber = (rand() % size);
                arr2[i] = randomNumber;
            }
            sort(arr2, arr2 + size);
        }
        
        double duration;
        clock_t startTime = clock(); 

        sortedArray(arr1,arr2,arr3,size);
        //sortedArray(arr1,arr2,arr3,size);
    
        clock_t endTime = clock();
        duration = 1000 * double( endTime - startTime ) / CLOCKS_PER_SEC;
        
        cout << "For case " << a << endl;
        cout << "Execution for size " << size << " took " << duration << " milliseconds." << endl;
        }
        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
    }
    
	return 0;
}

// Best Case: O(n)
// Worst Case: O(n^2)
// Avarage Case: O(n^2)
void sortedArray(const int* arr1, const int* arr2, int*& arr3, const int size){    
    int currentSize = size;
    int index3 = size - 1;
    int index2 = 0;
    
    for(int i = 0; i < size; i++){
        arr3[i] = arr1[i];
    }
    
    while(index2 < size){
        while(index3 >= 0){
            if(arr2[index2] >= arr3[index3]){
                if(index3 == size - 1){
                    arr3[index3 + 1] = arr2[index2];
                }
                else{
                    for(int i = currentSize - 1; i > index3; i--){
                        arr3[i + 1] = arr3[i];
                    }
                    arr3[index3 + 1] = arr2[index2];
                }
                currentSize++;
                break;
            }
            else if(index3 == 0){
                for(int i = currentSize - 1; i >= index3; i--){
                    arr3[i + 1] = arr3[i];
                }
                arr3[index3] = arr2[index2];
                currentSize++;
                break;
            }
            index3--;
        }
        index2++;
        index3 = currentSize - 1;
    }
    
}


// Best Case: O(n)
// Worst Case: O(n)
// Avarage Case: O(n)
void sortedArray2(const int* arr1, const int* arr2, int*& sorted, const int size){
    int index1 = 0;
    int index2 = 0;
    int index3 = 0;
    
    //Adds the items from the arrays until there are no items left in one of the arrays
    while(index1 < size && index2 < size){
        if(arr1[index1] < arr2[index2]){
            sorted[index3] = arr1[index1];
            index1++;
        }
        else{
            sorted[index3] = arr2[index2];
            index2++;
        }
        index3++;
    }
    //Checks if all of the items of array 1 are added or not 
    //If not adds the rest of the items
    while(index1 < size){
        sorted[index3] = arr1[index1];
        index1++;
        index3++;
    }
    //Checks if all of the items in array 2 are added or not 
    //If not, adds the rest of the items
    while(index2 < size){
        sorted[index3] = arr2[index2];
        index2++;
        index3++;
    }
}




#ifndef MSORT_H
#define MSORT_H
#include <vector>
#include <iostream>
using namespace std;

template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp){
	msort(myArray, 0, myArray.size()-1, comp);
}

template <class T, class Comparator>
void msort(vector<T>& myArray, int start, int end, Comparator comp){
	//base case
	if(start>=end)
		return;
	int mid = (start+end)/2;
	//sort first half
	msort(myArray, start, mid, comp);
	//sort second half
	msort(myArray, mid+1, end, comp);
	//combine lists
	merge(myArray, start, end, mid, comp);

}

template <class T, class Comparator>
void merge(vector<T>& myArray, int start, int end, int mid, Comparator comp){
	int i = start, j = mid+1, k = 0;

	T *temp = new T[end-start+1];
	while (i<=mid || j<= end){

		if (i<=mid && (j>end || comp(myArray[i],myArray[j]))){
			temp[k] = myArray[i];
			i++;	
			k++;
		}
		else{
			temp[k] = myArray[j];
			j++;
			k++;
		}
	}

	for (k=0; k<end-start+1; k++){
		myArray[k+start] = temp[k];
	}

}

#endif
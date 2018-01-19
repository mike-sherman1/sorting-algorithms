//This program compares the running time of 4 different sorting algorithms at input sizes n ranging from
//1000 to 20000. The numbers to be sorted are generated using the rand() function and stored in a two dimensional
//vector of ints

#include "math.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

int PARTITION(vector<int> &, int, int);
void QUICKSORT(vector<int> &, int, int);
void INSERTION_SORT(vector<int> &, int);
void BUILD_MAX_HEAP(vector<int> &, int);
void HEAPSORT(vector<int> &, int);
void MAX_HEAPIFY(vector<int> &, int, int);
int PARENT(int);
int LEFT(int);
int RIGHT(int);

int main()
{	
	const int nStart = 1000;
	const int nFinish = 20000;
	const int delta = 1000;
	const int m = 10;
	vector<vector<int>> A;
	vector<int> B;
	clock_t start;
	vector<double> durations;
	double average = 0;
	
	//populate master array
	for (int i = 0; i < m; i++) {
		vector<int> row;
		for (int j = 0; j < nFinish; j++) {
			row.push_back(rand());
		}
		A.push_back(row);
	}

	//measurements for ALG1: insertion sort
	for (int n = nStart; n <= nFinish; n += delta) {
		for (int i = 0; i < m; i++) {
			B = A[i];
			start = clock();
			INSERTION_SORT(B, n);
			durations.push_back((((clock() - start) / (double)CLOCKS_PER_SEC))* 1000);
		}//end m for
		//sum durations
		double sum = 0;
		for (int i = 0; i < m; i++) {
			sum += durations[i];
		}
		average = (sum / (double)m);
		cout << "Average running time in ms, alg 1, with input size " << n << ": " << average << endl;
		vector<double>().swap(durations);   // clear durations
	}//end n for
	cout << "---------------------------------------------------\n";
	
	 //measurements for ALG2: heap sort
	for (int n = nStart; n <= nFinish; n += delta) {
		for (int i = 0; i < m; i++) {
			B = A[i];
			start = clock();
			HEAPSORT(B, n);
			durations.push_back((((clock() - start) / (double)CLOCKS_PER_SEC)) * 1000);
		}//end m for
		 //sum durations
		double sum = 0;
		for (int i = 0; i < m; i++) {
			sum += durations[i];
		}
		average = (sum / (double)m);
		cout << "Average running time in ms, alg 2, with input size " << n << ": " << average << endl;
		vector<double>().swap(durations);   // clear durations
	}//end n for
	cout << "---------------------------------------------------\n";
	
	//measurements for ALG3: quick sort
	for (int n = nStart; n <= nFinish; n += delta) {
		for (int i = 0; i < m; i++) {
			B = A[i];
			start = clock();
			QUICKSORT(B, 0, n-1);
			durations.push_back((((clock() - start) / (double)CLOCKS_PER_SEC)) * 1000);
		}//end m for
		 //sum durations
		double sum = 0;
		for (int i = 0; i < m; i++) {
			sum += durations[i];
		}
		average = (sum / (double)m);
		cout << "Average running time in ms, alg 3, with input size " << n << ": " << average << endl;
		vector<double>().swap(durations);   // clear durations
	}//end n for

	return 0;
}

//ALG1 working
void INSERTION_SORT(vector<int> &A, int n) {
	for (int j = 1; j < n; j++) {
		int key = A[j];
		int i = j - 1;
		while (i >= 0 && A[i] > key) {
			A[i + 1] = A[i];
			i--;
		}//end while
		A[i + 1] = key;
	}//end for
}

//ALG2 working
void HEAPSORT(vector<int> &A, int n) {
	BUILD_MAX_HEAP(A, n);
	for (int i = n - 1; i >= 0; i--) {
		swap(A[0], A[i]);
		n--;
		MAX_HEAPIFY(A, 0, n);
	}
}
void MAX_HEAPIFY(vector<int> &A, int i, int n) {
	int l = LEFT(i);
	int r = RIGHT(i);
	int largest;
	if (l < n && A[l] > A[i]) {
		largest = l;
	}
	else {
		largest = i;
	}
	if (r < n && A[r] > A[largest]) {
		largest = r;
	}
	if (largest != i) {
		swap(A[i], A[largest]);
		MAX_HEAPIFY(A, largest, n);
	}
}
void BUILD_MAX_HEAP(vector<int> &A, int n) {
	for (int i = floor(n / 2); i >= 0; i--) {
		MAX_HEAPIFY(A, i, n);
	}
}
int PARENT(int i) {
	return floor(i / 2);
}
int LEFT(int i) {
	return (2 * i) + 1;
}
int RIGHT(int i) {
	return (2 * i) + 2;
}

//ALG3 working
int PARTITION(vector<int> &A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		if (A[j] <= x) {
			i = i + 1;
			swap(A[i], A[j]);
		} // end if
	} //end for
	swap(A[i + 1], A[r]);
	return i + 1;
}
void QUICKSORT(vector<int> &A, int left, int right) {
	if (left < right) {
		int q = PARTITION(A, left, right);
		QUICKSORT(A, left, q - 1);
		QUICKSORT(A, q + 1, right);
	} //end if
}




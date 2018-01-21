//TO-DO: selection sort, user decides input sizes, error catching

//This program compares the running time of 4 different sorting algorithms at input sizes n ranging from
//1000 to 20000. The numbers to be sorted are generated using the rand() function and stored in a two dimensional
//vector of ints.

#include "math.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

string measure(vector<vector<int>> &A, vector<int> &B, void (*currentFunction)(vector<int> &, int, int), int nStart, int nFinish, int delta, int m);
int partition(vector<int> &, int, int);
void selectionSort(vector<int> &, int);
void quicksort(vector<int> &, int, int);
void insertionSort(vector<int> &, int);
void buildMaxHeap(vector<int> &, int);
void heapsort(vector<int> &, int);
void maxHeapify(vector<int> &, int, int);
int parent(int);
int left(int);
int right(int);

int main() {	
	int nStart = 1000;
	int nFinish = 20000;
	int delta = 1000;
	int m = 10;
	vector<vector<int>> master;
	vector<int> currentSim;
	string result = "";
	bool exit = false;

	//main menu
	cout << "Welcome to the sorting algorithms tester v1.1.\nTo begin, let's set up the parameters of the simulations.\n\n";
	cout << "Please enter the lower limit of the input size, or just press enter for default value (1000): ";
	//if no input entered, keep default 
	cin >> nStart;
	
	while (!exit) {
		 
	}
	

	return 0;
}

//populate master array
void fillArray(vector<vector<int>> &master, int m, int nFinish) {
	for (int i = 0; i < m; i++) {
		vector<int> row;
		for (int j = 0; j < nFinish; j++) {
			row.push_back(rand());
		}
		master.push_back(row);
	}
}

//measure
string measure(vector<vector<int>> &A, vector<int> &B, void (*currentFunction)(vector<int> &, int, int), int nStart, int nFinish, int delta, int m) {
	vector<double> durations;
	clock_t start;
	
	for (int n = nStart; n <= nFinish; n += delta) {
		string result = "";
		for (int i = 0; i < m; i++) {
			B = A[i];
			int temp = n;
			if (currentFunction == quicksort) {
				n = 0;
			}
			start = clock();
			currentFunction(B, n, n-1);
			durations.push_back((((clock() - start) / (double)CLOCKS_PER_SEC)) * 1000);
			n = temp;
		}
		double sum = 0;
		for (int i = 0; i < m; i++) {
			sum += durations[i];
		}
		double average = (sum / (double)m);
		result += "Average running time in ms, alg 2, with input size " + to_string(n) + ": " + to_string(average) + "\n";
		vector<double>().swap(durations);   // clear durations
	}//end n for
	result += "---------------------------------------------------\n";
	return result;
}

//insertion sort
void insertionSort(vector<int> &A, int n, int trash) {
	trash.clear();
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

//selection sort (TO-DO)
void selectionSort(vector<int> &A, int n, int trash) {
	trash.clear();
	for (int i = 0; i <= n - 2; i++) //i in 0 to n - 2
	{
		int maxIndex = i;
		for (int j = i + 1; j <= n - 1; j++)
		{
			if (A[j] > A[maxIndex])
			{
				maxIndex = j;
			}//end if
			swap(A[i], A[maxIndex]);
		}//end j for
	}// end i for
}

//heap sort
void heapsort(vector<int> &A, int n, int trash) {
	trash.clear();
	buildMaxHeap(A, n);
	for (int i = n - 1; i >= 0; i--) {
		swap(A[0], A[i]);
		n--;
		maxHeapify(A, 0, n);
	}
}
void maxHeapify(vector<int> &A, int i, int n) {
	int l = left(i);
	int r = right(i);
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
		maxHeapify(A, largest, n);
	}
}
void buildMaxHeap(vector<int> &A, int n) {
	for (int i = floor(n / 2); i >= 0; i--) {
		maxHeapify(A, i, n);
	}
}
int parent(int i) {
	return floor(i / 2);
}
int left(int i) {
	return (2 * i) + 1;
}
int right(int i) {
	return (2 * i) + 2;
}

//quick sort
void quicksort(vector<int> &A, int left, int right) {
	if (left < right) {
		int q = partition(A, left, right);
		quicksort(A, left, q - 1);
		quicksort(A, q + 1, right);
	} //end if
}
int partition(vector<int> &A, int p, int r) {
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





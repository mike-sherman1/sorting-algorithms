//TODO: fix double enter on parameter inputs, error catching, refactoring and commenting, README

/*
This program compares the running time of 4 different sorting algorithms at input sizes n ranging, by default,
from 1000 to 20000. User can change the parameters, including the input size range, the increment between input
sizes, and the number of simulations to be ran at each input size. The numbers to be sorted are generated 
using the rand() function and stored in a two dimensional vector of ints.
*/

#include "math.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

//function prototypes
void parameterMenu(int &, int &, int &, int &);
vector<vector<int>> fillArray(int, int);
void measure(vector<vector<int>> &, string (*currentFunction)(vector<int> &, int, int), int, int, int, int);
string insertionSort(vector<int> &, int, int);
string selectionSort(vector<int> &, int, int);
string heapsort(vector<int> &, int, int);
void maxHeapify(vector<int> &, int, int);
void buildMaxHeap(vector<int> &, int);
int parent(int);
int left(int);
int right(int);
string quicksort(vector<int> &, int, int);
int partition(vector<int> &, int, int);

int main() {	
	//initialize variables
	int nStart = 1000;
	int nFinish = 20000;
	int delta = 1000;
	int m = 10;

	//initialize program parameters
	parameterMenu(nStart, nFinish, delta, m);
	vector<vector<int>> master = fillArray(m, nFinish);
	system("pause");
	
	//main menu
	bool exit = false;
	while (!exit) {
		system("cls");
		cout << "******************************\n";
		cout << "Sorting Algorithms Tester v1.3\n";
		cout << "******************************\n\n";
		cout << "Select an algorithm to test\n\n";
		cout << "1: Insertion sort\n";
		cout << "2: Selection sort\n";
		cout << "3: Heapsort\n";
		cout << "4: Quicksort\n";
		cout << "5: View or edit parameters\n";
		cout << "6: Exit\n\n";	
		
		int choice = 0;
		cout << "Enter choice: ";
		cin >> choice;
		cin.ignore();
		switch (choice) {
			case 1:
				cout << endl;
				measure(master, insertionSort, nStart, nFinish, delta, m);
				cout << endl;
				system("pause");
				break;
			case 2:
				cout << endl;
				measure(master, selectionSort, nStart, nFinish, delta, m);
				cout << endl;
				system("pause");
				break;
			case 3:
				cout << endl;
				measure(master, heapsort, nStart, nFinish, delta, m);
				cout << endl;
				system("pause");
				break;
			case 4:
				cout << endl;
				measure(master, quicksort, nStart, nFinish, delta, m);
				cout << endl;
				system("pause");
				break;
			case 5:
				parameterMenu(nStart, nFinish, delta, m);
				system("pause");
				master = fillArray(m, nFinish);
				break;
			case 6:
				exit = true;
				break;
			default:
				cout << "Invalid choice. Please try again.\n";
		}
	}//end main menu while 
	//exit program
	return 0;
}

void parameterMenu(int &nStart, int &nFinish, int &delta, int &m) {
	string input = "";
	system("cls");
	cout << "****************************************************************************\n";
	cout << "Welcome to the Sorting Algorithms Tester v1.3\n";
	cout << "Current parameters: nStart = " << nStart << ", nFinish = " << nFinish << ", delta = " << delta << ", and m = " << m << "\n";
	cout << "****************************************************************************\n\n";
	
	cout << "Please enter the lower limit of the input size, or just press enter for original value (" << nStart << "): ";
	getline(cin, input);
	stringstream a(input);
	if (a >> nStart) {
	} 
	cin.ignore();
	
	cout << "Please enter the upper limit of the input size, or just press enter for original value (" << nFinish << "): ";
	getline(cin, input);
	stringstream b(input);
	if (b >> nFinish) {
	} 
	cin.ignore();
	
	cout << "Please enter delta (how much you want to increment the input size by), or just press enter for original value (" << delta << "): ";
	getline(cin, input);
	stringstream c(input);
	if (c >> delta) {
	} 
	cin.ignore();
	
	cout << "Please enter m (the number of simulations to be ran at each input size), or just press enter for original value (" << m << "): ";
	getline(cin, input);
	stringstream d(input);
	if (d >> m) {
	} 
	cin.ignore();

	cout << "All parameters have been set! Going to main menu.\n\n";
}

//populate master array with random numbers
vector<vector<int>> fillArray(int m, int nFinish) {
	vector<vector<int>> master;
	for (int i = 0; i < m; i++) {
		vector<int> row;
		for (int j = 0; j < nFinish; j++) {
			row.push_back(rand());
		}
		master.push_back(row);
	}
	return master;
}

//measure
void measure(vector<vector<int>> &A, string (*currentFunction)(vector<int> &, int, int), int nStart, int nFinish, int delta, int m) {	
	for (int n = nStart; n <= nFinish; n += delta) {
		string func = "";
		vector<double> durations;
		for (int i = 0; i < m; i++) {
			vector<int> B = A[i];
			int temp = n;
			if ((*currentFunction) == quicksort) {
				n = 0;
			}
			clock_t start;
			start = clock();
			func = currentFunction(B, n, temp-1);
			durations.push_back((((clock() - start) / (double)CLOCKS_PER_SEC)) * 1000);
			n = temp;
		}
		double sum = 0;
		for (int i = 0; i < m; i++) {
			sum += durations[i];
		}
		double average = (sum / (double)m);
		cout << "Average running time in milliseconds, " << func << ", with input size " << n << ": " << average << "\n";
		vector<double>().swap(durations);   //clear durations
	}//end n for
}

//insertion sort
string insertionSort(vector<int> &A, int n, int trash) {
	for (int j = 1; j < n; j++) {
		int key = A[j];
		int i = j - 1;
		while (i >= 0 && A[i] > key) {
			A[i + 1] = A[i];
			i--;
		}//end while
		A[i + 1] = key;
	}//end for
	return __func__;
}

//selection sort
string selectionSort(vector<int> &A, int n, int trash) {
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
	return __func__;
}

//heapsort
string heapsort(vector<int> &A, int n, int trash) {
	buildMaxHeap(A, n);
	for (int i = n - 1; i >= 0; i--) {
		swap(A[0], A[i]);
		n--;
		maxHeapify(A, 0, n);
	}
	return __func__;
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

//quicksort
string quicksort(vector<int> &A, int left, int right) {
	if (left < right) {
		int q = partition(A, left, right);
		quicksort(A, left, q - 1);
		quicksort(A, q + 1, right);
	} //end if
	return __func__;
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





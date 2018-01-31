//TODO: output function name, parameter editing, error catching

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
#include <sstream>

using namespace std;

void measure(vector<vector<int>> &, vector<int> &, void (*currentFunction)(vector<int> &, int, int), int, int, int, int);
int partition(vector<int> &, int, int);
void selectionSort(vector<int> &, int, int);
void quicksort(vector<int> &, int, int);
void insertionSort(vector<int> &, int, int);
void buildMaxHeap(vector<int> &, int);
void heapsort(vector<int> &, int, int);
void maxHeapify(vector<int> &, int, int);
int parent(int);
int left(int);
int right(int);
void fillArray(vector<vector<int>> &, int, int);
void parameterMenu(int &, int &, int &, int &);

int main() {	
	int nStart = 1000;
	int nFinish = 20000;
	int delta = 1000;
	int m = 10;
	vector<vector<int>> master;
	vector<int> currentSim;
	bool exit = false;

	parameterMenu(nStart, nFinish, delta, m);
	fillArray(master, m, nFinish);
	
	//main menu
	while (!exit) {
		system("cls");
		cout << "Sorting Algorithms Tester v1.1\n";
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
		
		string output = "";
		switch (choice) {
			case 1:
				cout << endl;
				measure(master, currentSim, insertionSort, nStart, nFinish, delta, m);
				cout << endl;
				system("pause");
				break;
			case 2:
				cout << endl;
				measure(master, currentSim, selectionSort, nStart, nFinish, delta, m);
				cout << endl;
				system("pause");
				break;
			case 3:
				cout << endl;
				measure(master, currentSim, heapsort, nStart, nFinish, delta, m);
				cout << endl;
				system("pause");
				break;
			case 4:
				cout << endl;
				measure(master, currentSim, quicksort, nStart, nFinish, delta, m);
				cout << endl;
				system("pause");
				break;
			case 5:
				break;
			case 6:
				exit = true;
				break;
			default:
				cout << "Invalid choice. Please try again.\n";
		}
	}//end main menu while 
	
	
	return 0;
}

void parameterMenu(int &nStart, int &nFinish, int &delta, int &m) {
	string input = "";
	system("cls");
	cout << "Welcome to the Sorting Algorithms Tester v1.1.\n";
	cout << "To begin, let's set up the parameters of the simulation.\n";
	cout << "********************************************************\n\n";
	cout << "Please enter the lower limit of the input sizes, or just press enter for default value (1000): ";
	getline(cin, input);
	stringstream a(input);
	if (a >> nStart) {
	} 
	else {
		nStart = 1000;
	}
	
	cout << "Please enter the upper limit of the input sizes, or just press enter for default value (20000): ";
	cin.clear();
	getline(cin, input);
	stringstream b(input);
	if (b >> nFinish) {
	} 
	else {
		nFinish = 20000;
	}
	
	cout << "Please enter delta (how much you want to increment the input sizes by), or just press enter for default value (1000): ";
	getline(cin, input);
	stringstream c(input);
	if (c >> delta) {
	} 
	else {
		delta = 1000;
	}
	
	cout << "Please enter m (the number of simulations to be ran at each input size), or just press enter for default value (10): ";
	getline(cin, input);
	stringstream d(input);
	if (d >> m) {
	} 
	else {
		m = 10;
	}

	cout << "\nAll parameters have been set! Going to main menu.\n";
	system("pause");
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
void measure(vector<vector<int>> &A, vector<int> &B, void (*currentFunction)(vector<int> &, int, int), int nStart, int nFinish, int delta, int m) {
	vector<double> durations;
	clock_t start;
	
	for (int n = nStart; n <= nFinish; n += delta) {
		for (int i = 0; i < m; i++) {
			B = A[i];
			int temp = n;
			if ((*currentFunction) == quicksort) {
				n = 0;
			}
			start = clock();
			currentFunction(B, n, temp-1);
			durations.push_back((((clock() - start) / (double)CLOCKS_PER_SEC)) * 1000);
			n = temp;
		}
		double sum = 0;
		for (int i = 0; i < m; i++) {
			sum += durations[i];
		}
		double average = (sum / (double)m);
		cout << "Average running time in ms, function name, with input size " << n << ": " << average << "\n";
		vector<double>().swap(durations);   // clear durations
	}//end n for
}

//insertion sort
void insertionSort(vector<int> &A, int n, int trash) {
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

//selection sort
void selectionSort(vector<int> &A, int n, int trash) {
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

//heapsort
void heapsort(vector<int> &A, int n, int trash) {
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

//quicksort
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





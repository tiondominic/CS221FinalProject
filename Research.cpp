#include <iostream>
#include <vector>

using namespace std;

/*
TODO 
- Add Binary Search for early termination
- Add Parallel computing for the merge steps
- Finish the merge sort function
*/

void merge(vector<int>& arr){
	int size = arr.size();

	for(int i=0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << "\n";
}

void mergesort(vector<int>& arr)
{
	
	
	int size = arr.size();
	int mid = size / 2;
	
	cout << "Left half:\n";
	vector<int> leftHalf(arr.begin(), arr.begin() + mid);
	merge(leftHalf);
	cout << "Rigt half:\n";
    vector<int> rightHalf(arr.begin() + mid, arr.end());
	merge(rightHalf);
	
}


int main(){
	
	
	vector<int> Numbers = {41, 52, 6, 43, 49, 59, 38, 71, 34, 76, 40, 13, 67, 24, 54, 50, 65, 25, 85, 19};
	
	mergesort(Numbers);
	
	return 0;
}

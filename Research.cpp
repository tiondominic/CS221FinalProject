#include <iostream>
#include <vector>

using namespace std;

/*
TODO 
- Add Binary Search for early termination | High Priority
- Add Parallel computing for the merge steps | Medium Priority
- Finish the merge sort function *Done*
- Add a file reading system to calculate data | Low Priority
- Add output file as txt after finish sorting | Medium Priority
- Add timer to benchmark code | Low Priority
*/

vector<int> merge(vector<int> Left, vector<int> Right){
	vector<int> result;
	int sizeL = Left.size();
	int sizeR = Right.size();
	int i = 0, j = 0;

	while(i < sizeL && j < sizeR){
		if (Left[i] <= Right[j])
            result.push_back(Left[i++]);
        else
            result.push_back(Right[j++]);

	}

	while (i < sizeL)
        result.push_back(Left[i++]);
    while (j < sizeR)
        result.push_back(Right[j++]);


	return result;
}
vector<int> mergesort(vector<int>& arr)
{
	
	
	int size = arr.size();

	if(size <= 1){
		return arr;
	}
	
	int mid = size / 2;
	
	vector<int> leftHalf(arr.begin(), arr.begin() + mid);
	vector<int> rightHalf(arr.begin() + mid, arr.end());

	leftHalf = mergesort(leftHalf);
	rightHalf = mergesort(rightHalf); 


	return merge(leftHalf, rightHalf);
}


int main(){
	
	
	vector<int> Numbers = {41, 52, 6, 43, 49, 59, 38, 71, 34, 76, 40, 13, 67, 24, 54, 50, 65, 25, 85, 19};
	
	Numbers = mergesort(Numbers);

	for(int num: Numbers){
		cout << num << " ";
	}
	
	return 0;
}

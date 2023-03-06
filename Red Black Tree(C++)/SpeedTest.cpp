#include <cstdlib>
#include <ctime>
#include <random>
#include "RedBlackTree.h"

using namespace std;


int main(){

	// create a simulated 3.7 million ID number system.
	const int N = 3700000;

	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();
	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Collected " << rbt.Size() << " ID numbers in " << (duration) << " seconds." << endl;


	
	bool removed = false;
	int val;
	int i;
	for(i=0;i<6;i++){
	removed = false;
	while(!removed){
		val = rand() % 3700000;
		if(rbt.Contains(val)){
			clock_t start = clock();
			rbt.Remove(val);
			clock_t stop = clock();
			double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
			cout << "Removed in " << duration<< "seconds." <<endl;
			removed = true;
			}
	}
	}
	int j;
	for(j=0;j<6;j++){
	bool added = false;
	while(!added){
		val = rand() % 3700000;
		if(!rbt.Contains(val)){
			clock_t start = clock();
			rbt.Insert(val);
			clock_t stop = clock();
			double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
			cout << "inserted in " << duration<< "seconds." <<endl;
			added = true;
			}
	}
	}
	

	

	return 0;
}
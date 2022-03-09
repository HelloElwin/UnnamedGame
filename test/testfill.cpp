#include "block_fill.h"
#include <iostream>
using namespace std;
int main() {
	int content[5][10];
	int overall;
	cout<<"please type the overall_property: ";
	cin>>overall;
	fill(overall,(int*)content);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++)
			cout<<content[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}

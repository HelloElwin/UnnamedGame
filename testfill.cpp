#include "block_fill.h"
#include <iostream>
using namespace std;
int main() {
	int overall = 121;
	int content[4][10];
	fill(overall,(int*)content);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++)
			cout<<content[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}

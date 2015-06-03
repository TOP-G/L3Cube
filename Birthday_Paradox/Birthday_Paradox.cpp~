/*
Here we are calculating the probability that atleast two people in a room share their birthdays!!!

*/
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int main(){
	long double prob=1;
	int people;
	cout<<"Enter number of people:";
	cin>>people;
	for(int i=1;i<people;i++){
		prob = prob * ( (365.0 - i) / 365.0);
	}
	printf("Probability: %.30Lf%s\n", (100 - prob*100), "%");
}


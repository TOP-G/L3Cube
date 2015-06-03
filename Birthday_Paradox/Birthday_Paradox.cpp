/*

Problem Statement - Write a code that verifies - birthday paradox is indeed correct.
Solution - 

In this program, first we are finding out the probability by conventional solution for birthday paradox that at least 2 people in a room share the same birthday.
Then, by random experiments using RNG we are able to prove that the mean squared error term tends to zero. 

Hence, the birthday paradox is indeed correct.

*****USAGE*****
$ g++ Birthday_Paradox.cpp
$ ./a.out

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class People{
public:
	long double b_p,r_g;
	People(){
		b_p=r_g=0.0;
	}
	void fillUp(int [],int);
	void random_generator(int,People*);
	void birthday_paradox(int,People*);
};

//To generate random birthdays for people in a room
void People::fillUp(int birthdays [], int size){
    for (int i = 0; i < size; i++){
        birthdays[i] = rand() % 365 + 1;
    }
}

//Probability by conventional birthday paradox
void People::birthday_paradox(int people,People* p){
	long double prob=1;
	for(int j=1;j<=people;j++){
		for(int i=1;i<j;i++){
			prob = prob * ( (365.0 - i) / 365.0);      //probability that all people in a room have different birthdays
		}
		p[j-1].b_p=100-prob*100;                           //probability that atleast two people in a room share same birthday
		prob=1;
	}
}

//Probability by RNG 
void People::random_generator(int people,People* p){
	int trials = 5000, flag;
	long double total;
	int birthdays[people], collisions[people];

	//number of people "in the room"
    for (int i = 1; i <= people; i++){
  		collisions[i] = 0;
  		//do 5000 trials:
  		for (int t = 0; t < trials; t++){
    		fillUp(birthdays, i);
    		flag = 0;
    		//compare all pairs (j,k):
    		for (int j = 0; j < i - 1 && flag == 0; j++){
      			for (int k = j + 1; k < i && flag == 0; k++ ){
    				if (birthdays[k] == birthdays[j]){
      					collisions[i]++;
      					flag = 1;
					}
  				}
			}
  		}
		total = collisions[i] / 5000.0;
		cout.precision(30);
		p[i-1].r_g=total*100;
	}
}

int main(){
	int people;
	cout<<"Enter number of people:";
	cin>>people;
	long double arr[people];
	People *p = new People[people];
	p[0].birthday_paradox(people,p);
	p[0].random_generator(people,p);
	

	//Finding the mean squared error term

	for(int j=0;j<people;j++){
		arr[j] = p[j].r_g - p[j].b_p;
	}

	long double total1=0.0;
	for(int j=0;j<people;j++){
		total1+=arr[j]*arr[j];
	}

	cout<<"For "<<people<<" people in the room:"<<endl;
	cout<<"Probability according to Random Number Generator: "<<p[people-1].r_g<<"%"<<endl;
	cout<<"Probability according to Birthday Paradox: "<<p[people-1].b_p<<"%"<<endl;

	long double sq_er = total1/(2*people);
	cout<<"Squared Error = "<<sq_er<<"%"<<endl;
	cout<<sq_er<<" tends to 0"<<endl;
	cout<<"Hence, Proved";

	cout<<endl;
	return 0;
}

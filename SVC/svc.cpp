/*

Problem Statement - Create a simple version control (svc) program called "svc"
Solution - 

Here, this program helps to append or/and delete particular line from text file and create its versions accordingly.
 
*****USAGE*****
[1] To Commit file 
$ g++ svc.cpp -o svc
$ ./svc <filename.txt>

eg: ./svc test.txt

[2] To display a particular version
$ g++ svc.cpp -o svc
$ ./svc <version_number>

eg: ./svc 3

*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>

using namespace std;

int noOfVersions = -1;

//Function to commit a file
void commit(string filename){
	string filename2,line;
	ostringstream oss;
	std::ifstream infile4;
	std::ofstream outfile4; 
	oss.str(std::string());
	oss.clear();
	noOfVersions++;
	oss << "version" << noOfVersions;
	filename2 = oss.str() + ".txt";

	infile4.open(filename.c_str(),ios::binary | ios::in);
	outfile4.open(filename2.c_str(),ios::binary | ios::out);

	cout<<"Committed.."<<endl;
	while(!infile4.eof()){
		std::getline(infile4,line);
		outfile4 << line <<endl;
	}

	infile4.close();
	outfile4.close();
}

int main(int argc, char *argv[]){

	string str1,fname= "version",filename2,line,str;
	int ch,i,j,noOfLines=0,version_no;

	string filename = argv[1];

	ostringstream oss;
	ifstream infile4;
	ofstream outfile4;
	
	//To append and/or delete
	if(!atoi(filename.c_str()) && filename != "0"){
		do{
			cout<< "\n1.Append 2.Delete 3.Exit\nEnter your choice: ";
			cin >> ch;
			cin.ignore();
			switch(ch){
				case 1://Append to a file
					do{
						cout<<"Enter data upto 9 characters:";
						std::getline(cin,str1);
					}while(str1.length() > 9);
					outfile4.open(filename.c_str(),ios::binary | ios::app | ios::out);		
					outfile4<< str1 <<endl;
					outfile4.close();
					commit(filename);
					cout<<"Line has been Appended & Committed.."<<endl;
					break;

				case 2://Delete from a file 
					int lineno;
					infile4.open(filename.c_str(),ios::in);
					cout<<"Enter line number to delete : ";
					cin>>lineno;					
					i=0;
					oss.str(std::string());
					oss.clear();
					while(std::getline(infile4,line)){
						if(i == lineno-1){
							i++;
						}else{
							oss << line << endl;
							i++;
						}
					}
					infile4.close();			
					outfile4.open(filename.c_str(),ios::out);		
					outfile4<<oss.str();
					outfile4.close();
					commit(filename);
					cout<<"Line has been Deleted & Committed.."<<endl;					
					break;

				case 3://Exit 
					cout<<"Exiting..!!\n";
				break;

				default:
				cout<<"Invalid Choice!!!";
				break;
			}

		}while(ch<3);		

	}	
	else{
		//To display a particular version of a file
		version_no=atoi(argv[1]);
		oss << fname << version_no;
		filename2 = oss.str() + ".txt";
		infile4.open(filename2.c_str(),ios::binary | ios::in);

		while(std::getline(infile4,line)){
			cout << line << endl;
		}
		infile4.close();

	}
	return 0;
}

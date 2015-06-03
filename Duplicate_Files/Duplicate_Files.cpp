#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class node{
public:
	string filename,timestamp,filesize,filepath;
	node *next;
	node(){
		filename = "";
		timestamp = "";
		filesize = "";
		filepath = "";
		next = NULL;
	}
};

int main(){

    	string command = "find * -printf '%CY%Cm%Cd%CH%CM\t%s\t%f\t%p\n' > filenames.txt",command2;
    	system(command.c_str());
	
	int i=0,flag = 0;
	node *a,*b,*temp,*start=NULL,*end=NULL;
	string fname,fsize,ftime,fpath,delimeter1="\t",temp3="",temp4="",line;
        size_t found,pos = 0;
	char choice;
	ifstream infile("filenames.txt");

	if(!infile){
		cout<<"Error in opening file"<<endl;
	}else{
		while(getline(infile,line)){
			pos = line.find(delimeter1);
			ftime = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length());		

			pos = line.find(delimeter1);
			fsize = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length());		

			pos = line.find(delimeter1);
			fname = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length());		

			pos = line.find(delimeter1);
			fpath = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length());		

			if(i==0){
				a=new node();
				a->filename=fname;
				a->filepath=fpath;
				a->filesize=fsize;
				a->timestamp=ftime;
				start=a;
				end=a;
			}else{
				temp = start;
				while(temp != NULL){
					if(temp->filename == fname){
						flag=1;
						cout <<"Current File Path: "<< fpath <<endl;
						cout << fname <<" already exists in " << temp->filepath << "\nDou you want to remove this?? Y-Yes N-No\nYour Choice:"<< endl;
						cin >> choice;
						if(choice == 'Y' || choice == 'y'){
							command2 = "rm " + fpath;
							system(command2.c_str());
							cout << "File deleted successfully..";
						}
						break;
					}else{
						temp = temp->next;
					}
				}
				if(flag==0){
					b=new node();
					b->filename=fname;
					b->filesize=fsize;
					b->timestamp=ftime;
					b->filepath=fpath;
					end->next=b;
					end=b;
				}
				flag = 0;
			}	
			i++;
		}
	}
}

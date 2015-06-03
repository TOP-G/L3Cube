/*
Problem Statement - Making sense out of HTTP log file 
Solution -
In this program, we are sorting the weblog file and presenting it accordingly.

*****USAGE*****
$ g++ http_log.cpp
$ ./a.out

*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

//Struct for various log fields
struct Log{
	string ipaddr,date,method,web,ver,status,size,referer,browser;	
};

//Class for creating linked list
class node{
	public:
	int cnt;
	string browser,name;
	node *right;
	node(){
		cnt=0;
		name="";
		right=NULL;

	}
};

int main(){
	struct Log l1[2800];
	string delimeter1=" ",delimeter2="[",delimeter3="]",delimeter4="\"",delimeter5 = ".";  
	size_t pos=0;
	node *a,*b,*temp,*start=NULL,*end=NULL;
	ifstream infile("weblog.txt");
	string line, str,temp2;
	int noOfLines = 0, i=0,j,k,temp3,flag=0,total = 0, getCount = 0, postCount = 0, status200 = 0, status404 = 0, http11 = 0, http10 = 0;
	int ipclass[5];
	if(!infile){
		cout<<"Error in opening file"<<endl;
	}else{
		while(getline(infile,line)){    
			//Host IP       
			pos = line.find(delimeter5);
			temp2 = line.substr(0,pos);
			int temp3 = atoi(temp2.c_str());
			if(temp3 >= 240 && temp3 <= 255 ) ipclass[0]++;             
			else if(temp3 >= 224 && temp3 <= 239 ) ipclass[1]++;
			else if(temp3 >= 192 && temp3 <= 223 ) ipclass[2]++;
			else if(temp3 >= 128 && temp3 <= 191 ) ipclass[3]++;
			else if(temp3 >= 1 && temp3 <= 126 ) ipclass[4]++;

			pos = line.find(delimeter1);
			l1[i].ipaddr = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length()+3);		

			//Date and time
			pos = line.find(delimeter3);
			l1[i].date = line.substr(line.find(delimeter2), pos);
			line.erase(0, pos + delimeter3.length()+2);

			//Http method
			pos = line.find(delimeter1);
			l1[i].method = line.substr(0, pos);
			if(l1[i].method == "GET"){
				getCount += 1;
			}else{
				postCount += 1;
			}
			line.erase(0, pos + delimeter1.length());

			//Website requested by user
			pos = line.find(delimeter1);
			l1[i].web = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length());

			if(i==0){
				a=new node();
				a->name=l1[i].web;
				a->cnt=1;
				start=a;
				total+=1;
				end=a;
			}else{
				temp = start;
				while(temp != NULL){
					if(temp->name == l1[i].web){
						temp->cnt = temp->cnt + 1;
						flag=1;
						break;
					}else{
						temp = temp->right;
					}
				}
				if(flag==0){
					b=new node();
					b->name=l1[i].web;
					b->cnt=1;
					end->right=b;
					end=b;
					total+=1;
				}
				flag = 0;
			}	

			//Http version
			pos = line.find(delimeter4);
			l1[i].ver = line.substr(0, pos);
			if(l1[i].ver == "HTTP/1.1"){
				http11++;
			}else if(l1[i].ver == "HTTP/1.0"){
				http10++;
			}
			line.erase(0, pos + delimeter4.length()+1);

			//Http status code
			pos = line.find(delimeter1);
			l1[i].status = line.substr(0, pos);
			if(l1[i].status == "200"){
				status200++;
			}else if(l1[i].status == "404"){
				status404++;
			}
			line.erase(0, pos + delimeter1.length());

			//Size of response-object received by host
			pos = line.find(delimeter1);
			l1[i].size = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length()+1);			
			
			//Referer
			pos = line.find(delimeter4);
			l1[i].referer = line.substr(0, pos);
			line.erase(0, pos + delimeter4.length()+2);

			//User-agent/browser
			pos = line.find(delimeter4);
			l1[i].browser = line.substr(0, pos);
			line.erase(0, pos + delimeter4.length()+1);

			i++;
		}
			
	}

	noOfLines = i;

	cout<<"\nTotal Different Website Links:"<<total<<endl;
	cout<<"-------------------------------------------------------------------------"<<endl;

	//POPULAR LINKS
	cout<<"Most Popular Links getting more than 30 hits:\n";
	for(temp=start;temp->right!=NULL;temp=temp->right){
		if(temp->cnt > 30){
			cout<<"Link:"<<temp->name<<" got "<<temp->cnt<<" hits "<<endl;			
		}
	}
	cout<<"-------------------------------------------------------------------------"<<endl;

	//Method
	cout<<"HTTP methods -"<<endl;
	cout<<"Total GET Requests: "<<getCount<<endl;
	cout<<"Total POST Requests: "<<postCount<<endl;
	cout<<"-------------------------------------------------------------------------"<<endl;

	//Status Count
	cout<<"HTTP status code -"<<endl;
	cout<<"HTTP_OK: "<<status200<<endl;
	cout<<"HTTP_PAGE_NOT_FOUND: "<<status404<<endl;
	cout<<"Unsuccessful Requests: "<<noOfLines - status200<<endl;
	cout<<"-------------------------------------------------------------------------"<<endl;

	//HTTP Version
	cout<<"HTTP version -"<<endl;
	cout<<"HTTP/1.1: "<<http11<<endl;
	cout<<"HTTP/1.0: "<<http10<<endl;
	cout<<"-------------------------------------------------------------------------"<<endl;

	//IP Class
	cout<<"IP classification of remote host -"<<endl;
	cout<<"Class A: "<<ipclass[4]<<endl;
	cout<<"Class B: "<<ipclass[3]<<endl;
	cout<<"Class C: "<<ipclass[2]<<endl;
	cout<<"Class D: "<<ipclass[1]<<endl;
	cout<<"Class E: "<<ipclass[0]<<endl;

	cout<<"-------------------------------------------------------------------------"<<endl;

	//Date

	cout<<"Log file start Date:"<<l1[0].date<<endl;
	cout<<"Log file last Date:"<<l1[noOfLines-1].date<<endl;
	cout<<"-------------------------------------------------------------------------"<<endl;

	return 0;
}

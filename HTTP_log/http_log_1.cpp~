#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

struct Log
{
	std::string ipaddr;
	std::string date;	
	std::string method;
	std::string web;
	std::string ver;
	std::string status;
	std::string size;
	std::string referer;
	std::string browser;	
};

class node
{
	public:
	int cnt;
	string name;
	node *right;
	node()
	{
		cnt=0;
		name="";
		right=NULL;
	}
};


int main()
{

	std::string delimeter1=" ";
	std::string delimeter2="[";
	std::string delimeter3="]";
	std::string delimeter4="\"";
	size_t pos=0;

	struct Log l1[3000];

	node *a,*temp,*start=NULL,*end=NULL;
	
	std::ifstream infile("weblog.txt");
	std::string line, str;
	int i=0,j,k,flag=0,total=0;
	if(!infile)
	{
		cout<<"Error in opening file"<<endl;
	}
	else
	{
		while(std::getline(infile,line))
		{
			pos = line.find(delimeter1);
			l1[i].ipaddr = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length()+3);		

			pos = line.find(delimeter3);
			l1[i].date = line.substr(line.find(delimeter2), pos);
			line.erase(0, pos + delimeter3.length()+2);

			pos = line.find(delimeter1);
			l1[i].method = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length());



			pos = line.find(delimeter1);
			l1[i].web = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length());

			
			if(i==0)
			{
				a=new node();
				a->name=l1[i].web;
				a->cnt=1;
				start=a;
				end=a;
				total=1;
			}
			else
			{
				while(temp!=NULL)
				{
					if(temp->name == l1[i].web)
					{
						temp->cnt++;
						flag=1;
						total++;
						break;
					}
					temp=temp->right;
					
				}
				if(flag==0)
				{
					a=new node();
					a->name=l1[i].web;
					a->cnt=1;
					end->right=a;
					end=a;
					total++;
				}
				flag=0;
				
			}	


			pos = line.find(delimeter4);
			l1[i].ver = line.substr(0, pos);
			line.erase(0, pos + delimeter4.length()+1);

			pos = line.find(delimeter1);
			l1[i].status = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length());

			pos = line.find(delimeter1);
			l1[i].size = line.substr(0, pos);
			line.erase(0, pos + delimeter1.length()+1);
			cout<<line<<endl;			
			
			pos = line.find(delimeter4);
			l1[i].referer = line.substr(0, pos);
			line.erase(0, pos + delimeter4.length()+2);

			pos = line.find(delimeter4);
			l1[i].browser = line.substr(0, pos);
			line.erase(0, pos + delimeter4.length()+1);


			i++;
		}
			
	}
	for(j=0;j<i;j++)
	{
		cout<<j+1<<endl;
		cout<<"\nIp address is: "<<l1[j].ipaddr;
		cout<<"\nDate is: "<<l1[j].date;
		cout<<"\nMethod is: "<<l1[j].method;
		cout<<"\nWebsite is: "<<l1[j].web;
		cout<<"\nHttp version is: "<<l1[j].ver;
		cout<<"\nHttp status is: "<<l1[j].status;
		cout<<"\nSize is: "<<l1[j].size;
		cout<<"\nReferer is: "<<l1[j].referer;
		cout<<"\nBrowser is: "<<l1[j].browser;
		cout<<endl;
		cout<<"Total "<<total<<endl;
	}
	for(temp=start;temp->right!=NULL;temp=temp->right)
	{
		cout<<"Website: "<<temp->name<<" got "<<temp->cnt<<" hits "<<endl;			
	}
		
	return 0;
}

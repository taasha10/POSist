#include<bits/stdc++.h>
using namespace std;

struct Owner{
	string name;
	int ID;
	float value;
	string password;	
};
struct Node{
	time_t timestamp;
	Owner *owner;
	int nodeNumber;
	int nodeId;
	Node *refernceNodeId;
	vector<int> childNodeId;
	vector<Node*> refChildNodeId;
	
};
Node *getNode(int num,Owner *owner){
	Node *np=new Node;
	np->timestamp=time(0);
	np->Owner=owner;
	np->nodeNumber=num;
	np->nodeId=(num);
	vector<Node*> x;
	np->refChildNodeId=x;
	np->refernceNodeId=NULL;
	vector<int> y;
	np->childNodeId=y;
	return np;
}

void create_child(Node *child,int id,vector<Node*> &x){
	for(int i=0;i<x.size();i++){
		if(x[i]->nodeId==id){
			x[i]->refChildNodeId.push_back(child);
			x[i]->childNodeId.push_back(child->nodeId);
			child->refernceNodeId=x[i];
			break;
		}	
	}
}
//encryption
string encryption(string data,int n){
	string e=data;
	int len = e.length();
	for(int i=0;i<len;i++){
		e[i]+=n+10;
	}
	return e;
}
//decryption
string decryption(string data,int n){
	string d=data;
	int len = d.length();
	for(int i=0;i<len;i++){
		d[i]-=n-10;
	}
	return d;
}
Owner *newOwner(int id,string name, float value,string password){
	
	Owner *own=new Owner;
	own->ID=id;
	own->value=value;
	own->password=encryption(password,id);
	return own;	
}
bool verify(vector<Owner*> &owners,Owner *currOwner,vector<Node*> &v){
	cout<<"Enter NodeId: ";
			int id;
			cin>>id;
			bool f=false;
			for(int i=0;i<v.size();i++){
				if(v[i]->nodeId==id){
					if(currOwner==v[i]->owner){
						f=true;
					}
					break;
				}	
			}
		
			return f;
}

int main(){
    int num=0,nOwners=0;
    vector<vector<Node*> > set;
    vector<Node*> v;
    vector<Owner*> owners;
    int q,n=0;

    Owner *currOwner;
    bool f=false;
    	
    cin>>q;
    	if(q==1){
			cout<<"Enter id and password";
	    	string password;
	    	int p, q, r;
	    	int id;
	    	cin>>id;
	    	cin>>password;
	    	
	    	for(int i=0;i<owners.size();i++){
	    		if(owners[i]->ID==id){
	    			if(password==decrypt(owners[i]->password,owners[i]->ID)){
	    				f=true;
	    				currOwner=owners[i];
	    				break;
					}
				}
			}
			cout<<"wrong password"<<endl;
		}else{
			cout<<"Enter name, value, password:"<<endl;
			string name,password;
			float value;
			cin>>name;
			cin>>value;
			cin>>password;
			currOwner=newOwner(nOwners++,name,value,password);
			owners.push_back(currOwner);
			f=true;
		}
	}
    
    
    while(1){cout<<"Operations on node:"<<endl;
		cin>>q;
		switch(q){
			case 1:
				vector<Node*> v;
			    v.push_back(getNode(num++,currOwner));
			    set.push_back(v);
				break;
					
		    case 2:
		
			cout<<"Enter number of nodes: ";
			cin>>n;
			vector<Node*> v(1);
			for(int i=0;i<n;i++){
				v[0]=(getNode(num++,currOwner));	
				set.push_back(v);
			}
			break;
		case 3:{
			
			Node *np=getNode(num++,currOwner);
			v.push_back(np);
			cout<<"Enter number of set: ";
			int setNo;
			cin>>setNo;
			set[setNo].push_back(np);
			
		}
		break;
		case 4:{
			bool f=false;
			for(int i=0;i<set.size();i++){
				f=verify(owners,currOwner,set[i]);
				if(f){
					cout<<"Authorised."<<endl;
				}		
			}
			if(!f){			
				cout<<"NOT authorised!"<<endl;
			}
		}break;
	}
    return 0;
}

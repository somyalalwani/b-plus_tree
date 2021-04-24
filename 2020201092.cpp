#include <bits/stdc++.h>
//#include<vector.h>
#include<stdio.h>
#include<string.h>
#include <iostream>
#include <climits>
#include <sstream>
#include <fstream>
using namespace std;

struct Node {

  bool leaf;
  int size=0;
  int *key=new int[2];
  int *count=new int[2];
  Node **ptr = new Node *[3];
};

class BPlusTree {
    Node *root;

       public:
  void insertInternal(Node *temp,Node *child,int x)
   {
       //cout<<"hii";
        if(temp->size<2)
        {
            int i=0;
            

            while(i<temp->size && x>temp->key[i])
                i=i+1;
            
            int j=temp->size;
            ++j;
           while(j>i+1) 
            {
            temp->ptr[j]=temp->ptr[j-1];
            --j;
            }

            j=temp->size;
            while(j>i) 
            {
            temp->key[j]=temp->key[j - 1];
            temp->count[j]=temp->count[j-1];
                --j;
            }
            
            //cout<<j;
           
            

            temp->key[i]=x;
            temp->count[i]=1;
            ++ temp->size;
            temp->ptr[i+1] = child;
        } 

        else {
            int extraKey[3];
            int extracount[3];

            Node *extraPtr[4];
            Node *newInternal = new Node;
            
            
            int i=0;

            while(i<=2)
            {
            extraPtr[i] = temp->ptr[i];
            ++i;
            }
            
            i=0;
            while(i<=1)
            {
            extraKey[i] = temp->key[i];
            extracount[i] = temp->count[i];
            //cout<<extraKey[i];
                ++i;
            }
            //cout<<i;
            
            i=0;
            int j=0;
            while(i<=1 && x>extraKey[i])
                ++i;
            j=3;
            while(j>i)
            {
                extraKey[j]=extraKey[j-1];
                extracount[j]=extracount[j-1];
                --j;
            }
         for(j=4;j> i+1; j--)
                extraPtr[j] = extraPtr[j - 1];
           
            extraKey[i]=x;
            extracount[i]=1;

            
            extraPtr[1+ i] = child;
            //cout<<i;
            
            newInternal->leaf = false;
            temp->size =1;
            newInternal->size =1;
           // extraKey[i]=x;
           // extracount[i]=1;

            i=0;
            j=temp->size+1;
            for(;i<newInternal->size;++i,++j) 
                {
                    newInternal->key[i] = extraKey[j];
                    newInternal->count[i] = extracount[j];
                }
            i=0;
            j=temp->size+1;
            for(;i<newInternal->size+ 1; i++, j++) {
            newInternal->ptr[i] = extraPtr[j];
            }
            if (temp != root)  
            {
            insertInternal(ParentFunct(temp,root), newInternal, temp->key[temp->size]);
            }
            else
                
            {
            Node *newRoot = new Node;
            newRoot->count[0] = temp->count[temp->size];
            newRoot->ptr[0] = temp;
            newRoot->key[0] = temp->key[temp->size];
            newRoot->ptr[1] = newInternal;
            newRoot->leaf = false;
            newRoot->size = 1;
            root = newRoot;
            }
        }
    }
  
    Node * ParentFunct(Node *child, Node *p) 
    {
        Node *parent;
        if (p->leaf)
            return NULL;
        if((p->ptr[0])->leaf) 
            return NULL;
        int i=0;
        for(;i<= p->size;++i)
        {
            if(p->ptr[i]==child)
            {
                parent = p;
                return parent;
            }
            else
            {
                parent = ParentFunct(child,p->ptr[i]);
                if (parent != NULL)
                    return parent;
            }
        }
        return parent;
    }

  BPlusTree()
  {
      root = NULL;
  }
  
  void find(int x)
    {
        if (root!=NULL)
        {
                Node *temp = root;
                while (!temp->leaf)
                {
                    int i=0;
                    
                    while(i<temp->size)
                    {                      
                        if (x<temp->key[i])
                        {
                            temp = temp->ptr[i];
                            break;
                        }
                        if (i==temp->size-1) 
                        {
                            temp = temp->ptr[i + 1];
                            break;
                        }
                        
                        ++i;
                        //cout<<i;
                    }
                }
                int i=0;
                while(i<temp->size)
                {
                    if(temp->key[i]==x)
                        {
                            cout << "YES\n";
                            return;
                        }
                    ++i;
                }
                cout << "NO\n";
        }       
        else 
            cout << "NO\n";
    }

void count(int x)
    {
        cout<<"Count of "<<x<<": ";
        if (root!=NULL)
        {
                Node *temp = root;
                while (!temp->leaf)
                {
                    int i=0;
                    
                    while(i<temp->size)
                    {                      
                        if (x<temp->key[i])
                        {
                            temp = temp->ptr[i];
                            break;
                        }
                        if (i==temp->size-1) 
                        {
                            temp = temp->ptr[i + 1];
                            break;
                        }
                        
                        ++i;
                        //cout<<i;
                    }
                }
                int i=0;
                while(i<temp->size)
                {
                    if(temp->key[i]==x)
                        {
                            cout<<temp->count[i]<<endl;
                            return;
                        }
                    ++i;
                }
                cout<<"0 "<<endl;
        }       
        else 
            cout<<"0 "<<endl;
    }


  void insert_funct(int x)
    {
        if (root!=NULL)
        {
                Node *temp = root;
                while (!temp->leaf)
                {
                    int i=0;
                    
                    while(i<temp->size)
                    {   
                        if (x<temp->key[i])
                        {
                            temp = temp->ptr[i];
                            break;
                        }

                        if (i==temp->size-1) 
                        {
                            temp = temp->ptr[i + 1];
                            break;
                        }
                        
                        ++i;
                        //cout<<i;
                    }
                }     
                int i=0;
                while(i<temp->size)
                {
                    if(temp->key[i]==x)
                        {
                            ++temp->count[i];
                            //cout<<"^^"<<temp->count[i]<<endl;
                            return;
                        }
                    ++i;
                }
                insert(x);
        }       
        else 
           insert(x);
    }
  void insert(int x)
    {
        if(root!=NULL)
        {
           // cout<<"*****";;
        Node *temp = root;
        Node *parent;
        while (!temp->leaf)
        {   //cout<<"y";
            parent=temp;
            
            int i=0;
            while(i<temp->size)
            {
                if(x<temp->key[i])
                {
                    temp = temp->ptr[i];
                    break;
                }
                if (i==temp->size-1)
                {
                    temp = temp->ptr[i + 1];
                    break;
                }
            ++i;
            }
        }
        // cout<<"size:";
        // cout<<temp->size;
        
        if (temp->size<=1) 
        {
            //cout<<"aa";
        //cout<<temp->size<<endl;
        int i = 0;

        while ((i<temp->size) && (x>temp->key[i]))
            i=i+1;

        int j=temp->size;
        while(j > i)
        {
            temp->key[j]=temp->key[j-1];
            temp->count[j]=temp->count[j-1];
            --j;
        }
        //cout<<i;
        //cout<<j;
        //cout<<temp->size;
        temp->key[i] = x;
        temp->count[i]=1;
        temp->size ++;
        
        //cout<<temp->size;
        temp->ptr[temp->size]=temp->ptr[temp->size-1];
        temp->ptr[temp->size-1]=NULL;
        } 
        else {
            // cout<<"bb";
            // cout<<temp->key[0];
        Node *newLeaf = new Node;
        int extraNode[3];
        int extracount[3];
        int i=0;
        while(i<2)
        {
            extraNode[i] = temp->key[i];
            extracount[i] = temp->count[i];
            ++i;
        }
        
       //  cout<<"lll";
       // cout<<extraNode[0]<<endl;
       // cout<<extraNode[1]<<endl;
       // cout<<extraNode[2]<<endl;
       
        i = 0;
        while (i<=1 && x>extraNode[i])
            i++;
        //cout<<"i="<<i;
        int j=3;
        
//         cout<<"i====="<<i;
//         cout<<"j====="<<j;
//          cout<<endl;
//         cout<<"here1:"<<extraNode[0]<<" "<<extraNode[1]<<" "<<extraNode[2];
//  cout<<endl;
	while(j > i) { 
                extraNode[j]=extraNode[j-1];
				extraNode[j]=extraNode[j-1];
				j--; 
            } 
        
     //   cout<<endl;
     //   cout<<endl<<"**i="<<i<<endl;
      // cout<<"::"<<temp->key[0];
    //  cout<<"here2:"<<extraNode[0]<<" "<<extraNode[1]<<" "<<extraNode[2];
        extraNode[i] = x;
        extracount[i]=1;
        newLeaf->leaf = true;
        newLeaf->size= 2;
        temp->size=1;
        
      // cout<<"temp->size"<<temp->size;
        temp->ptr[temp->size]=newLeaf;
        newLeaf->ptr[newLeaf->size] = temp->ptr[2];
        temp->ptr[2] = NULL;
        i=0;
        // cout<<"ff";
        //     cout<<extraNode[0];

        while(i<temp->size) 
        {// cout<<"wohhooo"<<endl;
            temp->key[i] = extraNode[i];
            temp->count[i] = extracount[i];
            ++i;
        }
        
        i=0;
        for(j=temp->size;i<newLeaf->size;++i,++j) 
        {
            newLeaf->key[i] = extraNode[j];
            newLeaf->count[i] = extracount[j];
           // newLeaf->count[i] ++;
        }
        
        if(root==temp)
        {
            //cout<<"huhu2";
          //  cout<<"enter"<<endl;
            Node *newRoot = new Node;
            newRoot->key[0] = newLeaf->key[0];
            newRoot->count[0] = newLeaf->count[0];
            newRoot->ptr[0] = temp;
            newRoot->ptr[1] = newLeaf;
            newRoot->leaf = false;
            newRoot->size = 1;
            
            root = newRoot;
        }
        else 
        { // cout<<"huhu";
       // cout<<"whyy";
            insertInternal(parent,newLeaf, newLeaf->key[0]);
        }
        }
    }

        else
        {
            root = new Node;
            root->key[0] = x;
            root->leaf = true;
            root->size = 1;
            root->count[0]=1;
        } 
    }
    Node *ReturnRoot()
        {
        return root;
        }


  void output(Node *temp) 
  {
        if (temp) 
        {
            int i=0;
            int s=temp->size;
            while(i<s)
            {
                cout << temp->key[i] << "("<<temp->count[i]<<")";
                ++i;
                }
            cout << " || \n";
            if (! temp->leaf ) 
            {
            for(int j=0;j<=temp->size;++j) 
                output(temp->ptr[j]);
            }
        }
    }

void range(struct Node *temp,int a,int b, vector<int> &ans) 
    { //cout<<*ans<<endl;
        if (temp!=NULL) 
        {
            if (temp->leaf!= true) 
            {
            for(int i=0;i<=temp->size;++i) 
                range(temp->ptr[i],a,b,ans);
            }
            else
            {
              for(int i=0;i<temp->size;++i) 
              {
                if(temp->key[i]>=a && temp->key[i]<=b)
                    ans[0]=ans[0]+ temp->count[i] ;  
              }
            }  
        }         
    }
    
};

int ans=0;
/*
int main() {
 
  node.insert_funct(5);
  node.insert_funct(15);
  node.insert_funct(15);
  node.insert_funct(25);
    node.insert_funct(20);
  node.insert_funct(15);
    node.insert_funct(40);
    node.insert_funct(17);
   node.insert_funct(20);
   node.insert_funct(25);
   node.insert_funct(9);

  //node.output(node.ReturnRoot());
  /*
  node.find(15);
  node.find(17);
  node.find(8);
  node.find(9);
  node.find(41);
  node.count(7);
  node.count(1);
  node.count(15);
  node.count(17);
  node.count(20);
  int ans=0;
  node.range(node.ReturnRoot(),6,25,ans);
  cout<<ans<<endl;
  ans=0;
  node.range(node.ReturnRoot(),18,40,ans);
  cout<<ans<<endl;

    return 0;
}
*/

/*int main(int argc, char const *argv[])
{   
	char fileName[200];
	strcpy(fileName,argv[1]);
    BPlusTree node;

    int value1, value2;
	string line;
    
	ifstream infile(fileName);
	while(getline(infile, line))
	{
		if(line.find("INSERT") != string::npos)
		{
			istringstream (line.substr(7)) >> value1;
			node.insert_funct(value1);
		}
		else if(line.find("RANGE") != string::npos)
		{
           
			istringstream (line.substr(6)) >> value1 >> value2;			
            ans=0;
            //int a=stoi(value1);
            //int b=stoi(value2);
            // cout<<"val1:"<<value1;

            // cout<<"val2:"<<value2;
            // cout<<endl;
            // //cout<<value1+value2;
            node.range(node.ReturnRoot(),value1,value2,ans);
            cout<<ans<<endl;
		}
		else if(line.find("FIND") != string::npos)
		{
			istringstream (line.substr(5)) >> value1;
			node.find(value1);
		}
		else if(line.find("COUNT") != string::npos)
		{
			istringstream (line.substr(6)) >> value1;
			node.count(value1);
		}
		else
			cout << "Invalid Command : " << line;
	}
	return 0;
}*/

vector<string>split(string s,char del){
  stringstream ss(s);
  vector<string>request;
  string temp;
  while(getline(ss,temp,del)){
    request.push_back(temp);
  }
  return request;
}
int main(int argc,char** argv){
    vector<int> ans;
    ans.push_back(0);
    if(argc!=2){
        cout<<"Input Filename not given!!!"<<endl;
        return -1;
    }
    BPlusTree node;
    string filename = argv[1];

    ifstream in(filename.c_str());

    if(!in) {
        cout << "Cannot open input file.\n";
        return 1;
    }

    char str[255];

    while(in) {
        in.getline(str, 255);
        vector<string> s;
        s = split(str , ' ' );
        if(in){
            if(s[0]=="INSERT"){
                stringstream temp(s[1]);
                int x=0;
                temp>>x;
                node.insert_funct(x);
            }
            else if(s[0]=="RANGE"){
                stringstream low(s[1]);
                stringstream high(s[2]);
                int x=0,y=0;
                low >> x;
                high >> y;
                
                ans[0]=0;
                node.range(node.ReturnRoot(),x,y,ans);
                for(int i = 0 ; i < 1; i++)
                    cout<<ans[i]<<endl;
            }
            else if(s[0]=="COUNT"){
                stringstream temp(s[1]);
                int x=0;
                temp >> x;
                node.count(x);
            }
            else if(s[0]=="FIND"){
                stringstream temp(s[1]);
                int x=0;
                temp >> x;
                node.find(x);
            }
        }
    }

    in.close();
    return 0;
}
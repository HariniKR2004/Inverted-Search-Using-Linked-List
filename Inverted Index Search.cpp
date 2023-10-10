#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<bits/stdc++.h>
#include<stdlib.h>
using namespace std;

struct word_position
{
    string file_name;
    int line;
    int index;
};

struct node1
{
    string data1;
    struct node1 *link1;
    struct node1 *link2;
};

struct node2
{
    word_position data2;
    struct node2 *link;
};

class Hash
{
    int BUCKET;
    struct node1 *start1;
    struct node2 *start2;
    public:
        Hash(int);
        void insertItem(string ,int ,word_position);
        int hashFunction(string key,int n ) {
            int x;
            x=0;
            int c=1;
            for(int i=0;i<n;i++)
            {
                x=x+(c*int(key[i]));
                c=c+1;

            }
            return (x % BUCKET);
        }
        void create(){
            struct node1 *n=new node1;
            n->data1='0';
            n->link1=n->link2=NULL;
            start1=n;
        }
        void insert()
        {
            static int i=1;
            struct node1 *ptr1;
            ptr1=start1;
            while(ptr1->link1!=NULL){
                ptr1=ptr1->link1;
            }
            struct node1 *n=new node1;
            stringstream ss;
            ss<<i;
            string s;
            ss>>s;
            n->data1=s;
            n->link1=n->link2=NULL;
            ptr1->link1=n;
            i+=1;
        }
        void check(int,string,word_position);
        void displayHash(string);
};

Hash::Hash(int b)
{
    this->BUCKET = b;
}

void Hash::insertItem(string key,int n,word_position obj)
{
    int index = hashFunction(key,n);
    check(index,key,obj);
}

void Hash::check(int index,string key,word_position obj)
{
    int flag=0;
    struct node1 *ptr1;
    struct node2 *ptr2;
    struct node1 *temp;
    ptr1=start1;
    stringstream ss;
    ss<<index;
    string ind;
    ss>>ind;
    while(ptr1!=NULL){
        if(ptr1->data1==ind){
            temp=ptr1;
            break;
        }
        else{
            ptr1=ptr1->link1;
        }
    }
    if(ptr1->link2==NULL){
        struct node1 *n=new node1;
        n->data1=key;
        n->link1=n->link2=NULL;
        ptr1->link2=n;
        ptr2=(struct node2 *)ptr1->link2;
        ptr1=ptr1->link2;
        struct node2 *n1=new node2;
        n1->data2=obj;
        n1->link=NULL;
        ptr1->link1=(struct node1*)n1;
    }
    else{
        while(ptr1!=NULL){
            if(ptr1->data1==key){
                ptr2=(struct node2 *)ptr1->link1;
                while(ptr2->link!=NULL){
                    ptr2=ptr2->link;
                }
                struct node2 *n=new node2;
                n->data2=obj;
                n->link=NULL;
                ptr2->link=n;
                flag=0;
                break;
            }
            else{
                ptr1=ptr1->link2;
                flag=1;
            }
        }
        ptr1=temp;
        if(flag==1){
            while(ptr1->link2!=NULL){
                ptr1=ptr1->link2;
            }
            struct node1 *n=new node1;
            n->data1=key;
            n->link1=n->link2=NULL;
            ptr1->link2=n;
            ptr2=(struct node2 *)ptr1->link2;
            ptr1=ptr1->link2;
            struct node2 *n1=new node2;
            n1->data2=obj;
            n1->link=NULL;
            ptr1->link1=(struct node1*)n1;
        }
    }
}

void Hash::displayHash(string key)
{
    int flag=0;
    struct node1 *ptr1;
    struct node2 *ptr2;
    struct node1 *temp;
    int index;
    ptr1=start1;
    index=hashFunction(key,key.size());
    stringstream ss;
    ss<<index;
    string ind;
    ss>>ind;
    while(ptr1!=NULL)
    {
        if(ptr1->data1==ind){
            temp=ptr1;
            break;
        }
        else{
            ptr1=ptr1->link1;
        }
    }
    while(ptr1!=NULL)
    {
        if(ptr1->data1==key)
        {
            cout<<"--------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            ptr2=(struct node2*)ptr1->link1;
            while(ptr2!=NULL)
            {
                cout<<"\t\t\t\tFILE NAME   : "<<ptr2->data2.file_name<<endl;
                cout<<"\t\t\t\tLINE NUMBER : "<<ptr2->data2.line<<endl;
                cout<<"\t\t\t\tWORD NUMBER : "<<ptr2->data2.index<<endl;
                cout<<"--------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                ptr2=ptr2->link;
            }
            flag=1;
            break;
        }
        else
        {
            flag=0;
            ptr1=ptr1->link2;
        }
    }
    if(flag==0)
    {
        cout<<"\n\n\t\t\t\t\t\tNO INSTANCE EXIST.........."<<endl;
    }
    system("pause");
    system("cls");
}

class indexing
{
    vector<string>filelist;
    vector<word_position>wp;
    public:
        void add_file(Hash);
        void show_files();
};

void indexing::add_file(Hash h)
{
    fstream f;
    string f_name;
    int num,index;
    cout<<"\n\n\n";
    cout<<"\t\t\t\t\tEnter the file name : ";
    cin>>f_name;

    auto it=find(filelist.begin(),filelist.end(),f_name);
    if(it!=filelist.end())
    {
        cout<<"\t\t\t\t\tFile already added..."<<endl;
        system("pause");
        system("cls");
    }
    else
    {
        f.open(f_name,ios::in);
        if(!f)
        {
            cout<<"\n";
            cerr<<"\t\t\t\t\tFile does not exist...."<<endl;
            system("pause");
            system("cls");
        }
        else
        {
            filelist.push_back(f_name);
            string line,word;
            int line_number=0,word_number=0;
            while(getline(f,line))
            {
                line_number++;
                word_number = 0;
                stringstream s(line);
                while(s>>word)
                {
                    word_number++;
                    word_position obj;
                    obj.file_name = f_name;
                    obj.line = line_number;
                    obj.index = word_number;
                    num=word.size();
                    h.insertItem(word,num,obj);
                }
            }
            system("cls");
        }
    }
}

void indexing::show_files()
{
    int size = (int)filelist.size();
    cout<<"\t\t\t\t\tFILES THAT ARE ADDED"<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    for(int i=0;i<size;i++)
    {
        cout<<"\t\t\t\t\t"<<i+1<<"."<<filelist[i]<<endl;
    }
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    system("pause");
    system("cls");
    if(!size) cout<<"No files added\n";
}

int main()
{
    int choice;
    indexing in;
    string word;
    Hash h(33);
    h.create();
    for(int i=0;i<32;i++){
        h.insert();
    }
    do
    {
        cout<<"\t\t\t\t\t=========================================================="<<endl;
        cout<<"\t\t\t\t\t\t\t\tMAIN MENU"<<endl;
        cout<<"\t\t\t\t\t\t\t\t\n\t";
        cout<<"\t\t\t\t\t\t1.Add file\n";
        cout<<"\t\t\t\t\t\t\t2.See the files\n";
        cout<<"\t\t\t\t\t\t\t3.Search for the word\n";
        cout<<"\t\t\t\t\t\t\t4.Exit\n ";
        cout<<"\t\t\t\t\t=========================================================="<<endl;
        cout<<"\n";
        cout<<"\t\t\t\t\tEnter your choice : ";
        cin>>choice;
        switch (choice)
        {
            case 1:
            {
                system("cls");
                in.add_file(h);
                break;
            }
            case 2:
            {
                system("cls");
                in.show_files();
                break;
            }
            case 3:
            {
                system("cls");
                cout<<"\n\n\n";
                cout<<"\t\t\t\tENTER THE WORD TO BE SEARCHED : ";
                cin>>word;
                h.displayHash(word);
                break;
            }
            case 4:
            {
                system("cls");
                break;
            }
            default :
            {
                cout<<"\n\t\t\t\t\tInvalid choice..."<<endl;
                system("pause");
                system("cls");
                break;
            }
        }
    }while(choice!=4);
}

#include <bits/stdc++.h>
using namespace std;

struct fline
{
    int linenumber;
    string line;
    fline *next;
};
fline *head;

void createList()
{
    head=NULL;
}
fline *createNode(string str,int linenumber)
{
    fline *newLine= new fline;
    newLine->line = str;
    newLine->linenumber=linenumber;
    newLine->next = NULL;
    return newLine;
}
void insert1(fline *parameter){
    if(head==NULL){
        head=parameter;
        return;
    }
    fline *iterator1;
    fline *before;
    for(iterator1=head;;iterator1=iterator1->next){
        if(iterator1->next==NULL){
            iterator1->next=parameter;
            return;
        }
    }

}
int main()
{
    FILE *fp;
    string str;
    int i=0;
    char Block[1000],ch;
    int numl=0;
    fp = fopen("line55.txt","r");
    if(fp == NULL)
    {
        printf("error while opening the file\n");
        exit(0);
    }

    ch = fgetc(fp);
    while (ch != EOF)
    {

        ch = fgetc(fp);
        Block[i]=ch;
        i++;
    }
     createList();
    stringstream X(Block);
    int num=1;
    while(getline(X, str, '\n'))
    {

        insert1(createNode(str,num));
        num++;
    }
    fline *it;
    for(it=head;it->next!=NULL;it=it->next)
    {
        cout<<it->linenumber<<" number line:"<<it->line<<endl;

    }
    //cout<<head->next->line<<endl;


    return 0;
}


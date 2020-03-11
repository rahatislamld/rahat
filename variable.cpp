#include<iostream>
#include<vector>
#include<string>
#include<string.h>

using namespace std;

int main()
{
    FILE *cfile;
    vector<string> oper;
    int j=0, c=0;

    char block[1000], fileName[100], op[10];
    do
    {
        cin>>fileName;
        cfile= fopen(fileName, "r");
    } while(cfile==NULL);

    while(!feof(cfile))
    {
        fscanf(cfile, "%s", block);
        if(!strcmp(block, "char")||!strcmp(block, "int"))
        {
            fscanf(cfile, "%[^\n]", block);
            {
                if(!strcmp(block," main()")) continue;
                for(int i=0; i<strlen(block); i++)
                {
                    if(block[i]==','||block[i]==';'||block[i]=='=')
                    {
                        op[j]='\0';
                        oper.push_back(op);
                        c++;
                        j=0;
                        if(block[i]=='=')
                            while(block[i]!=',')
                                i++;
                    }
                    else if(block[i]!=' ')op[j++]=block[i];
                }
            }

        }

    }
    cout<< c<<endl;
    for(auto i= oper.begin(); i<oper.end(); i++)
        cout<<*i<<endl;

}

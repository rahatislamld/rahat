
#include<bits/stdc++.h>
using namespace std;


const int  MAX = 100;

int totalLine = 0;
int newTotalLine = 0;

struct scope
{
    int startLine;
    int endLine;
    string keyword;
};
vector < string > codeWord[ 100 ];
vector < string > wordType[ 100 ];
vector < scope > scopeInfo;
map < string, string > alternated_identifiers;


int parentLine[ MAX ];
int childLine[ MAX ];

vector<int> functionPrototype;
vector<int> header;
int headerEndingLine;


void childParentMapping()
{
    for ( int i = 1; i + 1 < MAX; ++i )
    {
        childLine[ i ] = i + 1;
    }

    for ( int i = 2; i < MAX; ++i )
    {
        parentLine[ i ] = i - 1;
    }
}


int strToInt(string str)
{
    int r = 0;
    for (int i = 0;i<str.size();i++ )
    {
        r *= 10;
        r += str[ i ]-'0';
    }
    return r;
}


void mappingOrderChange(int position1,int position2)
{
    childLine[parentLine[position2]] = childLine[position2];
    parentLine[childLine[position2]] = parentLine[position2];
    parentLine[childLine[position1]] = position2;
    childLine[position2] = childLine[position1];
    childLine[position1] = position2;
    parentLine[ position2 ] = position1;
}

void functionPrototypinng()
{
    for (int i=1;i<= totalLine;i++ )
    {
        if(codeWord[i].size()>=4 && (codeWord[i][0]=="int"||codeWord[i][0]=="double"||codeWord[i][0]=="char")&&wordType[i][1]=="identifier"&&codeWord[i][2]=="(")
        {
            newTotalLine++;
            codeWord[newTotalLine] = codeWord[i];
            wordType[newTotalLine] = wordType[i];
            codeWord[newTotalLine].push_back(";");
            wordType[newTotalLine].push_back("operator");
            functionPrototype.push_back(newTotalLine);
            mappingOrderChange(headerEndingLine, newTotalLine);
        }
    }
}

void scoping(int startLine,int endLine)
{
    stack<pair<int,string> > ss;
    pair<int,string> lastKeyword;

    for (int LN=startLine;LN<=endLine; LN++)
    {
        for (int CL=0;CL<codeWord[LN].size();CL++)
        {
            if (wordType[LN][CL]=="keyword")
            {
                lastKeyword.first = LN;
                lastKeyword.second = codeWord[LN][CL];


                if(CL > 0 && codeWord[LN][CL]=="if" && codeWord[LN][CL-1] == "else" )
                    lastKeyword.second = "else if";
            }

            if(codeWord[LN][CL]=="{")
            {
                ss.push(lastKeyword);
            }

            if(codeWord[LN][CL]=="}")
            {
                scope sc;
                sc.startLine = ss.top().first;
                sc.keyword = ss.top().second;
                sc.endLine = LN;
                ss.pop();
                scopeInfo.push_back(sc);
            }
        }
    }
}

void scopePrint()
{
    for (int i=0; i<scopeInfo.size(); i++ )
    {
        cout << scopeInfo[i].keyword << " " << scopeInfo[i].startLine << " " << scopeInfo[i].endLine << "\n";
    }

}

string replace_identifiers(string in)
{
    string s = "";
    if(alternated_identifiers.find(in)!=alternated_identifiers.end() )
    {
        return alternated_identifiers[in];
    }

    int len = 0;
    while(len<5)
    {
        len= rand()%9;
    }

    for(int i = 0;i<len;i++)
    {
        s+='a'+rand()%26;
    }

    return alternated_identifiers[in]=s;
}

void printThisLine(int LN)
{
    for(int i=0; i<codeWord[LN].size();i++)
        cout << codeWord[LN][i] << " ";
    cout << "\n";
}

void printFullCode()
{
    for (int curr=1;curr<=newTotalLine;curr=childLine[curr])
    {
        printThisLine(curr);
    }
}

void globalVariableInTop()
{
    for(int i=headerEndingLine+1;i<=totalLine;i++)
    {
        if(codeWord[i].empty())
        {
            continue;
        }
        bool isGlobal=true;
        for(int j=0;j<scopeInfo.size();j++)
        {
            if (i>=scopeInfo[j].startLine&&i<=scopeInfo[j].endLine)
            {
                isGlobal = false;
                break;
            }
        }
        if (isGlobal)
        {
            mappingOrderChange(headerEndingLine,i);
        }
    }
}

void functionSwaping( int s1, int s2 )
{
    int ss1=scopeInfo[s1].startLine;
    int es1=scopeInfo[s1].endLine;
    int ss2=scopeInfo[s2].startLine;
    int es2=scopeInfo[s2].endLine;

    int n1=childLine[es1];
    int n2=childLine[es2];
    int p1= parentLine[ss1];
    int p2= parentLine[ss2];



    childLine[p1]= ss2;
    parentLine[ss2]= p1;

    childLine[es1]= n2;
    parentLine[n2]= es1;

    childLine[p2]= ss1;
    parentLine[ss1]= p2;

    childLine[es2]= n1;
    parentLine[n1]= es2;
}

void functionShuffle()
{
    vector<int> functionScope;
    for (int i = 0;i<scopeInfo.size(); i++ )
    {
        if (scopeInfo[i].keyword=="int"||scopeInfo[i].keyword=="double"||scopeInfo[i].keyword=="char")
        {
            functionScope.push_back(i);
        }
    }

    vector<int>functionOrder= functionScope;
    random_shuffle(functionOrder.begin(),functionOrder.end());
    reverse(functionOrder.begin(),functionOrder.end());


    for (int i=0;i<functionOrder.size();++i)
    {
        if(functionOrder[i]!=functionScope[i])
        {
            int jj1 = i, jj2;
            for (int j=i+1;j<functionOrder.size();j++)
            {
                if (functionScope[j]==functionOrder[i])
                {
                    jj2 = j;
                    break;
                }
            }

            functionSwaping(functionScope[jj1],functionScope[jj2]);
            swap(functionScope[jj1],functionScope[jj2]);
        }
    }
}

void initialTask()
{
    for(int i=1;i<=totalLine;++i )
    {
        if(wordType[i].empty())
        {
            headerEndingLine=i;
        }
        else if(codeWord[i][0] =="#" )
        {
            headerEndingLine= i;
        }
        else
        {
            break;
        }
    }
}

int main()
{
    FILE *fp;
    string str, CODE;
    char ch;

    fp = fopen("output.txt","r");
    alternated_identifiers["main"] = "main";

    while((ch=fgetc(fp))!=EOF)
        CODE=CODE+ch;

    stringstream X(CODE);
    while(getline(X,str,'\n'))
    {
        string s1,s2,s3;

        stringstream Y( str );
        getline(Y,s1,'\t');
        getline(Y,s2,'\t');
        getline(Y,s3,'\t');
        int line=strToInt(s3);

        if(s1=="identifier"&&s2!="include"&&s2!="define"&&s2!="stdio"&&s2!="h"&&s2!="stdlib" && s2!="math")
        {
            s2=replace_identifiers(s2);
        }

        codeWord[line].push_back(s2);
        wordType[line].push_back(s2);

        totalLine=max(totalLine,line);
    }

    initialTask();

    childParentMapping();
    newTotalLine = totalLine;
    functionPrototypinng();

    scoping(1,totalLine);
    globalVariableInTop();
    functionShuffle();
    printFullCode();
}

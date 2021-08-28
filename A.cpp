#include <bits/stdc++.h>
using namespace std;



int totalLine=0;
string check;
ofstream PRINTinFILE("output.txt");
struct structL
{
    string text;
    int line;
};
structL LINE[100];
string keywords[32] = {"auto","break","case","char","const",
                       "continue","default","do","double","else",
                       "enum","extern","float","for","goto","if",
                       "int","long","register","return","short",
                       "signed","sizeof","static","struct","switch",
                       "typedef","union","unsigned","void","volatile","while"
                      };

void checking(int l,int col)
{
    if (check.size()==0)
        return;
    int flag = 0;
    for (int k=0; k<32; k++)
    {
        if (check.compare(keywords[k])==0)
        {
            flag=1;
            break;
        }
    }
    if (flag==1)
    {
        PRINTinFILE << "keyword\t" << check << "\t" << LINE[l].line <<"\n";
    }
    else
        PRINTinFILE << "identifier\t" << check << "\t" << LINE[l].line <<"\n";
    check = "";
}

bool itISoperatordup(char ch)
{
    if (ch=='+'||ch=='-'||ch=='&'||ch =='|'|| ch=='='||ch == '>'||ch=='<')
        return true;
    else
        return false;
}

bool itISoperator(char ch)
{
    if(ch=='{'||ch =='}'||ch=='['||ch==']'||ch =='('||ch==')'||ch=='#'||ch==';')
         return true;
    else if(ch==':'||ch=='?'||ch =='.'||ch=='+'||ch=='-'||ch=='*'||ch =='/')
         return true;
    else if(ch=='%'||ch=='^'||ch=='&'||ch== '|'||ch =='!'||ch=='='||ch=='<'||ch=='>'||ch == ',')
        return true;
    else
        return false;
}

bool itISdigit(char ch)
{
    if (ch>='0'&&ch<='9')
        return true;
    else
        return false;
}

void lexing()
{
    for (int i=0; i<totalLine; i++)
    {
        int lenPerLine=LINE[i].text.size();
        for (int j=0; j<lenPerLine; )
        {
            if (itISoperator(LINE[i].text[j]) && itISoperatordup(LINE[i].text[j+1]))
            {
                checking(i,j);
                PRINTinFILE << "operator\t" << LINE[i].text[j] << LINE[i].text[j+1] << "\t" << LINE[i].line <<"\n";
                j += 2;
            }
            else if (itISoperator(LINE[i].text[j]))
            {
                checking(i, j);
                PRINTinFILE << "operator\t" << LINE[i].text[j] << "\t" << LINE[i].line << "\n";
                j++;
            }
            else if(LINE[i].text[j]=='\\')
            {
                checking(i, j);
                PRINTinFILE << "character\t" << LINE[i].text[j] << LINE[i].text[j+1] << "\t" << LINE[i].line << "\n";
                j += 2;
            }
            else if(itISdigit(LINE[i].text[j]))
            {
                checking(i, j);
                int f=0, a=LINE[i].text[j]-'0';
                j++;
                int temp=j;
                while (itISdigit(LINE[i].text[j])||LINE[i].text[j]=='.')
                {
                    if (LINE[i].text[ j ]=='.')
                    {
                        f = 1;
                        PRINTinFILE << "float\t" << a << ".";
                        a=0;
                    }
                    else
                        a=a*10+(LINE[i].text[j]-'0');
                    j++;
                }
                if(f==0)
                    PRINTinFILE << "integer\t" << a << "\t" << LINE[i].line << "\n";
                else
                    PRINTinFILE << a << "\t" << LINE[i].line << "\n";
            }
            else if (LINE[i].text[j] =='"')
            {
                checking(i, j);
                j++;
                int temp = j;
                string strg;
                while ( LINE[i].text[j]!='"')
                {
                    strg =strg+LINE[i].text[j];
                    j++;
                }
                j++;
                PRINTinFILE << "string\t" << strg << "\t" << LINE[i].line << "\n";
            }
            else if (LINE[i].text[j]==' '|| LINE[i].text[j]=='\n')
            {
                checking(i, j);
                j++;
            }
            else
            {
                check =check+LINE[i].text[j++];
            }
        }
    }
}

int main()
{
    FILE *fp;
    string str, codeText, mainCodeText;
    char ch;

    cout << "Enter Your File Path:";
    char PRINTinFILEName[100];
    gets(PRINTinFILEName);

    fp = fopen(PRINTinFILEName,"r");

    if ( fp == NULL )
    {
        printf("error while opening the file\n");
        exit( 0 );
    }

    while ((ch = fgetc(fp))!= EOF)
    {
        codeText=codeText+ch;
    }

    mainCodeText =codeText;

    for (int i =0; i+1 <codeText.size(); ++i )
    {
        int starti =i;
        if ( codeText[i]=='/'&&codeText[i+1]=='/')
        {
            while (i<codeText.size()&&codeText[i]!='\n')
            {
                i++;
            }

            i--;
        }

        if (codeText[i] == '/' && codeText[i+1]=='*')
        {
            while (i+1<codeText.size()&&( codeText[i]!='*'||codeText[i+1]!='/'))
            {
                i++;
            }

            if (i+1==codeText.size()&&(codeText[i]!='*'||codeText[i+1]!='/'))
            {
                int lineNumberCount = 1;

                for (int j = 0; j<starti; ++j )
                {
                    if ( mainCodeText[ j ] == '\n' )
                    {
                        lineNumberCount++;
                    }
                }
            }

            i++;
        }

        if(starti==i)
        {
            continue;
        }

        while ( starti <= i )
        {
            if ( codeText[ starti ] != '\n' )
            {
                codeText[ starti ] = ' ';
            }

            starti++;
        }

    }

    stringstream X(codeText);
    while (getline(X,str,'\n'))
    {
        LINE[totalLine].text = str + " ";
        LINE[totalLine++].line = totalLine;
    }

    lexing();

    return 0;
}

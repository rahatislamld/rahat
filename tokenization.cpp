#include <bits/stdc++.h>
using namespace std;


struct line
{
    int line;
    string text;
};

line eachLine[ 100 ];
string keywords[ 32 ] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                          "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
                          "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
                        };
int totalLine = 0;
string check;



bool digitCheck( char ch )
{
    if ( ch >= '0' && ch <= '9' )
        return true;
    else
        return false;
}

bool oparetorCheck( char ch )
{
    if ( ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == '#' || ch == ';' || ch == ':' || ch == '?' || ch == '.' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '&' ||ch ==  '|' || ch == '!' || ch == '=' || ch == '<' || ch == '>' || ch == ',' )
        return true;
    else
        return false;
}

bool oparetorCheckdup(char ch)
{
    if ( ch == '+' || ch == '-' || ch == '&' || ch == '|' || ch == '=' || ch == '>' || ch == '<' )
        return true;
    else
        return false;
}

void keyword_identifier_check( int l, int col )
{
    if ( check.size() == 0 )
        return;
    int flag = 0;
    for ( int k = 0; k < 32; k++ )
    {
        if ( check.compare( keywords[ k ] ) == 0 )
        {
            flag = 1;
            break;
        }
    }
    if ( flag == 1 )
        cout << "keyword\n" << check << "\n" << eachLine[ l ].line << "\n" ;
    else
        cout << "indentifier\n" << check << "\n" << eachLine[ l ].line << "\n";

    check = "";
}

void tokenization()
{
    for ( int i = 0; i < totalLine; i++ )
    {
        int leneachLine = eachLine[ i ].text.size();
        for ( int j = 0; j < leneachLine; )
        {
            if ( oparetorCheck( eachLine[ i ].text[ j ] ) && oparetorCheckdup( eachLine[ i ].text[ j + 1 ] ) )
            {
                keyword_identifier_check( i, j );
                cout << "oparetor\n" << eachLine[ i ].text[ j ] << eachLine[ i ].text[ j + 1 ] << "\n" << eachLine[ i ].line << "\n";
                j += 2;
            }
            else if ( oparetorCheck( eachLine[ i ].text[ j ] ) )
            {
                keyword_identifier_check( i, j );
                cout << "oparetor\n" << eachLine[ i ].text[ j ] << "\n" << eachLine[ i ].line << "\n";
                j += 1;
            }

            else if ( eachLine[ i ].text[ j ] == '\\' )
            {
                keyword_identifier_check( i, j );
                cout << "character\n" << eachLine[ i ].text[ j ] << eachLine[ i ].text[ j + 1 ] << "\n" << eachLine[ i ].line << "\n";
                j += 2;
            }
            else if ( digitCheck(eachLine[ i ].text[ j ] ) )
            {
                keyword_identifier_check( i, j );
                int f = 0, a = eachLine[ i ].text[ j ] - '0';
                j++;
                int temp = j;
                while ( digitCheck( eachLine[ i ].text[ j ] ) || eachLine[ i ].text[ j ] == '.' )
                {
                    if ( eachLine[ i ].text[ j ] == '.' )
                    {
                        f = 1;
                        cout << "float\n" << a << ".";
                        a = 0;
                    }
                    else
                        a = a * 10 + ( eachLine[ i ].text[ j ] - '0' );
                    j++;
                }
                if( f == 0 )
                    cout << "integer\n" << a << "\n" << eachLine[ i ].line << "\n";
                else
                    cout << a << "\n" << eachLine[ i ].line << "\n";
            }
            else if ( eachLine[ i ].text[ j ] == '"' )
            {
                keyword_identifier_check( i, j );
                j++;
                int temp = j;
                string strg;
                while ( eachLine[ i ].text[ j ] != '"' )
                {
                    strg = strg + eachLine[ i ].text[ j ];
                    j++;
                }
                j++;
                cout << "string\n" << strg  << "\n" << eachLine[ i ].line << "\n" << temp + 1 << "\n";
            }
            else if ( eachLine[ i ].text[ j ] == ' ' || eachLine[ i ].text[ j ] == '\n' )
            {

                keyword_identifier_check( i, j );

                j++;
            }
            else
            {
                check = check + eachLine[ i ].text[ j++ ];
            }
        }
    }
}

int main()
{
    FILE *fp;
    freopen("tokens.txt", "w", stdout );
    string str, codeText;
    char ch;


    fp = fopen( "rahat (2).cpp", "r" );

    if ( fp == NULL )
    {
        printf( "error while opening the cout\n" );
        exit( 0 );
    }

    while ( ( ch = fgetc( fp ) ) != EOF )
    {
        codeText = codeText + ch;
    }

    stringstream X( codeText );
    while ( getline( X, str, '\n' ) )
    {
        eachLine[ totalLine ].text = str + " ";
        eachLine[ totalLine++ ].line = totalLine;
    }

    tokenization();
    fclose(fp);
    return 0;
}

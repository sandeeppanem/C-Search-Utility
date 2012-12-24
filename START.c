/*<.module progid="C-search"           Source="START.C">                *

* PROGRAM NAME:C-SEARCH UTILITY                                         *

* Description:A String is searched in every function of the input       *
*             Supplied program files.The Objective is to search
*             for the String in each function from the main and         *
*             have to print the entire path from main to the
*             function that contains the string is displayed            *                                              *
*
* Usage      : This can be used to find the impact of particular        *
*              string in a particular function and later can be         *
*              used to extract the function code.                       *
* Parameters  :input-supplied file,main,string to be searched,file-name *
*              to store the paths                                       *                  *
*                                                                       *
* Created By  :    Sandeep Panem
                   
  </module>                                                             *
*
* <.modification name="SANDEEP" date="27/10/2011">                    *

************************************************************************/

/***********************************************************************
 *                                                                     *
 *                              INCLUDES                               *
 *                                                                     *
 **********************************************************************/
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

/***********************************************************************
 *                                                                     *
 *                              DEFINES                                *
 *                                                                     *
 ***********************************************************************/
                                                                            
/***********************************************************************
 *                                                                     *
 *                          PUBLIC VARIABLES                           *
 *                                                                     *
 **********************************************************************/

char stack[100]={0};
int s=0;
int k=0;//number of user-defined functions
int occur=0;
char fun_name[100][100]={0};
/***********************************************************************
 *                                                                     *
 *                        FUNCTION PROTOTYPES                          *
 *                                                                     *
 **********************************************************************/

void fun_names(int argc,char **argv,int l);
void search_string(int argc,char **argv,int l);
void path(int argc,char **argv,int l);
void print_path(int argc,char **argv);
void push(char ch1);
void pop();
int isempty();

/*************************************************************************
 * <Function-name="main"                                                 *
 *                                                                       *
 *  Description:Searches for a Particualr String and prints the function *
 *              in which the string is found and the Function path       *
 *                                                                       *
 *  Parameters:argc and argv                                             *
 *                                                                       *
 *  Returns:nothing                                                      *
 *                                                                       *
 *  Added By:SANDEEP                                                   *
 *                                                                       *
 *                                                                       *
 ************************************************************************/
int main(int argc,char **argv)
{
int i;
for(i=0;i<argc-4;i++)
{
fun_names(argc,argv,i);
search_string(argc,argv,i);
path(argc,argv,i);

if(occur>0)
{
printf("\n\n*************Total number of occurences are %d***************",occur);
}
else
printf("\n No Match Found");
s=0;
occur=0;
}
print_path(argc,argv);
return 0;
}

/***********************************************************************
 * <Function-name="Function_names"                                     *
 *                                                                     *
 *  Description: Extract the function names so as to differentiate     *
 *               between user-defined and built-in functions           *
 *                                                                     *
 *  Parameters: argc and argv                                          *
 *                                                                     *
 *  Returns:   nothing                                                 *
 *                                                                     *
 *  Added By:SANDEEP                                                 *
                                                                       *
 ***********************************************************************/

void fun_names(int argc,char **argv,int l)
{
FILE *fp=fopen(argv[l+1],"r");
int i=0,j=0,check=0;
char ch;
char search[100]={0};
if(fp==NULL)
printf("\n file could not be opened");
for(i=0;argv[argc-3][i]!='\0';i++)
fun_name[k][i]=argv[argc-3][i];
while((ch=fgetc(fp))!=EOF)
{
if(ch=='/' && fgetc(fp)=='*')
{
while(!(fgetc(fp)=='*') || !(fgetc(fp)=='/'));
}
else if(ch=='/' && fgetc(fp)=='/')
{
while(!(ch=='\n'))
{
ch=fgetc(fp);
}
}
else if(ch=='\n')
{
for(i=0;search[i]!='\0';i++)
search[i]=0;
j=0;
}
else if(ch==' ')
{
for(i=0;search[i]!='\0';i++)
search[i]=0;
j=0;
}
else if(ch=='(')
{
k++;
for(i=0;search[i]!='\0';i++)
{
fun_name[k][i]=search[i];
}
}
else
{
search[j]=ch;
j++;
}
for(i=0;argv[argc-3][i]!='\0' || search[i]!='\0';i++)
{
if(argv[argc-3][i]!=search[i])
{
check=1;
break;
}
check=0;
}
if(check==0)
{
fclose(fp);
break;
}
}
}

/**************************************************************************
 * <Function-name="search_string"                                         *
 *                                                                        *
 *  Description:Find The string in which function and line number it is   *
 *                                                                        *
 *  Parameters:argc and argv                                              *
 *                                                                        *
 *  Returns:nothing                                                       *
 *                                                                        *
 *  Added By:SANDEEP                                                    *
 *                                                                        *
 **************************************************************************/


void search_string(int argc,char **argv,int l)
{
FILE *fp;
char ch,*ptr;
char p[40]={0};
char temp_fun_name[40]={0};
char temp_fun_name1[40]={0};
int i=0,j=0,line=0,n,t;
int check,match_found;
char search[1000]={0};
fp=fopen(argv[l+1],"r");
if(fp==NULL)
printf("\n file could not be opened");
printf("\n************Total number of functions are : %d***************\n",k+1);
for(i=0;i<=k;i++)
{
for(j=0;fun_name[i][j]!='\0';j++)
{
printf("%c",fun_name[i][j]);
}
printf("\n");
}
j=0;
printf("\n\n**************Searching for the string \"%s\" in File \"%s\"******************\n",argv[argc-2],argv[l+1]);
while(fp!=NULL)
{
fgets(p,40,fp);
line++;
n=strspn(argv[argc-3],p);
if(n==4)
break;
}
strcpy(temp_fun_name1,"main");
while((ch=fgetc(fp))!=EOF)
{
if(ch=='(')
{
for(i=0;i<=k;i++)
{
t=strcmp(search,fun_name[i]);
if(t==0)
{
strcpy(temp_fun_name1,search);
break;
}
}
}
else if(ch=='{')
{
if(isempty())
strcpy(temp_fun_name,temp_fun_name1);
push(ch);
}
else if(ch=='\n'|| ch==' ')
{
if((ptr=strstr(search,argv[argc-2]))==NULL)
match_found=0;
else
match_found=1;
if(match_found==1)
{
occur++;
printf("\n match found at line number:%d->",line+1);
if(strcmp(temp_fun_name,"NULL"))
printf("In The Function name:%s",temp_fun_name);
else
printf("It is in the Function Definition");
for(i=0;search[i]!='\0';i++)
search[i]=0;
j=0;
match_found=0;
}
if(ch=='\n')
line++;
for(i=0;search[i]!='\0';i++)
search[i]=0;
j=0;
}
else if(ch=='}')
{
pop();
if(isempty())
strcpy(temp_fun_name,"NULL");
}
else
{
search[j]=ch;
j++;
}
}
fclose(fp);
strcpy(search,"NULL");
j=0;
strcpy(temp_fun_name,"NULL");
strcpy(temp_fun_name1,"NULL");
s=0;
return;
}

/***************************************************************************
 * <Function-name="push()"                                                 *
 *                                                                         *
 *  Description:Inserts a character into stack                             *
 *                                                                         *
 *  Parameters:character                                                   *
 *                                                                         *
 *  Returns:nothing                                                        *
 *                                                                         *
 *  Added By:SANDEEP                                                     *
 ***************************************************************************/

void push(char ch1)
{
stack[s]=ch1;
s++;
return;
}

/***************************************************************************
 * <Function-name="pop()"                                                  *
 *                                                                         *
 *  Description:Removes an element from the stack                          *
 *                                                                         *
 *  Parameters: none                                                       *
 *                                                                         *
 *  Returns:nothing                                                        *
 *                                                                         *
 *  Added By:SANDEEP                                                     *
 ***************************************************************************/

void pop()
{
s--;
stack[s]=0;
return;
}

/***************************************************************************
 * <Function-name="isempty()"                                              *
 *                                                                         *
 *  Description: checks whether stack is empty or not                      *
 *                                                                         *
 *  Parameters:none                                                        *
 *                                                                         *
 *  Returns:integer                                                        *
 *                                                                         *
 *  Added By:SANDEEP                                                     *
 ***************************************************************************/


int isempty()
{
if(s==0)
return 1;
else
return 0;
}

/***************************************************************************
 * <Function-name="path()"                                                 *
 *                                                                         *
 *  Description:Stores the order of function-calls in a file               *
 *                                                                         *
 *  Parameters:argc and argv                                               *
 *                                                                         *
 *  Returns:nothing                                                        *
 *                                                                         *
 *  Added By:SANDEEP                                                     *
 ***************************************************************************/

void path(int argc,char **argv,int l)
{
char temp_fun_name[40]={0};
char temp_fun_name1[40]={0};
char temp1[30]={0};
FILE *fp;
FILE *fp1;
char ch;
int i=0,j=0,n=0,check=0;
char search[100]={0};
fp=fopen(argv[l+1],"r");
fp1=fopen(argv[argc-1],"a");
if(fp==NULL)
printf("file could not be opened");
if(fp1==NULL)
printf("file could not be opened");
while(fp!=NULL)
{
fgets(temp1,30,fp);
n=strspn("main()",temp1);
if(n==6)
break;
}
fprintf(fp1,"*********%s**********\n\n",argv[l+1]);
strcpy(temp_fun_name1,"main");
while((ch=fgetc(fp))!=EOF)
{
if(ch=='"')
{
while(fgetc(fp)!='"');
}
if(ch=='(')
{
// differentiate between built-in and user defined functions
if(strlen(search)>0)
{
for(i=0;i<=k;i++)
{
check=strcmp(search,fun_name[i]);
if(check==0)
break;
}

if(check==0)
{
if(isempty())
strcpy(temp_fun_name1,search);
else
{
strcpy(temp_fun_name1,search);
fprintf(fp1,"%s->%s\n",temp_fun_name,temp_fun_name1);
}
}
else
for(i=0;search[i]!='\0';i++)
{
search[i]=0;
j=0;
}
}
}
else if(ch=='{')
{
if(isempty())
strcpy(temp_fun_name,temp_fun_name1);
push(ch);
}
else if(ch=='\n' || ch==' ')
{
for(i=0;search[i]!='\0';i++)
{
search[i]=0;
j=0;
}
}
else if(ch=='}')
{
pop();
if(isempty())
{
strcpy(temp_fun_name,"NULL");
}
}
else
{
search[j]=ch;
j++;
}
}
s=0;
fprintf(fp1,"\n\n");
for(i=0;i<=k;i++)
strcpy(fun_name[i],"NULL");
k=0;
strcpy(search,"NULL");
j=0;
strcpy(temp_fun_name,"NULL");
strcpy(temp_fun_name1,"NULL");
s=0;
fclose(fp1);
fclose(fp);
return;
}

/***************************************************************************
 * <Function-name="print_path()"
 *
 *  Description:Prints the Paths of the function calls
 *
 *  Parameters:argc and argv
 *
 *  Returns:nothing
 *
 *  Added By:SANDEEP
 ***************************************************************************/
/**************** Prints the paths of the function calls***************/
void print_path(int argc,char **argv)
{
FILE *fp;
char ch;
fp=fopen(argv[argc-1],"r");
printf("\n***************** Printing The Path****************\n");
while((ch=fgetc(fp))!=EOF)
{
printf("%c",ch);
}
fclose(fp);
}

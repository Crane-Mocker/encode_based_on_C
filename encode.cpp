/***************************
coder:Crane_Mocker
the last changed time:2019-5-22
function:opt based on C
        input plaintext,get cipher,print pher ciand ciphertext
theory:E(x) = ((x1 + k1)%NUM,(x2 + k2)%NUM,...(xn + kn)%NUM)
    D(x) = ((x1 - k1)%NUM,(x2 - k2)%NUM,...(xn - kn)%NUM)
******************************/
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<iostream>

#define MAX 100000
#define NUM 93
#define FIRST 33
#define LAST 126

using namespace std;

/******************************
function:judge if the char can be encoded
parameter:a,the char to be judged
function exits:char is in the range of ascii,return true
        else, return false
***************************/
bool suitable_char(char a)
{
  if(a>='!'&&a<='~')
    return true;
  else
    return false;
}

/****************************
function:judge if the plaintext can be encoded
parameter:str,the plaintext
    n, the length of str
function exits:if there is a char in the string is out of the
    range of ascii when going through chars in the str,return false
    else return true
***********************************/
bool suitable_string(char str[],int n)
{
  int i;
  for(i=0;i<n;i++)
    if(!suitable_char(str[i]))return false;
  return true;
}

/*************************
function: get otp cipher according to plaintext
parameter:str,plaintext
    n, the length of plaintext
    key, to store the cipher
function exits:if the plaintext can have a cipher, return true
        else,return false
*****************************/
bool OTPKey(char str[],int n,int key[])//get opt cipher
{
  int i;
  if(suitable_string(str,n))
  {
    srand(static_cast<unsigned int>(time(NULL)));//set seed
    for(i=0;i<n;i++)
      key[i]=FIRST+rand()%NUM;//33~126
    printf("cipher:\n");
    for(i=0;i<n;i++)
      printf("%c",key[i]);
    printf("\n");
    return true;
  }
  else return false;
}

/***********************
function:encode
parameter:str,plaintext
function exits:if the plaintext can be encoded, return true
        else,return false
theory:E(x) = ((x1 + k1)%NUM,(x2 + k2)%NUM,...(xn + kn)%NUM)
************************/
bool OTPEncode(char str[])
{
  int key[MAX];
  int str_len=strlen(str),i;
  if(!OTPKey(str,str_len,key)) return false;
  //OTPKey(str,str_len,key);
  printf("ciphertext:\n");
  for(i=0;i<str_len;i++)
    printf("%c",FIRST+(str[i]+key[i]-2*FIRST)%NUM);
  printf("\n");
  return true;
}

/******************
function:decode
parameter:str,ciphertext
    key,cipher
function exits:if the lengths are not the same, return false
        else retu true
theory:D(x) = ((x1 - k1)%NUM,(x2 - k2)%NUM,...(xn - kn)%NUM)
********************/
bool OTPDecode(char str[],char key[])
{
  int str_len = strlen(str),key_len = strlen(key),i,temp;
  if(str_len!=key_len)return false;
  printf("plaintext:\n");
  for(i=0;i<str_len;i++)
    {
      temp=str[i]-key[i];
      if(temp<0)temp+=NUM;
      printf("%c",FIRST+temp%NUM);
    }
  printf("\n");
  return true;
}

/*********************
function:print the list
no parameter
function exits:input 1,return true
        input 2,return false
***********************/
bool dispList()
{
  int a;
  do {
    std::cout << "please choose one option:" << '\n';
    std::cout << "1.encode" << '\t' << "2.decode" << '\n';
    std::cin >> a;
    if(a==1)return true;
    else if(a==2)return false;
    else std::cout << "please choose from 1 or 2" << '\n';
  } while(a!=1&&a!=2);
}

/***********************
the main
function:call the functions before
*************************/
int main()
{
  char a[MAX],key[MAX];
  if(dispList())
  {
    std::cout << "please input plaintext:" << '\n';
    std::cin >> a;//for g++ doesn't suport gets()
    if(!OTPEncode(a))
      printf("it can't be encoded!\n");
    //else OTPEncode(a);
  }
  else
  {
    std::cout << "please input the ciphertext:" << '\n';
    std::cin >> a;
    std::cout << "please input the cipher:" << '\n';
    std::cin >> key;
    if(!OTPDecode(a,key))
      std::cout << "please check the cipher and the ciphertext" << '\n';
    //else OTPDecode(a,key);
  }
    return 0;
}

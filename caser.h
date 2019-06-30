/***************************
last change time:2019-6-5
function:Caser encode and decode based on C
theory:a=a+k
******************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
char small_letter[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
char big_letter[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };


//judge if the char can be encoded
bool suitable_caser(char a)
{
	if (a >= ' '&&a <= '~')
		return true;
	else
		return false;
}

bool if_caserin(char text[],int *count)
{
	int i,c;
	c = getchar();
	for (*count = 0; ; (*count)++)
	{
		if (c == '\n') break;
		text[*count] = c;
		printf("%c", text[*count]);
		c = getchar();
	}
	printf("\n");

	for (i = 0; i < *count; i++)
		if (!suitable_caser(text[i]))return false;
	return true;
}

bool CaserEncode(char text[],int *k,int count)
{
	int i,j;
	char result[1000];
	printf("need a cipher?\n1.yes 2.no\n");
	scanf("%d", &j);
	if (j == 1)
	{
		srand((unsigned int)time(NULL));
		i = rand() % 26 + 1;
		*k = i;
		printf("your cipher is %d", i);
	}
	else if (j == 2)
	{
		printf("please input your cipher(1~25):");
		scanf("%d", k);
		if (*k < 1 || *k>25)
			return false;
	}

	for (int i = 0; i < count; i++)//can be changed here, to save the space of storing a~z
	{
		if (text[i] >= 'A'&&text[i] <= 'Z')
		{
			result[i] = big_letter[((text[i] - 'A') + *k) % 26];
		}
		else if (text[i] >= 'a'&&text[i] <= 'z')
		{
			result[i] = small_letter[((text[i] - 'a') + *k) % 26];
		}
		else if (text[i] == ' ')
		{
			continue;
		}
		else result[i] = text[i];
		printf("%c", result[i]);
	}

		return true;
}

bool CaserDecode(char text[], int k,int count)
{
	int p;
	char result[1000];
	if (k < 1 || k>25)
		return false;
	for (int i = 0; i < count; i++)
	{
		if (text[i] >= 'A'&&text[i] <= 'Z')
		{
			p = ((text[i] - 'A') - k);
			while (p < 0)p += 26;
			result[i] = big_letter[p];
		}
		else if (text[i] >= 'a'&&text[i] <= 'z')
		{
			p = ((text[i] - 'a') - k);
			while (p < 0)p += 26;
			result[i] = small_letter[p];
		}
		else result[i] = text[i];
		printf("%c", result[i]);
	}
	printf("\n");

	return true;
}

void caser()
{
	char text[1000];
	int function;
	int k,count;

	printf("please input the string you want to encode/decode\n");
	getchar();
	for (;;)
	{
		if (!if_caserin(text,&count))
			printf("sorry there is sth wrong with the char you input\n
                please input again\n");
		else break;
	}

   printf("encode or decode? 1 or 2:");
   scanf("%d",&function);
   if (function == 1)
	   CaserEncode(text,&k,count);
   else if (function == 2)
   {
	   printf("please input cipher");
	   scanf("%d", &k);
	   CaserDecode(text, k, count);
   }
}

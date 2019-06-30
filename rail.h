#include<cstdio>
#include<cstdlib>
#include<ctime>
#define max 200
char result[max];
char result1[max];

bool suitable_rail(char a)
{
	if(a >= ' '&&a <= '~')
		return true;
	else
		return false;
}

bool railin(char letterset[], int *count1)
{
	int i, j, count;
	letterset[1]=getchar();
	for (count = 1;letterset[count]!='\n';)
	{
		if(!suitable_rail(letterset[count]))
			{
               printf("the string can't be encoded\n
                because there is sth wrong with the the char\n");
             return false;
         }
		count++;
		scanf("%c", &letterset[count]);
	}
	count--;
	for (j = 1; j <= count; j++)
		if (letterset[j] >= 33 && letterset[j] <= 126)
		{
			result[(*count1) + 1] = letterset[j];
			(*count1)++;
		}
	for (j = 1; j <= *count1; j++)
		letterset[j] = result[j];

	return true;
}

bool railEncode(char letterset[], int *k, int count1)
{
	int i, j, p, q;
	int d = 0;
	printf("need a cipher given by the system?\n1.yes 2.no\n");
	scanf("%d", &p);
	if (p == 1)
	{
		srand((unsigned int)time(NULL)); random:
	q = rand() % (count1 - 2) + 2;
	if (count1%q != 0)
		goto random;
	*k = q;
	printf("your cipher is:%d", q);
	}
	else if (p == 2)
	{
		printf("please input your cipher:\n");
		do
		{
			scanf("%d", k);
		} while (count1%*k != 0);
		if (*k < 1 || *k>25)
			return false;
	}
	for (i = 1; i <= *k; i++)
		for (j = i; j <= count1; j += *k)
		{
			result1[d + 1] = letterset[j];
			d++;
		}
	printf("the ciphertext:\n");
	for (i = 1; i <= count1; i++)
	{
		printf("%c", result1[i]);
	}

	return true;
}

bool railDecode(char letterset[], int k, int count1)
{
	int m, i, j;
	if (k < 1 || k>25)
		return false;
	printf("the plaintext:\n");
	m = count1 / k;
	for (i = 1; i <= m; i++)
	{
		for (j = i; j <= count1; )
		{
			printf("%c", letterset[j]);
			j += m;
		}
	}
	printf("\n");

	return true;
}

void rail()
{
	char letterset[max] = { 0 };
	int k, count1 = 0;
	int judge;

	printf("encode or decode? 1.encode 2.decode\n");
	scanf("%d", &judge);

	printf("please input the string you want to encode/decode");
	railin(letterset,&count1);
	while(!railin(letterset,&count1));

	if (judge == 1)
		railEncode(letterset, &k, count1);
	else if(judge==2)
	{
		printf("please input your cipher");
		scanf("%d", &k);
		railDecode(letterset, k, count1);
	}
}

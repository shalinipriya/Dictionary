/*Hashing using open addressing*/
/*Input from file words.txt and meanings.txt*/
/*Data structures used : dynamically allocated array*/
/*Functionality : double hashing*/
/*Output : Search Result and delete operation*/


#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include"math.h"
#define N 5000

int count=0,k=0;
int m_array[9]={53,97,193,389,769,1543,3079,6151,12289};
int m;
struct hash
{
	char word[20];
	char meaning[200];
	int del;
}*array,*array1;

/*hashing function*/
unsigned long int h1(char *c)
{

	int len,i;
	unsigned long int h=0;

	len=strlen(c);

	for(i=len-1;i>=0;i--)
		h=h*5+c[i];

	return(h);
}






/**/

void insert(char *c,char *c1)
{
	int b,d,i=0;
	unsigned long int a;

	a=h1(c);

	b=a%m;
	a=1+(a%(m-1));
	
	while(i!=m)		
	{
		d=(b+i*a)%m;

		if(strcmp(array[d].word,"")==0)		//found empty slot
		{
			strcpy(array[d].word,c);
			strcpy(array[d].meaning,c1);
			array[d].del=0;		
			return;		
		}
		i++;
	}
	printf("\nHash table overflow!");
}


/**/

char* search(char *word)
{
	int b,c,i=0,found=1;
	unsigned long int a;
	
	a=h1(word);

	b=a%m;
	a=1+(a%(m-1));

	c=b%m;
	while(i<=m)		
	{
		if(strlen(array[c].word)==0&&array[c].del==0) break;
		c=(b+i*a)%m;

		if(strcmp(array[c].word,word)==0)		
		{
			return array[c].meaning;		

		}
		i++;
	}
	printf("\nnot found");
	return(NULL);
}


void deleteword(char *word)
{
	int b,c,i=0,found=1;
	unsigned long int a;
	
	a=h1(word);

	b=a%m;
	a=1+(a%(m-1));

	c=b%m;
	while(i<=m)		
	{
		if(strlen(array[c].word)==0&&array[c].del==0) break;
		c=(b+i*a)%m;

		if(strcmp(array[c].word,word)==0)		
		{
			strcpy(array[c].meaning,"");
			strcpy(array[c].word,"");
			array[c].del=1;		
		}
		i++;
	}

	
}


/*to resize the hash table when load factor >0.75)*/
void rehash()
{
	int old_m,i,key,j;
	char meaning[100],word[20];

	array1=new struct hash[m];

	old_m=m;
	m=m_array[k];
	k++;

	for(i=0;i<old_m;i++)
	{
		strcpy(array1[i].word,array[i].word);
		strcpy(array1[i].meaning,array[i].meaning);
	}
	delete(array);
	array=new struct hash[m];

	for(i=0;i<m;i++)
	{
		strcpy(array[i].word,"");
		strcpy(array[i].meaning,"");

	}

	
	for(i=0;i<old_m;i++)
	{
		if(strlen(array1[i].word)!=0)
		{
			insert(array1[i].word,array1[i].meaning);
		}

	}
	delete(array1);	
}


int main()
{
	int i,j=0;
	char word[20],*ptr,word1[200],ch;
	float alpha;
	FILE *fp1,*fp2;
	
	m=m_array[k];
	k++;		

	fp1=fopen("words.txt","r");
	if(fp1==NULL) printf("\nError open file");	
	fp2=fopen("meanings.txt","r");
	if(fp2==NULL) printf("\nError open file");

	array=new struct hash[m];

	for(i=0;i<m;i++)
	{
		strcpy(array[i].word,"");
		array[i].del=0;
	}


	for(i=0;i<N;i++)	
	{
		j=0;

		fscanf(fp1,"%s",word);
		ch=fgetc(fp2);		

		while(ch!='\n')
		{
			word1[j]=ch;
			j++;

			ch=fgetc(fp2);

		}
		word1[j]='\0';
		insert(word,word1);

		count++;

		alpha=(float)count/m;

		if(alpha>=0.75)
			rehash();
	}

	fclose(fp1);
	fclose(fp2);
	
	int choice=0;
	while(1)
	{
		printf("\nEnter 1:Search 2:Delete 3:Insert 4:exit\n");
		scanf("%d",&choice);
		if(choice==4) break;
		
		
		if(choice==1)
		{	
			printf("\nEnter the word whose meaning to be found\n");
			scanf("%s",word);
		
			ptr=search(word);
			if(ptr!=NULL)
				printf("\nMeaning : %s",ptr);
		}
		else if(choice==2)
		{
			printf("\nEnter the word to be deleted\n");
			scanf("%s",word);
		
			deleteword(word);
	
		}
		else if(choice==3)
		{
			printf("\nEnter the word");
			scanf("%s",word);
			printf("\nEnter the meaning");
			gets(word1);
			gets(word1);			
			insert(word,word1);

			count++;

			alpha=(float)count/m;

			if(alpha>=0.75)
				rehash();
		}
	}	

}



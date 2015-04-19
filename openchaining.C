/*Hashing using open chaining*/
/*Input from file words.txt and meanings.txt*/
/*Data structures used : dynamically allocated array*/
/*Functionality : double hashing*/
/*Output : Search Result and delete operation*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define n 5000

int m;
int maxLength=10;
int flag=0;
int num=0;
int prime[9]={53,97,193,389,769,1543,3079,6151,12289};
int primeNext;

struct node{
	char word[20];
	char meaning[200];
	struct node *next;
	}*table,*temp_table,*curr,*temp;
int *size;

//creation of a node
void createnode()
{
temp=(struct node *)malloc(sizeof(struct node));
temp->next=NULL;
} 

//hash function
int hashing(char *c)
{
	int hash;
	int len,i;
	unsigned long int h=0;

	len=strlen(c);

	for(i=len-1;i>=0;i--)
		h=h*5+c[i];

	hash=h%m;
	return(hash);
}


//insertion
void hash_insert(int hash,char *word,char *meaning)
{
	if((strcmp(table[hash].word,"")==0)&&table[hash].next==NULL)
		{		
		strcpy(table[hash].word,word);
		strcpy(table[hash].meaning,meaning);
		}
	else
		{		createnode();
		strcpy(temp->word,"");		strcpy(temp->meaning,"");		strcpy(temp->word,table[hash].word);		strcpy(temp->meaning,table[hash].meaning);		temp->next=table[hash].next;
		
		strcpy(table[hash].word,"");
		strcpy(table[hash].meaning,"");
		strcpy(table[hash].word,word);		strcpy(table[hash].meaning,meaning);
		table[hash].next=temp;
		}
	return;
}


//searching
void hash_search(int hash,char *word)
{
	int i=0,j=0;
	curr=&table[hash];
	while(curr!=NULL)
		{
			i++;
			if(strcmp(curr->word,word)==0)
				{
				printf("\nMeaning : ");
				puts(curr->meaning);	
				//printf("found at position %d ",i);
				return;
				}
			curr=curr->next;
		}
	printf("\nNot found");
}

/*deletion*/
void hash_delete(int hash,char *word)
{
	int i=0,j=0;
	curr=&table[hash];
	struct node *prev,*x;
	prev=curr;
	if(strcmp(curr->word,word)==0)	
	{	
		x=curr->next;
		strcpy(curr->word,(curr->next)->word);
		strcpy(curr->meaning,(curr->next)->meaning);
		curr->next=(curr->next)->next;
		free(x);
		
	}
	while(curr!=NULL)
	{
		i++;
		if(strcmp(curr->word,word)==0)
		{
				
			prev->next=curr->next;
			free(curr);
			return;				
		}
		prev=curr;
		curr=curr->next;
	}
	printf("\nNot found");
}


//to resize the hash table when rehasing is required
void initialize()
{
	int i;
	primeNext++;
	m=prime[primeNext];
	free(table);
	free(size);
	table=new struct node[m];
	size=new int[m];
	for(i=0;i<m;i++)
	{
		size[i]=0;
		strcpy(table[i].word,"");
		strcpy(table[i].meaning,"");
		table[i].next=NULL;
	}	
	
}

/*Free linked list created at every slot*/		
void free_table()
{
	int i;
	for(i=0;i<m;i++)
	{
		curr=table[i].next;
		while(curr!=NULL)
		{
			temp=curr;
			curr=curr->next;
			free(temp);
		}
	}		
}

/*to copy into a temporary table before resizing*/
void copyIntoTempTable(char *word,char *meaning)
{
	int i,count=0;
	temp_table=new struct node[num];
	for(i=0;i<m;i++)
	{
		if(strcmp(table[i].word,"")!=0)
		{
			strcpy(temp_table[count].word,table[i].word);
			strcpy(temp_table[count].meaning,table[i].meaning);
			count++;
			curr=table[i].next;
			while(curr!=NULL)
			{
				strcpy(temp_table[count].word,curr->word);
				strcpy(temp_table[count].meaning,curr->meaning);		
				curr=curr->next;
				count++;			
			}
		}
	}
	strcpy(temp_table[count].word,word);
	strcpy(temp_table[count].meaning,meaning);
}


/*to rehash the contents from temporary table into new hash table*/
void initial_rehashing()
{
	int i,hash;
	while(1)
	{
		for(i=0;i<num;i++)
		{
			hash=hashing(temp_table[i].word);
			size[hash]++;
			if(size[hash]<=maxLength)
				hash_insert(hash,temp_table[i].word,temp_table[i].meaning);
			else
			{
				free_table();
				initialize();
			
				break;
			}
		}
		if(i==num)
		return;
	}	
}			


int main()
{
	int hash,i,j;
	char word[20],word1[200],ch;
	FILE *fp1;
	FILE *fp2;
	m=53;
	primeNext=1;
	table=new struct node[m];
	size=new int[m];
	
	//initializing 
	for(i=0;i<m;i++)
	{
		size[i]=0;
		strcpy(table[i].word,"");
		strcpy(table[i].meaning,"");
		table[i].next=NULL;
	}	
		
	//intake of words
	
	fp1=fopen("words.txt","r");
	if(fp1==NULL) printf("\nError open file");
	fp2=fopen("meanings.txt","r");
	if(fp2==NULL) printf("\nError open file");
	
	while(1)
	{
		if(temp_table!=NULL)
			initial_rehashing();
			
		strcpy(word,"");
		strcpy(word1,"");
		
			for(i=num;i<n;i++)
			{					//intake of words and meanings
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
				num++;

				hash=hashing(word);

				size[hash]++;

				if(size[hash]<=maxLength)
				{
					hash_insert(hash,word,word1);
					strcpy(word,"");
					strcpy(word1,"");
				}
					else	
				{
					copyIntoTempTable(word,word1);
					free_table();					
					initialize();
					break;
				}
			}
			if(i==n)
				break;	
			if(m==12289)
			{
				printf("Maxlength cannot be maintained");
				exit(1);
			}
	}
	
	fclose(fp1);
	fclose(fp2);	
	printf("\n The no. of slots (m) chosen is %d",m);
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
	
			hash=hashing(word);
			hash_search(hash,word);
		}
		else if(choice==2)
		{
			printf("\nEnter the word which has to be deleted\n");
			scanf("%s",word);
	
			hash=hashing(word);
			hash_delete(hash,word);
	
		}
		else if(choice==3)
		{
			
			printf("\nEnter the word\n");
			scanf("%s",word);
			printf("\nEnter the meaning\n");
			gets(word1);
			gets(word1);			
			
			hash=hashing(word);

				size[hash]++;

				if(size[hash]<=maxLength)
				{
					hash_insert(hash,word,word1);
					strcpy(word,"");
					strcpy(word1,"");
				}
					else	
				{
					copyIntoTempTable(word,word1);
					free_table();					
					initialize();
					initial_rehashing();
			
				}
		
		}		
	}
	free_table();
	delete(table);
}



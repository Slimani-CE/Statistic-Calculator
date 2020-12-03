#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct statistic 
{
	int length ;
	float *input_xi;
	float *input_ni;
	float N , Xbar , variance ;
	float *XiNi_table;
	float *Ni_table;
	float *Pi_table;
	float *fi_table;
	float *table_1;// |xi-Xbar|
	float *table_2;// ni*|xi-Xbar|
	float *table_3;// ni*(xi-Xbar)^2
	int *mode_table , mode_nb ;
};
typedef struct statistic STATISTIC ;
void print_ligne(char *ligne_name , float *table ,int length , int cur_value , char *next ,char symbole)
{
	//cur_value is the current length of table
	//next is a string printed instead of value of the blank cases
	int i ;
	for(i=0;i<length*14+19;i++)
		printf("#");
	printf("\n");
	printf("# %14s  #",ligne_name);
	for(i=0;i<cur_value;i++)
		printf(" %10.4f%c #",table[i],(symbole)? symbole:' ');
	for(i=cur_value;i<length;i++)
		printf("             #");
	printf("\n");
	for(i=0;i<length*14+19;i++)
		printf("#");
	printf("\n");
}

void check_mode(STATISTIC *f_user)
{
	f_user->mode_nb=0;
	int j=0 , temp=0;
	f_user->mode_table[j]=temp;
	for(int i=0;i<f_user->length;i++)
	{
		if(f_user->input_ni[temp]<f_user->input_ni[i])
		{
			j=0;
			temp=i;
			f_user->mode_table[j]=temp;
		}
		if(f_user->input_ni[temp]==f_user->input_ni[i] && temp!=i)
			f_user->mode_table[++j]=i;
	}
	f_user->mode_nb=j;
}

int main()
{
	// freopen("input.txt","r",stdin);
	system("cls");
	STATISTIC user ;
	printf("Donner moi le nombre des cases du tableux: ");
	scanf("%d",&user.length);
	system("cls");
	user.mode_table=(int*)malloc(user.length*sizeof(int));
	user.input_xi=(float*)malloc(user.length*sizeof(float));
	user.input_ni=(float*)malloc((user.length+2)*sizeof(float));
	user.N=0 ; user.Xbar=0 ;
	user.XiNi_table=(float*)malloc((user.length+2)*sizeof(float));
	user.Ni_table=(float*)malloc(user.length*sizeof(float));
	user.Pi_table=(float*)malloc((user.length+2)*sizeof(float));
	user.fi_table=(float*)malloc((user.length+2)*sizeof(float));
	user.table_1=(float*)malloc((user.length+2)*sizeof(float));// |xi-Xbar|
	user.table_2=(float*)malloc((user.length+2)*sizeof(float));// ni*|xi-Xbar|
	user.table_3=(float*)malloc((user.length+2)*sizeof(float));// ni*(xi-Xbar)^2
	for(int i=0;i<user.length;i++)
	{
		print_ligne("xi",user.input_xi,user.length,i,"           ",' ');
		print_ligne("ni",user.input_ni,user.length,i,"           ",' ');
		printf("Donner moi  x%d: ",i+1);
		scanf("%f",&user.input_xi[i]);
		printf("Donner moi  x%d: ",i+1);
		scanf("%f",&user.input_ni[i]);
		user.N+=user.input_ni[i];
		user.Ni_table[i]=user.N;
		user.XiNi_table[i]=user.input_ni[i]*user.input_xi[i];
		user.Xbar+=user.XiNi_table[i] ;
		system("cls");
	}
	user.input_ni[user.length]=user.N;
	user.XiNi_table[user.length]=user.Xbar;
	user.Xbar/=user.N ;
	user.XiNi_table[user.length+1]=user.Xbar;
	user.table_1[user.length]=0;
	user.table_2[user.length]=0;
	user.table_3[user.length]=0;
	user.fi_table[user.length]=0;
	user.Pi_table[user.length]=0;
	for(int i=0 ; i<user.length ; i++)
	{
		user.table_1[i]=(user.Xbar-user.input_xi[i]>0)? user.Xbar-user.input_xi[i]:-user.Xbar+user.input_xi[i] ;
		user.table_1[user.length]+=user.table_1[i];
		user.table_2[i]=user.table_1[i]*user.input_ni[i];
		user.table_3[i]=user.input_ni[i]*pow(user.table_1[i],2);
		user.table_2[user.length]+=user.table_2[i];
		user.table_3[user.length]+=user.table_3[i];
		user.fi_table[i]=user.input_ni[i]/user.N;
		user.fi_table[user.length]+=user.fi_table[i];
		user.Pi_table[i]=user.fi_table[i]*100;
		user.Pi_table[user.length]+=user.Pi_table[i];
	}

	user.table_1[user.length+1]=user.table_1[user.length]/user.N;
	user.table_2[user.length+1]=user.table_2[user.length]/user.N;
	user.table_3[user.length+1]=user.table_3[user.length]/user.N;
	check_mode(&user);
	system("cls");
	if(user.length<=8)
	{for(int i=0;i<user.length*14+18;i++)
			printf(" ");
		printf("#############################\n");
		for(int i=0;i<user.length*14+18;i++)
			printf(" ");
		printf("#     somme   #   somme/N   #\n");
		for(int i=0;i<user.length*14+18;i++)
			printf(" ");
		printf("#############################\n");}
	print_ligne("xi",user.input_xi,(user.length<=8)? user.length+2:user.length,user.length,"           ",' ');
	print_ligne("ni",user.input_ni,(user.length<=8)? user.length+2:user.length,(user.length<=8)? user.length+1:user.length,"           ",' ');
	print_ligne("Ni",user.Ni_table,(user.length<=8)? user.length+2:user.length,user.length,"           ",' ');
	print_ligne("fi",user.fi_table,(user.length<=8)? user.length+2:user.length,(user.length<=8)? user.length+1:user.length,"           ",' ');
	print_ligne("Pi",user.Pi_table,(user.length<=8)? user.length+2:user.length,(user.length<=8)? user.length+1:user.length,"           ",'%');
	print_ligne("xi*ni",user.XiNi_table,(user.length<=8)? user.length+2:user.length,(user.length<=8)? user.length+2:user.length,"  ",' ');
	print_ligne("|xi-Xbar|",user.table_1,(user.length<=8)? user.length+2:user.length,(user.length<=8)? user.length+2:user.length,"  ",' ');
	print_ligne("ni*|xi-Xbar|",user.table_2,(user.length<=8)? user.length+2:user.length,(user.length<=8)? user.length+2:user.length,"  ",' ');
	print_ligne("ni*(xi-Xbar)^2",user.table_3,(user.length<=8)? user.length+2:user.length,(user.length<=8)? user.length+2:user.length,"  ",' ');
	printf("le nombre des modes de ce tableaux statistique : %d\n",user.mode_nb+1);
	for(int i=0 ;i<=user.mode_nb;i++)
		printf("mode %d: x%d= %f\n",i+1,user.mode_table[i]+1,user.input_xi[user.mode_table[i]]);
	// int answer ;
	// scanf("%d",&answer);
	return 0 ;
}

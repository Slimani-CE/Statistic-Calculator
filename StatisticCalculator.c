#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct statistic 
{
	int length ;
	float *input_xi;
	float *input_ni;
	float N , Xbar , variance  , ecart_type , etendue ;
	float *XiNi_table;
	float *Ni_table;
	float *Pi_table;
	float *fi_table;
	float *table_1;// |xi-Xbar|
	float *table_2;// ni*|xi-Xbar|
	float *table_3;// ni*(xi-Xbar)^2
	int *mode_table , mode_nb , Xmed_nb , *Xmed_table;
};
typedef struct statistic STATISTIC ;
void print_ligne(char *ligne_name , char* file_name, float *table ,int length , int cur_value , char *next ,char symbole)
{
	//cur_value is the current length of table
	//next is a string printed instead of value of the blank cases
	int i ;
	if(!file_name)
	{
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
	else
	{
		FILE *file=fopen(file_name,"a");
		for(i=0;i<length*14+19;i++)
			fprintf(file,"#");
		fprintf(file,"\n");
		fprintf(file,"# %14s  #",ligne_name);
		for(i=0;i<cur_value;i++)
			fprintf(file," %10.4f%c #",table[i],(symbole)? symbole:' ');
		for(i=cur_value;i<length;i++)
			fprintf(file,"             #");
		fprintf(file,"\n");
		for(i=0;i<length*14+19;i++)
			fprintf(file,"#");
		fprintf(file,"\n");
		fclose(file);
	}
}

int scan_int(char *message )
{
	int output ;
	printf("<<: %s\n",message);
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

void check_med(STATISTIC *f_user)
{
	float temp;
	int k=0;
	for(int i=0;i<f_user->length;i++)
	{
		if(f_user->Ni_table[i]>=f_user->N/2)
		{
			if(f_user->N-f_user->Ni_table[i]<=f_user->N/2)
			{	
				f_user->Xmed_table[k++]=i;
				f_user->Xmed_nb=k;
				break;
			}
		}
	}
}

void print_info(char* file_name , STATISTIC *f_user)// if the user wanted to export a file the file_name!=NULL, otherwise it will be, 
{
	//Calculations
	if(!file_name){
		f_user->input_ni[f_user->length]=f_user->N;
		f_user->XiNi_table[f_user->length]=f_user->Xbar;
		f_user->Xbar/=f_user->N ;
		f_user->XiNi_table[f_user->length+1]=f_user->Xbar;
		f_user->table_1[f_user->length]=0;
		f_user->table_2[f_user->length]=0;
		f_user->table_3[f_user->length]=0;
		f_user->fi_table[f_user->length]=0;
		f_user->Pi_table[f_user->length]=0;
		for(int i=0 ; i<f_user->length ; i++)
		{
			f_user->table_1[i]=(f_user->Xbar-f_user->input_xi[i]>0)? f_user->Xbar-f_user->input_xi[i]:-f_user->Xbar+f_user->input_xi[i] ;
			f_user->table_1[f_user->length]+=f_user->table_1[i];
			f_user->table_2[i]=f_user->table_1[i]*f_user->input_ni[i];
			f_user->table_3[i]=f_user->input_ni[i]*pow(f_user->table_1[i],2);
			f_user->table_2[f_user->length]+=f_user->table_2[i];
			f_user->table_3[f_user->length]+=f_user->table_3[i];
			f_user->fi_table[i]=f_user->input_ni[i]/f_user->N;
			f_user->fi_table[f_user->length]+=f_user->fi_table[i];
			f_user->Pi_table[i]=f_user->fi_table[i]*100;
			f_user->Pi_table[f_user->length]+=f_user->Pi_table[i];
		}
		f_user->table_1[f_user->length+1]=f_user->table_1[f_user->length]/f_user->N;
		f_user->table_2[f_user->length+1]=f_user->table_2[f_user->length]/f_user->N;
		f_user->table_3[f_user->length+1]=f_user->table_3[f_user->length]/f_user->N;
		f_user->variance=f_user->table_3[f_user->length+1];
		f_user->ecart_type=sqrt(f_user->variance);
		check_mode(f_user);
		check_med(f_user);
	}


	if(!file_name){system("cls");}
	if(f_user->length<=8 && !file_name)
	{
		for(int i=0;i<f_user->length*14+18;i++)
			printf(" ");
		printf("#############################\n");
		for(int i=0;i<f_user->length*14+18;i++)
			printf(" ");
		printf("#     somme   #   somme/N   #\n");
		for(int i=0;i<f_user->length*14+18;i++)
			printf(" ");
		printf("#############################\n");
	}
	if(f_user->length<=8 && file_name)
	{
		FILE *file=fopen(file_name,"w");
		for(int i=0;i<f_user->length*14+18;i++)
			fprintf(file," ");
		fprintf(file,"#############################\n");
		for(int i=0;i<f_user->length*14+18;i++)
			fprintf(file," ");
		fprintf(file,"#     somme   #   somme/N   #\n");
		for(int i=0;i<f_user->length*14+18;i++)
			fprintf(file," ");
		fprintf(file,"#############################\n");
		fclose(file);
	}
	print_ligne("xi",file_name,f_user->input_xi,(f_user->length<=8)? f_user->length+2:f_user->length,f_user->length,"           ",' ');
	print_ligne("ni",file_name,f_user->input_ni,(f_user->length<=8)? f_user->length+2:f_user->length,(f_user->length<=8)? f_user->length+1:f_user->length,"           ",' ');
	print_ligne("Ni",file_name,f_user->Ni_table,(f_user->length<=8)? f_user->length+2:f_user->length,f_user->length,"           ",' ');
	print_ligne("fi",file_name,f_user->fi_table,(f_user->length<=8)? f_user->length+2:f_user->length,(f_user->length<=8)? f_user->length+1:f_user->length,"           ",' ');
	print_ligne("Pi",file_name,f_user->Pi_table,(f_user->length<=8)? f_user->length+2:f_user->length,(f_user->length<=8)? f_user->length+1:f_user->length,"           ",'%');
	print_ligne("xi*ni",file_name,f_user->XiNi_table,(f_user->length<=8)? f_user->length+2:f_user->length,(f_user->length<=8)? f_user->length+2:f_user->length,"  ",' ');
	print_ligne("|xi-Xbar|",file_name,f_user->table_1,(f_user->length<=8)? f_user->length+2:f_user->length,(f_user->length<=8)? f_user->length+2:f_user->length,"  ",' ');
	print_ligne("ni*|xi-Xbar|",file_name,f_user->table_2,(f_user->length<=8)? f_user->length+2:f_user->length,(f_user->length<=8)? f_user->length+2:f_user->length,"  ",' ');
	print_ligne("ni*(xi-Xbar)^2",file_name,f_user->table_3,(f_user->length<=8)? f_user->length+2:f_user->length,(f_user->length<=8)? f_user->length+2:f_user->length,"  ",' ');
	if(!file_name)
	{
		printf(">>>>> les parametres de position\n");
		printf("le nombre des modes: %d\n",f_user->mode_nb+1);
		for(int i=0 ;i<=f_user->mode_nb;i++)
			printf("mode %d: x%d= %10.4f\n",i+1,f_user->mode_table[i]+1,f_user->input_xi[f_user->mode_table[i]]);
		printf("\nla moyenne arithmetique: Xbar=%10.4f",f_user->Xbar);
		printf("\nla mediane :             x%d = %10.4f\n\n",f_user->Xmed_table[0]+1,f_user->input_xi[f_user->Xmed_table[0]]);
		printf(">>>>> les parametres de dispertion\n\n");
		printf("La variance:      V(x)= %10.4f\n",f_user->variance);
		printf("Ecart type moyen: E(x)= %10.4f\n",f_user->table_2[f_user->length+1]);
		printf("Ecart type:       e(x)= %10.4f\n",f_user->ecart_type);
		printf("Etendue:         x%d-x1= %10.4f\n",f_user->length,f_user->input_xi[f_user->length-1]-f_user->input_xi[0]);
	}
	else
	{
		FILE *file=fopen(file_name,"a");
		fprintf(file,">>>>> les parametres de position\n");
		fprintf(file,"le nombre des modes: %d\n",f_user->mode_nb+1);
		for(int i=0 ;i<=f_user->mode_nb;i++)
			fprintf(file,"mode %d: x%d= %10.4f\n",i+1,f_user->mode_table[i]+1,f_user->input_xi[f_user->mode_table[i]]);
		fprintf(file,"\nla moyenne arithmetique: Xbar=%10.4f",f_user->Xbar);
		fprintf(file,"\nla mediane :             x%d = %10.4f\n\n",f_user->Xmed_table[0]+1,f_user->input_xi[f_user->Xmed_table[0]]);
		fprintf(file,">>>>> les parametres de dispertion\n\n");
		fprintf(file,"La variance:      V(x)= %10.4f\n",f_user->variance);
		fprintf(file,"Ecart type moyen: E(x)= %10.4f\n",f_user->table_2[f_user->length+1]);
		fprintf(file,"Ecart type:       e(x)= %10.4f\n",f_user->ecart_type);
		fprintf(file,"Etendue:         x%d-x1= %10.4f\n",f_user->length,f_user->input_xi[f_user->length-1]-f_user->input_xi[0]);
		fclose(file);
	}
	
}

int main()
{
	system("cls");
	STATISTIC user ;
	// freopen("input.txt","r",stdin);
	system("cls");
	printf("Donner moi le nombre des cases du tableau: ");
	scanf("%d",&user.length);
	while(user.length<=0)
	{
		system("cls");
		printf("Donner moi le nombre des cases du tableau:");
		scanf("%d",&user.length);
	}

	user.Xmed_table=(int*)malloc(user.length*sizeof(int));
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
		print_ligne("xi",NULL,user.input_xi,user.length,i,"           ",' ');
		print_ligne("ni",NULL,user.input_ni,user.length,i,"           ",' ');
		printf("Donner moi  x%d: ",i+1);
		scanf("%f",&user.input_xi[i]);
		printf("Donner moi  n%d: ",i+1);
		scanf("%f",&user.input_ni[i]);
		user.N+=user.input_ni[i];
		user.Ni_table[i]=user.N;
		user.XiNi_table[i]=user.input_ni[i]*user.input_xi[i];
		user.Xbar+=user.XiNi_table[i] ;
		system("cls");
	}
	print_info(NULL,&user);
	int answer ;
	printf("1: reessayer\n2: Exporter une copie!\n3: Sortie\nentrez la reponse:");
	scanf("%d",&answer);
	while(answer!=1 && answer!=2 && answer!=3)
	{
		printf("1: reessayer\n2: Exporter une copie!\n3: Sortie\nentrez la reponse:");
		scanf("%d",&answer);
	}
	switch(answer)
	{
		case 1 : 
		{
			main();break;
		}
		case 2 : 
		{

			print_info("output.dat",&user);
			printf("\n>>> les resultats de votre tableau sont disponible sur le fichier \"output.dat\"\n");
			printf("1: reessayer\n2: Sortie\nentrez la reponse:");
			scanf("%d",&answer);
			while(answer!=1 && answer!=2 )
			{
				printf("1: reessayer\n2: Sortie\nentrez la reponse:");
				scanf("%d",&answer);
			}
			if (answer-1)
			{
				exit(1);
			}
			else main();
			break ;
		}
		case 3 : exit(1);
	}
	return 0 ;
}
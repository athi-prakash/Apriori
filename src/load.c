#include "diggers.h"
//READ THE COLUMN NAMES
char ** load_headers(FILE *fp)
{
	char c,**headers;
	int i,flag1;

	flag1=0;
	i=0;
    
	headers = (char **) malloc(1 * sizeof(char * ));
	headers[g_column_count] = (char * ) malloc(sizeof(char));
	while ((c = getc(fp)) != EOF)
	{
//END OF LINE BREAK
		if (c=='\n' && flag1==1)
		{
			i++;
			headers[g_column_count] = (char * ) realloc(headers[g_column_count],(i+1) * sizeof(char));
			headers[g_column_count][i]='\0';
			g_column_count++;
			break;
		}
		else if (c=='\n' && flag1==0)
		{
			break;
		}
//END OF WORD
		else if (c==' ' && flag1==1)
		{
			i++;
			headers[g_column_count] = (char * ) realloc(headers[g_column_count],(i+1) * sizeof(char));
			headers[g_column_count][i]='\0';
			flag1=0;
			i=0;
			g_column_count++;
		}
//WORD
		else if (c!=' ' && flag1==0)
		{
			flag1=1;
			headers = (char **) realloc(headers, (g_column_count + 1) * sizeof(char * ));
			headers[g_column_count] = (char * ) malloc(sizeof(char));
			headers[g_column_count][i]=c;
		}
		else if (c!=' ' && c!='\n')
		{
			i++;
			headers[g_column_count] = (char * ) realloc(headers[g_column_count],(i+1) * sizeof(char));
			headers[g_column_count][i]=c;
		}
	}
	return headers;
}
//READ ALL RECORDS
void load_records(FILE *fp,char **headers)
{
    char str[50];
	int i,j,flag1;
	
	g_words = (char **) malloc(1 * sizeof(char * ));
	g_headers = (char **) malloc(1 * sizeof(char * ));
    if (g_words == NULL)
	{
		perror("Error in memory allocation.\n");
		exit(EXIT_FAILURE);
    }
    g_index = (int *) malloc(sizeof(int));
    g_lines = (char ***) malloc(1 * sizeof(char ** ));
    if (g_lines == NULL)
	{
		perror("Error in memory allocation.\n");
		exit(EXIT_FAILURE);
    }
	i=0;
	g_line_count=-1;
//Read word by word 
    while (fscanf(fp, "%s", str) != EOF) 
	{
		if (i%g_column_count==0)
		{
			g_line_count++;
			g_lines = (char ***) realloc(g_lines,(g_line_count+1) * sizeof(char ** ));
			if (g_lines == NULL) 
			{
				perror("Error in memory allocation.\n");
				exit(EXIT_FAILURE);
			}
			g_lines[g_line_count] = (char **) malloc(g_column_count * sizeof(char * ));
			if (g_lines[g_line_count] == NULL) 
			{
				perror("Error in memory allocation.\n");
				exit(EXIT_FAILURE);
			}
		}
		g_lines[g_line_count][i%g_column_count]= (char *) malloc(strlen(str) * sizeof(char));
		if (g_lines[g_line_count][i%g_column_count] == NULL)
		{
			perror("Error in memory allocation.\n");
			exit(EXIT_FAILURE);
		}
		strcpy(g_lines[g_line_count][i%g_column_count], str);
		i++;
//CHECK FOR REPEATED WORDS
		flag1 = 0;
		for (j = 0; j < g_word_count; j++)
		{
			if (strcmp(str, g_words[j]) == 0)
			{
				flag1 = 1;
				break;
			}
		}
		if (flag1 == 1)
		{
			continue;
		}
//STORE NEW WORDS AND CREATE INDEX
		g_words = (char **) realloc(g_words, (g_word_count + 1) * sizeof(char * ));
		g_headers = (char **) realloc(g_headers, (g_word_count + 1) * sizeof(char * ));
		if (g_words == NULL)
		{
			perror("Error in memory allocation.\n");
			exit(EXIT_FAILURE);
		}
		g_words[g_word_count] = (char * ) malloc(strlen(str) * sizeof(char));
		g_headers[g_word_count] = (char * ) malloc(strlen(headers[(i-1)%g_column_count]) * sizeof(char));
		g_index = (int *) realloc(g_index,(g_word_count + 1) * sizeof(int));
		if (g_words[g_word_count] == NULL)
		{
			perror("Error in memory allocation.\n");
			exit(EXIT_FAILURE);
		}
		strcpy(g_words[g_word_count],str);
		strcpy(g_headers[g_word_count],headers[(i-1)%g_column_count]);
		g_index[g_word_count]=(i-1)%g_column_count;
		g_word_count++;
	}
}
//INPUT FILE READING
void load()
{
	char ip_file[200],**headers;
	FILE *fp;
	int i;

	printf("Enter the input file name:");
    scanf("%s",ip_file);
	gettimeofday(&start,NULL);
	fp = fopen(ip_file, "r");

    if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
    }
	
	headers=load_headers(fp);
	load_records(fp,headers);
	for (i = 0; i < g_column_count; i++)
	{
		free(headers[i]);
	}
	free(headers);
	fclose(fp);
	gettimeofday(&end,NULL);
}

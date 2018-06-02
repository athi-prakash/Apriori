#include "diggers.h"

//GLOBAL VARIABLES DEFINITION
sup_struct2 *g_freq;
int g_level_count;
char **g_words;
char **g_headers;
int *g_index;
int g_word_count = 0;
char ***g_lines;
int g_line_count = 0;
int g_column_count = 0;
int g_rule_count = 0;
float g_sup,g_conf;

struct timeval start;
struct timeval end;

int main ()
{
	float in_time,gen_time,out_time;
//INPUT & FILE READING
	load();
	in_time=(float)(((end.tv_sec-start.tv_sec)*1000000)+(end.tv_usec-start.tv_usec))/1000;
	printf("NOTE:\n");
	printf("\t*Inputs are in percentage*\n");
	printf("\t*Accepts numeric values ranging 0.01 to 100.00*\n");
    printf("\nEnter the support rate:");
    scanf("%f",&g_sup);	
	g_sup=roundf(g_sup*100)/100;
	if (g_sup>100 | g_sup<=0)
	{
        perror("Invalid percentange or zero.\n");
        exit(EXIT_FAILURE);
	}
    printf("Enter the confidence rate:");
    scanf("%f",&g_conf);
    g_conf=roundf(g_conf*100)/100;
	if (g_conf>100 | g_conf<=0)
	{
        perror("Invalid percentange or zero.\n");
        exit(EXIT_FAILURE);
	}
//ALGORITHM EXECUTION & POPULATE DATA STRUCTURE
	gettimeofday(&start,NULL);
	lvl_1_gen();
	lvl_n_gen();
	lvl_1_rule();
	gettimeofday(&end,NULL);
	gen_time=(float)(((end.tv_sec-start.tv_sec)*1000000)+(end.tv_usec-start.tv_usec))/1000;
//EXTRACT OUTPUT FROM DATA STRUCTURE
	gettimeofday(&start,NULL);
	extract ();
	gettimeofday(&end,NULL);
	out_time=(float)(((end.tv_sec-start.tv_sec)*1000000)+(end.tv_usec-start.tv_usec))/1000;
	printf("----------------------------------------------------------------\n");
	printf("Statistics\n");
	printf("----------------------------------------------------------------\n");
	printf("Loading Time Taken:%.3f ms\n",in_time);
	printf("Generation Time Taken:%.3f ms\n",gen_time);
	printf("Extraction Time Taken:%.3f ms\n",out_time);
	return 0;
}

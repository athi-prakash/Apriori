//Include libraries
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<math.h>
#include<sys/time.h>

//ITEM
typedef struct Sup_Struct1 {
	int *item;
	float sup;
//RULESET - RECURSIVE USE OF STRUCTURES
	struct Sup_Struct2 *rule;
	int rule_count;
}sup_struct1;

//ITEMSET
typedef struct Sup_Struct2 {
	int level;
	int count;
	sup_struct1 *node;
}sup_struct2;

//GLOBAL VARIABLE DECLARATION
extern sup_struct2 *g_freq;
extern int g_level_count;
extern char **g_words;
extern char **g_headers;
extern int *g_index;
extern int g_word_count;
extern char ***g_lines;
extern int g_line_count;
extern int g_column_count;
extern int g_rule_count;
extern float g_sup,g_conf;
//VARIABLES TO MEASURE PERFORMANCE
extern struct timeval start;
extern struct timeval end;

//FUNCTION DECLARATION
char ** load_headers(FILE *fp);
void load_records(FILE *fp,char **headers);
void load();
void lvl_1_gen ();
void lvl_n_gen ();
int apriori_prune(int *tmp_item,int cur_lvl);
sup_struct2 * lvl_n_rule (sup_struct2 *l_rule,sup_struct1 *parent,int max_level);
void lvl_1_rule();
float find_sup(int *tmp_item,int lvl);
float apriori_prune_rule(int *tmp_item,int cur_lvl,sup_struct2 *l_rule,sup_struct1 *parent,int parent_level);
void print_rule(sup_struct1 *parent,sup_struct1 *right,int parent_size,int right_size,FILE *fp);
void extract ();

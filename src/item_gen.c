#include "diggers.h"
//GENERATE LEVEL 1 FREQUENT ITEMS
void lvl_1_gen ()
{
	int i,j,k,l;

	g_freq = (sup_struct2 * ) malloc(sizeof(sup_struct2));
	g_freq[0].level=1;
	g_freq[0].count=0;
	g_freq[0].node = (sup_struct1 * ) malloc(sizeof(sup_struct1));
	for (i=0;i<g_word_count;i++)
	{
		l=0;
//CHECK FOR FREQUENCY
		for (j=0;j<=g_line_count;j++)
		{
			for (k=0;k<g_column_count;k++ )
			{
				if (strcmp(g_words[i],g_lines[j][k])==0)
				{
					l++;
//Break should be avoided if items are not restricted to a single column.
					break;
				}
			}
		}
		if (g_sup<=(((float)l*100)/(g_line_count+1)))
		{
//ADD FREQUENT ITEM TO DATA STRUCTURE
			g_freq[0].node = (sup_struct1 * ) realloc(g_freq[0].node,(g_freq[0].count+1)*sizeof(sup_struct1));
			g_freq[0].node[g_freq[0].count].item=(int *)malloc(sizeof(int));
			g_freq[0].node[g_freq[0].count].item[0]=i;
			g_freq[0].node[g_freq[0].count].sup=(((float)l*100)/(g_line_count+1));
			g_freq[0].node[g_freq[0].count].rule_count=0;
			g_freq[0].count++;
		}
	}
	g_level_count=1;
}
void lvl_n_gen ()
{
	int i,j,k,l,flag1;
	int *tmp_item;
	float tmp_sup;

	tmp_item=(int *)malloc(sizeof(int));
//LEVEL-WISE LOOP
//Word count should be used if items are not restricted to a single column.
	for (i=1;i<g_column_count;i++)
	{
		g_freq = (sup_struct2 *)realloc(g_freq,(i+1)*sizeof(sup_struct2));
		g_freq[i].count=0;
		g_freq[i].node = (sup_struct1 * ) malloc(sizeof(sup_struct1));
		tmp_item=(int *)realloc(tmp_item,(i+1)*sizeof(int));
//FIRST N-1 ITEM LOOP
		for (j=0;j<g_freq[i-1].count;j++)
		{
//SECOND N-1 ITEM LOOP TO CROSSOVER WITH PREVIOUS LOOP
			for (k=j+1;k<g_freq[i-1].count;k++)
			{
				flag1=0;
//Last position and Attribute type checks
				if (g_freq[i-1].node[j].item[i-1]<g_freq[i-1].node[k].item[i-1] & g_index[g_freq[i-1].node[j].item[i-1]]!=g_index[g_freq[i-1].node[k].item[i-1]])
				{
					tmp_item[i]=g_freq[i-1].node[k].item[i-1];
//ITEM LEVEL CHECK TO MATCH CROSSOVER COMPATABILITY
					for (l=0;l<i-1;l++)
					{
//OTHER THAN LAST POSITION ITEM VALIDATION FOR CROSSOVER
						if (g_freq[i-1].node[j].item[l]!=g_freq[i-1].node[k].item[l] | g_index[g_freq[i-1].node[j].item[l]]==g_index[g_freq[i-1].node[k].item[i-1]])
						{
							flag1=1;
							break;
						}
						tmp_item[l]=g_freq[i-1].node[j].item[l];
					}
					tmp_item[i-1]=g_freq[i-1].node[j].item[i-1];
					if (flag1!=1)
					{
//APRIORI VALIDATION AND FREQUENCY CHECK
						tmp_sup=(((float)apriori_prune(tmp_item,i)*100)/(g_line_count+1));
						if (g_sup<=tmp_sup)
						{
//ADD TO DATA STRUCTURE
							g_freq[i].node = (sup_struct1 * ) realloc(g_freq[i].node,(g_freq[i].count+1)*sizeof(sup_struct1));
							g_freq[i].node[g_freq[i].count].item=(int *)malloc((i+1)*sizeof(int));
							memcpy(g_freq[i].node[g_freq[i].count].item,tmp_item,(i+1)*sizeof(int));
							g_freq[i].node[g_freq[i].count].sup=tmp_sup;
							g_freq[i].node[g_freq[i].count].rule_count=0;
							g_freq[i].count++;
						}
					}
				}
			}
		}
		if (g_freq[i].count==0)
		{
			free(g_freq[i].node);
			g_freq = (sup_struct2 *)realloc(g_freq,(i)*sizeof(sup_struct2));
			break;
		}
		g_level_count++;
		g_freq[i].level=i+1;
	}
	free(tmp_item);
}

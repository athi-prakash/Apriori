#include "diggers.h"
//N ITEM RIGHT SIDE GENERATION
sup_struct2 * lvl_n_rule (sup_struct2 *l_rule,sup_struct1 *parent,int max_level)
{
	int i,j,k,l,flag1;
	int *tmp_item;
	float tmp_sup,tmp_conf;

	tmp_item=(int *)malloc(sizeof(int));
//LOOP FROM 2 TO N RIGHT SIDE RULES
	for (i=1;i<max_level;i++)
	{
		l_rule = (sup_struct2 *)realloc(l_rule,(i+1)*sizeof(sup_struct2));
		l_rule[i].count=0;
		l_rule[i].node = (sup_struct1 * ) malloc(sizeof(sup_struct1));
		tmp_item=(int *)realloc(tmp_item,(i+1)*sizeof(int));
//FIRST LOOP ON N-1 RIGHT SIDE
		for (j=0;j<l_rule[i-1].count;j++)
		{
//SECOND LOOP ON N-1 RIGHT SIDE FOR CROSSOVER
			for (k=j+1;k<l_rule[i-1].count;k++)
			{
				flag1=0;
//LAST POSITION ITEM VALIDATION
				if (l_rule[i-1].node[j].item[i-1]<l_rule[i-1].node[k].item[i-1] & g_index[l_rule[i-1].node[j].item[i-1]]!=g_index[l_rule[i-1].node[k].item[i-1]])
				{
					tmp_item[i]=l_rule[i-1].node[k].item[i-1];
//LOOP ITEM FOR CROSSOVER
					for (l=0;l<i-1;l++)
					{
//OTHER THAN LAST POSITION ITEM VALIDATION FOR CROSSOVER
						if (l_rule[i-1].node[j].item[l]!=l_rule[i-1].node[k].item[l] | g_index[l_rule[i-1].node[j].item[l]]==g_index[l_rule[i-1].node[k].item[i-1]])
						{
							flag1=1;
							break;
						}
						tmp_item[l]=l_rule[i-1].node[j].item[l];
					}
					tmp_item[i-1]=l_rule[i-1].node[j].item[i-1];
					if (flag1!=1)
					{
//APRIORI & CONFIDENCE RATE VALIDATION
						tmp_sup=apriori_prune_rule(tmp_item,i,l_rule,parent,max_level);
						tmp_conf=parent->sup*100/tmp_sup;
						if (g_conf<=tmp_conf)
						{
//ADD TO DATA STRUCTURE
							l_rule[i].node = (sup_struct1 * ) realloc(l_rule[i].node,(l_rule[i].count+1)*sizeof(sup_struct1));
							l_rule[i].node[l_rule[i].count].item=(int *)malloc((i+1)*sizeof(int));
							memcpy(l_rule[i].node[l_rule[i].count].item,tmp_item,(i+1)*sizeof(int));
							l_rule[i].node[l_rule[i].count].sup=tmp_conf;
							l_rule[i].count++;
							g_rule_count++;
						}
					}
				}
			}
		}
		if (l_rule[i].count==0)
		{
			free(l_rule[i].node);
			l_rule = (sup_struct2 *)realloc(l_rule,(i)*sizeof(sup_struct2));
			break;
		}
		parent->rule_count++;
		l_rule[i].level=i+1;
	}
	free(tmp_item);
	return l_rule;
}
//I ITEM RIGHT SIDE GENERATION
void lvl_1_rule()
{
	int i,j,k;
	int *tmp_item;
	float tmp_sup,tmp_conf;

	tmp_item=(int *)malloc(sizeof(int));
//LOOP ON ITEMSET
	for (i=1;i<g_level_count;i++)
	{
		tmp_item=(int *)realloc(tmp_item,i*sizeof(int));
//LOOP ON ITEMS
		for (j=0;j<g_freq[i].count;j++)
		{
			g_freq[i].node[j].rule = (sup_struct2 * ) malloc(sizeof(sup_struct2));
			g_freq[i].node[j].rule[0].count=0;
			g_freq[i].node[j].rule[0].node = (sup_struct1 * ) malloc(sizeof(sup_struct1));
			g_freq[i].node[j].rule_count=1;
//LOOP IN FORM 1 ITEM RIGHT SIDE RULE
			for (k=0;k<=i;k++)
			{
//FORM LEFT SIDE
				memcpy(tmp_item,g_freq[i].node[j].item,(k)*sizeof(int));
				memcpy(&tmp_item[k],&(g_freq[i].node[j].item[k+1]),(i-k)*sizeof(int));
//CONFIDENCE RATE VALIDATION BY FETCHING SUPPORT RATE OF LEFT
				tmp_sup=find_sup(tmp_item,i-1);
				if (tmp_sup == -1)
				{
					perror("Rule generated for unsupported item.\n");
					exit(EXIT_FAILURE);
				}
				tmp_conf=g_freq[i].node[j].sup*100/tmp_sup;
				if (g_conf<=tmp_conf)
				{
//ADD TO DATA STRUCTURE
					g_freq[i].node[j].rule[0].node = (sup_struct1 * ) realloc(g_freq[i].node[j].rule[0].node,(g_freq[0].count+1)*sizeof(sup_struct1));
					g_freq[i].node[j].rule[0].node[g_freq[i].node[j].rule[0].count].item=(int *)malloc(sizeof(int));
					g_freq[i].node[j].rule[0].node[g_freq[i].node[j].rule[0].count].item[0]=g_freq[i].node[j].item[k];
					g_freq[i].node[j].rule[0].node[g_freq[i].node[j].rule[0].count].sup=tmp_conf;
					g_freq[i].node[j].rule[0].count++;
					g_rule_count++;
				}
			}
			if (g_freq[i].node[j].rule[0].count==0)
			{
				free(g_freq[i].node[j].rule[0].node);
				free(g_freq[i].node[j].rule);
				g_freq[i].node[j].rule_count=0;
			}
			else
			{
				g_freq[i].node[j].rule=lvl_n_rule(g_freq[i].node[j].rule,&(g_freq[i].node[j]),i);
			}
		}
	}
	free(tmp_item);
}

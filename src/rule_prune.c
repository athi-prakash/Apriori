#include "diggers.h"

//GET SUPPORT RATE FOR A ITEM IN SPECIFIC LEVEL
float find_sup(int *tmp_item,int lvl)
{
	int i,j;
//LOOP ON ITEMS IN THE LEVEL
	for (i=0;i<g_freq[lvl].count;i++)
	{
//LOOP OF VALUES IN ITEM
		for (j=0;j<=lvl;j++)
		{
//VALIDATE IF LOOP ITEM & SEARCH ITEM MATCHES
			if (tmp_item[j]!=g_freq[lvl].node[i].item[j])
			{
				break;
			}
		}
		if (j>lvl)
		{
			return g_freq[lvl].node[i].sup;
		}
	}
	return -1;
}
//APRIORI VALIDATION ON RULES
float apriori_prune_rule(int *tmp_item,int cur_lvl,sup_struct2 *l_rule,sup_struct1 *parent,int parent_level)
{
	int i,j,k,l,*left_item;
	float sup;
//LOOP ON SUBSET
	for (i=0;i<=cur_lvl;i++)
	{
//LOOP ON N-1 RIGHT SIDE
		for (j=0;j<l_rule[cur_lvl-1].count;j++)
		{
//LOOP ON VALUES IN ITEM
			for (k=0;k<cur_lvl;k++)
			{
//VALIDATE MATCHING ITEMS
				if (tmp_item[k+(int)ceil(((float)(k+1-i))/(k+i+1))]!=l_rule[cur_lvl-1].node[j].item[k])
				{
					break;
				}
			}
			if (k==cur_lvl)
			{
				break;
			}
		}
		if (j==l_rule[cur_lvl-1].count)
		{
			return -1;
		}
	}
//GENERATE LEFT SIDE
	l=0;
	left_item=(int *)malloc((parent_level-cur_lvl)*sizeof(int));
	for (i=0;i<=parent_level;i++)
	{
		k=0;
		for (j=i-l;j<=cur_lvl;j++)
		{
			if (parent->item[i]==tmp_item[j])
			{
				k=1;
				break;
			}
		}
		if (k==0)
		{
			left_item[l]=parent->item[i];
			l++;
			if (l>=parent_level-cur_lvl)
			{
				break;
			}
		}
	}
//FIND SUPPORT RATE OF LEFT
	sup=find_sup(left_item,parent_level-cur_lvl-1);
	free(left_item);
	return sup;
}

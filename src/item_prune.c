//Include libraries
#include "diggers.h"

int apriori_prune(int *tmp_item,int cur_lvl)
{
	int i,j,k,l,flag1;
//LOOP ON SUBSET
	for (i=0;i<=cur_lvl;i++)
	{
//LOOP N-1
		for (j=0;j<g_freq[cur_lvl-1].count;j++)
		{
//LOOP ON ITEM
			for (k=0;k<cur_lvl;k++)
			{
//VALIDATE SUBSET ITEM AGAINST N-1 ITEM
				if (tmp_item[k+(int)ceil(((float)(k+1-i))/(k+i+1))]!=g_freq[cur_lvl-1].node[j].item[k])
				{
					break;
				}
			}
			if (k==cur_lvl)
			{
				break;
			}
		}
		if (j==g_freq[cur_lvl-1].count)
		{
			return 0;
		}
	}
//COUNT OCCURENCE
	l=0;
	for (i=0;i<=g_line_count;i++)
	{
		for (j=0;j<=cur_lvl;j++)
		{
			for (k=0;k<g_column_count;k++ )
			{
				if (strcmp(g_words[tmp_item[j]],g_lines[i][k])==0)
				{
					break;
				}
			}
			if (k==g_column_count)
			{
				break;
			}
		}
		if (j>cur_lvl)
		{
			l++;
		}
	}
	return l;
}

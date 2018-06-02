#include "diggers.h"
//FORM LEFT AND RIGHT SIDE OF RULE
void print_rule(sup_struct1 *parent,sup_struct1 *right,int parent_size,int right_size,FILE *fp)
{
	int i,j,k,l;

	printf("(Support=%.2f, Confidence=%.2f)\n{",parent->sup,right->sup);
	fprintf(fp,"(Support=%.2f, Confidence=%.2f)\n{",parent->sup,right->sup);
	l=0;
//LOOP ON PARENT
	for (i=0;i<=parent_size;i++)
	{
		k=0;
//LOOP ON RIGHT
		for (j=i-l;j<=right_size;j++)
		{
			if (parent->item[i]==right->item[j])
			{
				k=1;
				break;
			}
		}
//PRINT DIFFERENCE
		if (k==0)
		{
			printf("%s=%s",g_headers[parent->item[i]],g_words[parent->item[i]]);
			fprintf(fp,"%s=%s",g_headers[parent->item[i]],g_words[parent->item[i]]);
			l++;
			if (l>=parent_size-right_size)
			{
				break;
			}
			printf(", ");
			fprintf(fp,", ");
		}
	}
	printf("} ---> {");
	fprintf(fp,"} ---> {");
//PRINT RIGHT
	for (i=0;i<=right_size;i++)
	{
		printf("%s=%s",g_headers[right->item[i]],g_words[right->item[i]]);
		fprintf(fp,"%s=%s",g_headers[right->item[i]],g_words[right->item[i]]);
		if (i<right_size)
		{
			printf(", ");
			fprintf(fp,", ");
		}
	}
	printf("}\n");
	fprintf(fp,"}\n");
}
//PRINT OUTPUT TO FILE AND SCREEN
void extract ()
{
	int i,j,k,l,x;
	FILE *fp;
//PRINT HEADER
	fp = fopen("Rules", "w");
	printf("\n\n\nSummary:\n");
	printf("Total rows in the original set: %d\n",g_line_count+1);
	printf("Total rules discovered: %d\n",g_rule_count);
	printf("The selected measures: Support=%.2f, Confidence=%.2f\n",g_sup,g_conf);
	printf("------------------------------------------------------\nDiscovered Rules:\n\n");
	fprintf(fp,"Summary:\n");
	fprintf(fp,"Total rows in the original set: %d\n",g_line_count+1);
	fprintf(fp,"Total rules discovered: %d\n",g_rule_count);
	fprintf(fp,"The selected measures: Support=%.2f, Confidence=%.2f\n",g_sup,g_conf);
	fprintf(fp,"------------------------------------------------------\nDiscovered Rules:\n\n");
//LOOP ON ITEMSET
	for (i=0;i<g_level_count;i++)
	{
//LOOP ON ITEM
		for (j=0;j<g_freq[i].count;j++)
		{
//LOOP ON RIGHT SIDE SIZE
			for (k=0;k<g_freq[i].node[j].rule_count;k++)
			{
//LOOP ON RIGHT ITEM FOR EACH SIZE
				for (l=0;l<g_freq[i].node[j].rule[k].count;l++)
				{
					x++;
					printf("Rule#%d:",x);
					fprintf(fp,"Rule#%d:",x);
//CALL TO PRINT RULE
					print_rule(&g_freq[i].node[j],&g_freq[i].node[j].rule[k].node[l],i,k,fp);
					free(g_freq[i].node[j].rule[k].node[l].item);
				}
				free(g_freq[i].node[j].rule[k].node);
			}
			if (g_freq[i].node[j].rule_count>0)
			{
				free(g_freq[i].node[j].rule);
			}
			free(g_freq[i].node[j].item);
		}
		free(g_freq[i].node);
	}
	free(g_freq);
	printf("***The Output is also stored in the Rules file.***\n");
//FREE OTHER DYNAMIC ALLOCATED MEMORY
    for (i = 0; i < g_word_count; i++) {
      free(g_words[i]);
	  free(g_headers[i]);
    }
    free(g_words);
	free(g_index);

    for (i=0;i<=g_line_count;i++) {
		for (j=0;j<g_column_count;j++)
		{
			free(g_lines[i][j]);
		}
		free(g_lines[i]);
    }
    free(g_lines);
}

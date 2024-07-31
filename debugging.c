#include "minishell.h"

void printf_int(int d)
{
	printf("debug >> %d\n", d);
	exit(0);
}
void printf_str(char *s)
{
	printf("debug >> [%s]\n", s);
	exit(0);
}
void print_cmd(t_cmds **cmds)
{
	while (cmds && *cmds)
	{
		printf("cmd       :[%s]\n", (*cmds)->cmd);
		int j = 0;
		while ((*cmds)->args && (*cmds)->args[j])
		{
			printf("args      :[%s]\n", (*cmds)->args[j]);
			j++;
		}
		printf("heredoc   : %d\n", (*cmds)->heredoc);
		printf("out_file  : %d\n", (*cmds)->out_file);
		printf("in_file   : %d\n", (*cmds)->in_file);
		printf("aout_file : %d\n", (*cmds)->aout_file);
		*cmds = (*cmds)->next;
		printf("##########################\n");
	}
	exit(0);
}
void print_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		printf("name : [%s] >>", lexer->str);
		if (lexer->prev)
			printf(" << prev : [%s] >>", lexer->prev->str);
		if (lexer->next)
			printf(" << next : [%s] >>", lexer->next->str);
		printf(" token : %d >> \n", lexer->token);
		lexer = lexer->next;
	}
}
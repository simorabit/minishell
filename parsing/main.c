/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:42:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/06/11 14:56:17 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void printf_int(int d)
{
	printf("debug >> %d\n", d);
	exit(0);
}
void printf_str(char *s)
{
	printf("debug >> %s\n", s);
	exit(0);
}
void print_cmd(t_simple_cmds **cmds)
{
	while (cmds && *cmds)
	{
		printf("cmd       : %s\n", (*cmds)->cmd);
		int j = 0;
		while ((*cmds)->args && (*cmds)->args[j])
		{
			printf("args      : %s\n", (*cmds)->args[j]);
			j++;
		}
		printf("heredoc   : %d\n", (*cmds)->heredoc);
		printf("out_file  : %d\n", (*cmds)->out_file);
		printf("in_file   : %d\n", (*cmds)->in_file);
		printf("aout_file : %d\n", (*cmds)->aout_file);
		*cmds = (*cmds)->next;
		printf("##########################\n");
	}
}
void print_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		printf("name : %s >>", lexer->str);
		if (lexer->prev)
			printf(" << prev : %s >>", lexer->prev->str);
		if (lexer->next)
			printf(" << next : %s >>", lexer->next->str);
		printf(" token : %d >> \n", lexer->token);
		lexer = lexer->next;
	}
}

void handel_input(char *line, t_env **env_list)
{
	t_lexer *lexer;
	char **res;
	t_simple_cmds *cmds;
	
	lexer = NULL;
	cmds = NULL;
	if (!handel_quotes(line))
		return;
	line = add_spaces(line);
	if (!line)
		return;
	res = ft_split(line);
	if (!res)
		return;
	tokenizer(res, &lexer);
	if (!syntax_error(&lexer))
		return;
	handel_expanding(&lexer);
	remove_quotes(&lexer);
	cmds = parser(&lexer, &cmds, get_lcmd(lexer));
	free_lexer(lexer);
	initialize_files(cmds);
	multiple_cmd(*env_list, cmds);
	// print_cmd(&cmds);
}

void parsing(char **env)
{
	char *line;
	t_env		*env_list;

	env_list = get_env(env);
	while (1)
	{
		line = readline(GREEN"minishell\x1b[0m \x1b[31m😎 "RESET);
		if (!line)
			break;
		if (line && *line)
			add_history(line);	
		handel_input(line, &env_list);
		free(line); // be aware of this
	}
}

int main(int arc, char *arv[], char **env)
{
	(void)arv;
	
	if (arc != 1)
	    (printf("InputError"), exit(0));
	parsing(env);
}

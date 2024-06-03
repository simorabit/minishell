/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:42:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/06/03 14:56:30 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	print_cmd(t_simple_cmds **cmds)
{
	int i = 0;
	while (cmds && cmds[i])
	{
		printf("cmd : %s\n",cmds[i]->cmd);
		int j = 0;
		while (cmds[i]->args && cmds[i]->args[j])
		{
			printf("args %s\n", cmds[i]->args[j]);
			j++;
		}
		j = 0;
		while (cmds[i]->in_file && cmds[i]->in_file[j])
		{
			printf("in_file %s\n", cmds[i]->in_file[j]);
			j++;
		}
		j = 0;
		while (cmds[i]->out_file && cmds[i]->out_file[j])
		{
			printf("out_file %s\n", cmds[i]->out_file[j]);
			j++;
		}
		j = 0;
		while (cmds[i]->aout_file && cmds[i]->aout_file[j])
		{
			printf("aout_file %s\n", cmds[i]->aout_file[j]);
			j++;
		}
		j = 0;
		while (cmds[i]->heredoc && cmds[i]->heredoc[j])
		{
			printf("heredoc %s\n", cmds[i]->heredoc[j]);
			j++;
		}
		i++;
		printf("##########################\n");
	}
}
void	print_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		printf("<< name : %s >>", lexer->str);
		if (lexer->prev)
			printf(" << prev : %s >>", lexer->prev->str);
		if (lexer->next)
			printf(" << next : %s >>", lexer->next->str);
		printf(" << token : %d >> \n", lexer->token);
		lexer = lexer->next;
	}
}

void	handel_input(char *line)
{
	t_lexer	*lexer;
	char	**res;
	t_simple_cmds *cmds;
	
	lexer = NULL;
	cmds = NULL;
	if (!handel_quotes(line))
		return;
	line = add_spaces(line);
	if(!line)
		return ;
	res = ft_split(line);
	if (!res)
	{
		free_list(res);
		allocation_error(line);
	}
	tokenizer(res, &lexer);
	if (!syntax_error(&lexer))
		return ;
	handel_expanding(&lexer);
	remove_quotes(&lexer);
	cmds = parser(&lexer, &cmds);
	// print_cmd(&cmds);
}

void	parsing(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		handel_input(line);
		// free(line);
	}
}

int	main(void)
{
    // if(arc == 1)
    //     (printf(InputError), exit(0));
	parsing();
    //syntax error
    // parser(&lexer);
}

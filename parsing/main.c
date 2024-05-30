/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:42:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/30 16:06:08 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	print_cmd(t_simple_cmds *lexer)
{
	t_simple_cmds *cmds;
	int i = 0;
	cmds = lexer;
	while (cmds)
	{
		while (cmds->str[i])
		{
			printf("cmd[%d] %s\n",i, cmds->str[i]);
			i++;
		}
		print_lexer(cmds->redirections);
		cmds = cmds->next;
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
	// parser(&lexer, &cmds);
	print_lexer(lexer);
}
//'"'$USER'"'
//'"'"'$USER'"'"'
//$5sss
//$'USER'
//single quotes cases

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:42:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/27 12:51:47 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO - remove it at end
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

	lexer = NULL;
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
	print_lexer(lexer);
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

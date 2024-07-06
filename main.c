/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:42:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/04 09:54:26 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handel_input(char *line, t_env **env_list)
{
	t_lexer			*lexer;
	char			**res;
	t_simple_cmds	*cmds;

	lexer = NULL;
	cmds = NULL;
	if (!handel_quotes(line))
		return ;
	line = add_spaces(line);
	if (!line)
		return ;
	res = ft_split(line);
	if (!res)
		return ;
	tokenizer(res, &lexer);
	if (!syntax_error(&lexer))
		return ;
	handel_expanding(&lexer);
	remove_quotes(&lexer);
	cmds = parser(&lexer, &cmds, get_lcmd(lexer));
	free_lexer(lexer);
	initialize_files(cmds);
	multiple_cmd(env_list, cmds);
}

void	read_input(char **env)
{
	char	*line;
	t_env	*env_list;

	env_list = get_env(env);
	while (1)
	{
		line = readline(GREEN"minishell\x1b[0m \x1b[31m😎 "RESET);
		if (!line)
			break ;
		if (line && *line)
			add_history(line);
		handel_input(line, &env_list);
		free(line); // be aware of this
	}
}

int	main(int arc, char *arv[], char **env)
{
	(void)arv;
	if (arc != 1)
		(printf("InputError"), exit(0));
	read_input(env);
}

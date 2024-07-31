/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:42:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/31 17:23:39 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_s = 0;

void	handel_input(char *line, t_env **env_list)
{
	t_lexer			*lexer;
	char			**res;
	t_cmds	*cmds;
	int				len;

	lexer = NULL;
	cmds = NULL;
	if (!handel_quotes(line))
		return (error_msg(SYNTAX_ERROR, env_list));
	line = add_spaces(line);
	if (!line)
		return ;
	res = ft_split(line);
	if (!res)
		return ;
	tokenizer(res, &lexer);
	if (!syntax_error(&lexer, env_list))
		return (handel_herdoc_err(&lexer, &cmds));
	handel_expanding(&lexer, env_list);
	remove_quotes(&lexer);
	cmds = parser(&lexer, &cmds, get_lcmd(lexer), env_list);
	len = ft_lstsize_cmd(cmds);
	multiple_cmd(env_list, cmds, len);
}
	
void	read_input(char **env)
{
	char	*line;
	int		exit_status;
	t_env	*env_list;

	exit_status = 0;
	if (!env || !env[0])
		add_emergency_env(&env_list);
	else
		env_list = get_env(env);
	notify_signals();
	while (1)
	{
		line = readline("minishell : ");
		if (g_exit_s == 1)
			(1) && (modify_exit_status(1, &env_list), g_exit_s = 0);
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (line && *line)
			add_history(line);
		handel_input(line, &env_list);
		free(line);
	}
}

int	main(int arc, char *arv[], char **env)
{
	(void)arv;
	rl_catch_signals = 0;
	if (arc != 1)
		(printf("InputError"), exit(0));
	read_input(env);
}


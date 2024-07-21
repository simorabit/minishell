/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:42:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/21 02:30:01 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handel_input(char *line, t_env **env_list)
{
	t_lexer			*lexer;
	char			**res;
	t_simple_cmds	*cmds;
	int				len;

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
		return handel_herdoc_err(&lexer);
	handel_expanding(&lexer, env_list);
	remove_quotes(&lexer);
	cmds = parser(&lexer, &cmds, get_lcmd(lexer));
	free_lexer(lexer);
	initialize_files(cmds);
	len = ft_lstsize_cmd(cmds);
	multiple_cmd(env_list, cmds, len);
}

void sighandler(int sig)
{
	 if (sig == SIGINT)
    {
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			printf("\n");
			return ;
		}
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}
void	read_input(char **env)
{
	char	*line;
	t_env	*env_list;
	
	if (!env || !env[0])
		add_emergency_env(&env_list);
	else
		env_list = get_env(env);
	signal(SIGINT, sighandler);
	while (1)
	{
		line = readline("minishell : ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line && *line)
			add_history(line);
		handel_input(line, &env_list);
		free(line); // be aware of this
	}
}

int	main(int arc, char *arv[], char **env)
{
	(void)arv;
	rl_catch_signals = 0; // 
	//TODO - replace this variable into 1 in child for heredoc
	//TODO - handle -n for echo
	if (arc != 1)
		(printf("InputError"), exit(0));
	read_input(env);
}

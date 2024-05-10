/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:42:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/10 15:43:16 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handel_input(char *line)
{
    t_lexer *lexer;
    char    **res;

    lexer = NULL;
    if (!handel_quotes(line))
        error_msg(SyntaxError);
    line = add_spaces(line);
    res = ft_split(line, ' ');
    if(!res)
    {
        free_list(res);
        allocation_error(line);
    }
    tokenizer(res, &lexer);
}

void parsing()
{
    char    *line;

    while (1)
    {
        line = readline("minishell> ");
        if (!line)
            break;
        if (*line)
            add_history(line);
        handel_input(line);
        free(line);
    }
}

int main()
{
    // if(arc == 1)
    //     (printf(InputError), exit(0));
    parsing();
    //syntax error
    // parser(&lexer);
}

#include "../../minishell.h"

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		i++; 
	}
	return (i);
}

void	ft_memcpy(char *dst, char *src, size_t	n)
{
	char	*d;
	char	*s;
	size_t	i;

	d = dst;
	s = src;
	i = 0;
	if (d == NULL && s == NULL)
		return ;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

char	*add_double_quotes(char *var)
{
	int		i;
	int		j;
	int		x;
	int		size;
	char	*ptr;

	size = ft_strlen(var);
	i = 0;
	j = 0;
	x = 0;
	if (ft_strchr(var, '='))
		size += 2;
	
	ptr = malloc(sizeof(char) * size + 1);
	if (var[0] == '\0' || var == NULL)
		return (NULL);
	while (var[i])
	{
		if (var[i] == '=' && x == 0)
		{
			ptr[j] = '=';
			j++;
			ptr[j] = '\"';
			j++;
			i++;
			x++;
		}
		if (var[i] != '\0')
		{
			ptr[j] = var[i];
			i++;
			j++;
		}
	}
	
	if (x != 0)
	{
		ptr[j] = '\"';
		j++;
	}
	
	ptr[j] = '\0';
	return (ptr);
}

void	ft_sort_env(t_env *env)
{
	char	**ptr;
	char	*tmp;
	int		list_len;
	int		i;
	t_env	*head;

	ptr = NULL;
	list_len = ft_lstsize_env(env);
	i = 0;
	while (i < list_len)
	{
		head = env;
		while(head->next)
		{
			if (ft_strcmp(head->content, head->next->content) > 0)
			{
				tmp = head->content;
				head->content = head->next->content;
				head->next->content = tmp;
			}
			head = head->next;
		}
		i++;
	}
	head = NULL;
}

char	*get_var_from_beg_to_eq(char *var)
{
	int 	i;
	char	*ptr;

	i = 0;
	while (var[i] && var[i] != '+')
		i++;
	ptr = malloc(i + 1);
	i = 0;
	while (var[i] && var[i] != '+')
	{
		ptr[i] = var[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*get_content_from_eq_to_fin(char *var)
{
	int	i;

	i = 0;
	if (ft_strchr(var, '='))
	{
		while (var[i] && var[i] != '=')
			i++;
		i++;
	}
	return (var + i);
}

char	*check_var_does_it_exist(char *arg)
{

	char	*var;

	var = get_var_from_beg_to_eq(arg);
	// printf ("---> %s", arg);
	// exit (0);
	return (getenv(var));
}

int	check_arg_is_valide(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if ((arg[i] >= '0' && arg[i] <= '9')
			|| (arg[i] >= 'a' && arg[i] <= 'z')
				|| (arg[i] >= 'A' && arg[i] <= 'Z')
					|| arg[i] == '_' || arg[i] == '=')
				i++;
		else
			break ;
	}
	if (arg[i])
		return (1);
	return (0);
}

int	check_for_first_char(char *arg)
{
	if ((arg[0] >= 'a' && arg[0] <= 'z')
		|| (arg[0] >= 'A' && arg[0] <= 'Z')
			|| arg[0] == '_')
			return (0);
	else
		return (1);
}
int	check_for_plus_and_eq(char *arg, int w)
{
	int	i;
	char	*first_part;
	char	*sec_part;

	i = 0;
	first_part = get_var_from_beg_to_eq(arg);
	sec_part = get_content_from_eq_to_fin(arg);
	if ((check_arg_is_valide(first_part) || check_for_first_char(first_part)) && w == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		//exit (1);
	}
	else if (check_arg_is_valide(sec_part) && w == 1 )
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd("`", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd(": not a valid identifier", 2);
		ft_putstr_fd("\n", 2);
		//exit (1);
	}
	while (arg[i + 1])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_plus(char *new)
{
	int		i;
	int		j;
	char	*ptr;
	

	i = 0;
	j = 0;
	ptr = malloc(ft_strlen(new) + 1);
	
	while (new[i])
	{
		if (new[i] != '+')
		{
			ptr[j] = new[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

void	add_variable(t_env **list_env, char *new)
{
	t_env	*var;
	char	*new_var;
	char	*first_part;
	char	*sec_part;
	
	first_part = NULL;
	sec_part = NULL;
	new_var = NULL;
	if (check_for_plus_and_eq(new, 1))
	{
		new_var = check_var_does_it_exist(new);
		if (new_var)
		{
			first_part = ft_strjoin(get_var_from_beg_to_eq(new), "=");
			sec_part = ft_strjoin(new_var, get_content_from_eq_to_fin(new));
			new = ft_strjoin(first_part, sec_part);
		}
		new = remove_plus(new);
	}
	var = ft_lstnew_env(new);
	ft_lstadd_back_env(list_env, var);
}

t_env	*env_dup(t_env *list)
{
	t_env	*nood;
	t_env	*new_list;

	new_list = NULL;
	if (list == NULL)
		return (NULL);
	while (list)
	{
		nood = ft_lstnew_env(list->content);
		ft_lstadd_back_env(&new_list, nood);
		list = list->next;
	}
	return (new_list);
}

int	one_plus_and_one_eq(char *str)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == '+')
			x++;
		else if (str[i] == '=')
			y++;
		i++;
	}
	if (x == 1 && y == 1)
		return (1);
	return (0);
}

void	export_exe(char **cmd, t_env *list_env)
{
	// char	**export;
	t_env	*head;
	t_env	*copy_env;
	int		i;

	i = 1;
	if (cmd [0] == NULL || cmd == NULL)
		return ;
	while (cmd[i])
	{
		if (check_for_plus_and_eq(cmd[i], 0) && one_plus_and_one_eq(cmd[i]))
		{
			add_variable(&list_env, cmd[i]);
		}
		else if (!check_arg_is_valide(cmd[i]) && !check_for_first_char(cmd[i]))
			add_variable(&list_env, cmd[i]);
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		
		i++;
	}
	
	if (!ft_strncmp(cmd[0], "export", 6) && !cmd[1])
	{
		
		copy_env = env_dup(list_env);
		ft_sort_env(copy_env);
		head = copy_env;
		while (head)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(add_double_quotes(head->content), 1);
			ft_putstr_fd("\n", 1);
			head = head->next;
		}
	}
}

# include "../minishell.h"

char	*get_content_from_eq_to_fin(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	i++;
	return (var + i);
}

int main ()
{
	printf ("%s\n", get_content_from_eq_to_fin("hgshga+=jdhjssss"));
}
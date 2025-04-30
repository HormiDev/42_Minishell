
#include "../../include/minishell.h"


void	ft_free_array_content(void **array, void (*free_func)(void *))
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free_func(array[i]);
		i++;
	}
}

static char	*ft_find_needle(char *needle, char *hay, int flag)
{
	char	*wildcard_search;
	char	*wildcard_search_aux;

	if (flag == 0)
		wildcard_search = ft_strnstr_p(needle, hay, ft_strlen_p(needle));
	else
	{
		wildcard_search = ft_strnstr_p(needle, hay, ft_strlen_p(needle));
		if (wildcard_search)
			needle = wildcard_search + ft_strlen_p(hay);
		wildcard_search_aux = NULL;
		while (wildcard_search)
		{
			wildcard_search_aux = wildcard_search;
			wildcard_search = ft_strnstr_p(needle, hay, ft_strlen_p(needle));
			if (wildcard_search)
				needle = wildcard_search + ft_strlen_p(hay);
		}
		wildcard_search = wildcard_search_aux;
	}
	return (wildcard_search);
}

/**
 * numbers[1] = number of wildcards
 * numbers[2] = ends with wildcard
 */
char	*ft_get_wildcard_search(char *str, char **wildcard,
	char *needle, int *numbers)
{
	char	*wildcard_search;

	wildcard_search = ft_find_needle(str, needle, 0);
	if (!numbers[2])
	{
		while (**wildcard != 1)
			(*wildcard)++;
		numbers[1]--;
		if (numbers[1] == 0)
			wildcard_search = ft_find_needle(str, needle, 1);
	}
	return (wildcard_search);
}

int	ft_number_of_wildcards(char *wildcard)
{
	int	i;
	int	number_of_wildcards;

	i = 0;
	number_of_wildcards = 0;
	if (*wildcard != 1)
		number_of_wildcards++;
	while (wildcard[i])
	{
		if (wildcard[i] == 1)
		{
			while (wildcard[i] == 1)
				i++;
			i--;
			number_of_wildcards++;
		}
		i++;
	}
	return (number_of_wildcards);
}

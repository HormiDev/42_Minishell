/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:59:48 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/26 21:54:11 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_search_alnum_char(char *str)
{
	while (*str)
	{
		if (ft_isalnum(*str))
			return (str);
		str++;
	}
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)// pasar funcion a la libft
{
	int	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_alnum_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	char1;
	int	char2;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	char1 = s1[i];
	char2 = s2[i];
	if (char1 >= '0' && char1 <= '9')
		char1 = 128 + char1 - 48;
	else if (char1 >= 'a' && char1 <= 'z')
		char1 = 128 + char1 - 97 + 10;
	else if (char1 >= 'A' && char1 <= 'Z')
		char1 = 128 + char1 - 65 + 10;
	if (char2 >= '0' && char2 <= '9')
		char2 = 128 + char2 - 48;
	else if (char2 >= 'a' && char2 <= 'z')
		char2 = 128 + char2 - 97 + 10;
	else if (char2 >= 'A' && char2 <= 'Z')
		char2 = 128 + char2 - 65 + 10;
	return ((unsigned char)char1 - (unsigned char)char2);
}

int	ft_is_order_wildcard(t_list *list)
{
	char	*str1;
	char	*str2;

	while (list->next)
	{
		str1 = ft_search_alnum_char(list->content);
		str2 = ft_search_alnum_char(list->next->content);
		if ((str1 == NULL && str2 == NULL
				&& ft_strcmp(list->content, list->next->content) > 0)
			|| (str1 != NULL && str2 != NULL && ft_alnum_strcmp(str1, str2) > 0)
			|| (str1 != NULL && str2 == NULL))
			return (0);
		list = list->next;
	}
	return (1);
}

void	ft_print_list(t_list *list)//borrar funcion
{
	while (list)
	{
		ft_printf("%s ", list->content);
		list = list->next;
	}
	ft_printf("\n");
}

void	ft_order_wildcards(t_list *list)
{
	t_list	*aux;
	char	*str[2];

	if (ft_lstsize(list) < 2)
		return ;
	while (!ft_is_order_wildcard(list))
	{
		aux = list;
		while (aux->next)
		{
			str[0] = ft_search_alnum_char(aux->content);
			str[1] = ft_search_alnum_char(aux->next->content);
			if ((str[0] == NULL && str[1] == NULL
					&& ft_strcmp(list->content, list->next->content) > 0)
				|| (str[0] != NULL && str[1] != NULL
					&& ft_alnum_strcmp(str[0], str[1]) > 0)
				|| (str[0] != NULL && str[1] == NULL))
			{
				str[0] = aux->content;
				aux->content = aux->next->content;
				aux->next->content = str[0];
			}
			aux = aux->next;
		}
	}
}

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

char	*ft_find_needle(char *needle, char *hay, int flag)
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
		while (**wildcard != '*')
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
	if (*wildcard != '*')
		number_of_wildcards++;
	while (wildcard[i])
	{
		if (wildcard[i] == '*')
		{
			while (wildcard[i] == '*')
				i++;
			number_of_wildcards++;
		}
		i++;
	}
	return (number_of_wildcards);
}

int	ft_free_and_leave(char **wildcard_split, char *wildcard_copy, int ret)
{
	ft_free_array_content((void **)wildcard_split, ft_free_alloc);
	ft_free_alloc(wildcard_split);
	ft_free_alloc(wildcard_copy);
	return (ret);
}

/**
 * numbers[0] = iterator
 * numbers[1] = number of wildcards
 * numbers[2] = ends with wildcard
 */
int	ft_needle_search_loop(char *wildcard, char *str,
	int number_of_wildcards, int ends_with_wildcard)
{
	char	**wildcard_split;
	char	*wildcard_search;
	char	*wildcard_copy;
	int		nums[3];

	wildcard_split = ft_split_ae(wildcard, '*');
	wildcard_copy = ft_strdup_ae(wildcard);
	nums[0] = -1;
	nums[1] = number_of_wildcards;
	nums[2] = ends_with_wildcard;
	while (wildcard_split[++nums[0]])
	{
		wildcard_search = ft_get_wildcard_search(str, &wildcard,
				wildcard_split[nums[0]], nums);
		if ((wildcard_search == NULL) || (nums[0] == 0
				&& *wildcard_copy != '*' && wildcard_search != &str[0])
			|| (wildcard_split[nums[0] + 1] == 0
				&& wildcard_copy[ft_strlen_p(wildcard_copy) - 1] != '*'
				&& wildcard_search != &str[ft_strlen_p(str)
					- ft_strlen_p(wildcard_split[nums[0]])]))
			return (ft_free_and_leave(wildcard_split, wildcard_copy, 0));
		str = wildcard_search + ft_strlen_p(wildcard_split[nums[0]]);
	}
	return (ft_free_and_leave(wildcard_split, wildcard_copy, 1));
}

int	ft_check_wildcard(char *str, char *wildcard)
{
	int		number_of_wildcards;
	int		ends_with_wildcard;

	number_of_wildcards = ft_number_of_wildcards(wildcard);
	if (wildcard[ft_strlen_p(wildcard) - 1] == '*')
		ends_with_wildcard = 1;
	else
		ends_with_wildcard = 0;
	return (ft_needle_search_loop(wildcard, str,
			number_of_wildcards, ends_with_wildcard));
}

void	ft_process_wildcards(char *dir, char *str, t_list **list)
{
	DIR				*directory;
	struct dirent	*entry;
	int				hidden_file;

	directory = opendir(dir);
	if (str == NULL || *str == '\0' || list == NULL || directory == NULL)
		return ;
	hidden_file = 0;
	if (str[0] == '.')
		hidden_file = 1;
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (hidden_file == 0 && (entry->d_name[0] == '.'
				|| ft_strncmp_p(entry->d_name, ".", 2) == 0
				|| ft_strncmp_p(entry->d_name, "..", 3) == 0))
			;
		else if (ft_check_wildcard(entry->d_name, str))
			ft_lstadd_back(list, ft_lstnew_ae(ft_strdup_ae(entry->d_name)));
		entry = readdir(directory);
	}
	if (closedir(directory) == -1)
		perror("closedir");
}

int	main(int argc, char *argv[])
{
	t_list	*list;

	if (argc != 2)
	{
		printf("Usage: %s \"wi*ld*ca*rd*s\"\n", argv[0]);
		return (1);
	}
	list = NULL;
	ft_process_wildcards(".", argv[1], &list);
	ft_order_wildcards(list);
	if (list == NULL)
		ft_lstadd_back(&list, ft_lstnew_ae(ft_strdup_ae(argv[1])));
	ft_print_list(list);
	ft_alloc_lst(0, 0);
	return (0);
}

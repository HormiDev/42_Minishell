/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:59:48 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/16 01:59:40 by ide-dieg         ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_is_order_wildcard(t_list *list)
{
	char	*str1;
	char	*str2;
	int		min_len;

	while (list->next)
	{
		str1 = ft_search_alnum_char(list->content);
		str2 = ft_search_alnum_char(list->next->content);
		if ((str1 == NULL && str2 == NULL
			&& ft_strcmp(list->content, list->next->content) > 0 )
			|| (str1 != NULL && str2 != NULL && ft_strcmp(str1, str2) > 0)
			|| (str1 != NULL && str2 == NULL))
			return (0);
		list = list->next;
	}
	return (1);
}

void	ft_order_wildcards(t_list *list)
{
	t_list	*aux;
	char	*str1;
	char	*str2;

	if (ft_lstsize(list) < 2)
		return ;
	while(!ft_is_order_wildcard(list))
	{
		aux = list;
		while (aux->next)
		{
			str1 = ft_search_alnum_char(aux->content);
			str2 = ft_search_alnum_char(aux->next->content);
			if ((str1 == NULL && str2 == NULL
				&& ft_strcmp(list->content, list->next->content) > 0 )
				|| (str1 != NULL && str2 != NULL && ft_strcmp(str1, str2) > 0)
				|| (str1 != NULL && str2 == NULL))
			{
				str1 = aux->content;
				aux->content = aux->next->content;
				aux->next->content = str1;
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

int	ft_check_wildcard(char *str, char *wildcard)
{
	char	**wildcard_split;
	int		i;
	char	*wildcard_search;

	//if (*wildcard == '*')
	//if (wildcard[ft_strlen_p(wildcard) - 1] == '*')
	wildcard_split = ft_split_ae(wildcard, '*');
	i = 0;
	while (wildcard_split[i])
	{
		wildcard_search = ft_strnstr_p(str, wildcard_split[i], ft_strlen_p(str));
		if (wildcard_search == NULL)
		{
			ft_free_array_content((void **)wildcard_split, ft_free_alloc);
			ft_free_alloc(wildcard_split);
			return (0);
		}
		if (i == 0 && *wildcard != '*' && wildcard_search != &str[0])
		{
			ft_free_array_content((void **)wildcard_split, ft_free_alloc);
			ft_free_alloc(wildcard_split);
			return (0);
		}
		if (wildcard_split[i + 1] == 0 && wildcard[ft_strlen_p(wildcard) - 1] != '*' 
			&& wildcard_search != &str[ft_strlen_p(str) - 1 - ft_strlen_p(wildcard_split[i])])
		{
			ft_free_array_content((void **)wildcard_split, ft_free_alloc);
			ft_free_alloc(wildcard_split);
			return (0);
		}
		str += ft_strlen_p(wildcard_split[i]);
		i++;
	}
	ft_free_array_content((void **)wildcard_split, ft_free_alloc);
	ft_free_alloc(wildcard_split);
	return (1);
}

void	ft_process_wildcards(char *dir, char *str, t_list **list)
{
	DIR				*directory;
	struct dirent	*entry;
	int 			hidden_file;

	directory = opendir(dir);
	if (str == NULL || *str == '\0' || list == NULL || directory == NULL)
		return ;
	hidden_file = 0;
	if (str[0] == '.')
		hidden_file = 1;
	while ((entry = readdir(directory)) != NULL)
	{
		if (hidden_file == 0 && entry->d_name[0] == '.'
			|| ft_strncmp_p(entry->d_name, ".", 2) == 0
			|| ft_strncmp_p(entry->d_name, "..", 3) == 0)
			continue ;
		if (ft_check_wildcard(entry->d_name, str))
		{
			ft_lstadd_back(list, ft_lstnew_ae(ft_strdup_ae(entry->d_name)));
		}
	}
	if (closedir(directory) == -1)
		perror("closedir");
}

int main(int argc, char *argv[])
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
	while (list)
	{
		ft_printf("%s ", list->content);
		list = list->next;
	}
	ft_printf("\n");
	ft_alloc_lst(0, 0);
	return (0);
}

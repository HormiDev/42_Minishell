/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_wildcards_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:34:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/07 14:44:45 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

static char	*ft_search_alnum_char(char *str)
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

static int	ft_alnum_strcmp(const char *s1, const char *s2)
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

static int	ft_is_order_wildcard(t_list *list)
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

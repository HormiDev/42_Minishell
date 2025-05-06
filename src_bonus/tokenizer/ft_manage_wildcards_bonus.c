/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_wildcards_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:11:22 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 23:34:23 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

static char	*ft_quotes_out(char *str)
{
	char	*content;

	content = ft_substr_ae(str, 1, ft_strlen_p(str) - 2);
	ft_free_alloc(str);
	return (content);
}

static char	*ft_quotes_in(char *str)
{
	char	*content;

	content = ft_alloc_lst(ft_strlen_p(str) + 3, 4);
	ft_sprintf(content, "\"%s\"", str);
	ft_free_alloc(str);
	return (content);
}

static void	ft_append_files_into_list(t_list **list, t_list **files)
{
	t_list	*aux;

	aux = (*list)->next;
	(*list)->content = ft_quotes_in((char *)(*files)->content);
	if ((*files)->next)
	{
		*files = (*files)->next;
		(*list)->next = *files;
		while ((*files)->next)
		{
			(*files)->content = ft_quotes_in((char *)(*files)->content);
			*files = (*files)->next;
		}
		(*files)->content = ft_quotes_in((char *)(*files)->content);
	}
	(*files)->next = aux;
}

static void	ft_replace_non_printables_for_asteriks(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 1)
			str[i] = '*';
		i++;
	}
}

void	ft_manage_wildcards(t_list *list)
{
	char	*content;
	t_list	*files;

	while (list)
	{
		content = (char *)list->content;
		if (ft_strchr_p(content, 1))
		{
			list->content = ft_quotes_out(content);
			files = NULL;
			ft_process_wildcards(".", (char *)list->content, &files);
			if (files)
			{
				ft_order_wildcards(files);
				ft_append_files_into_list(&list, &files);
			}
			else
				list->content = ft_quotes_in((char *)list->content);
			if (ft_strchr_p((char *)list->content, 1))
				ft_replace_non_printables_for_asteriks((char *)list->content);
		}
		list = list->next;
	}
}

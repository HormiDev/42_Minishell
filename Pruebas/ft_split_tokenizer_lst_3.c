/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:50:10 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/17 20:53:15 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_special_token(char *c);

void	ft_remove_spaces(t_list **list)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (*(char *)list[0]->content == ' '
		|| (*(char *)list[0]->content == '\t'))
	{
		tmp = *list;
		*list = (*list)->next;
		ft_free_alloc(tmp->content);
		ft_free_alloc(tmp);
	}
	tmp = *list;
	while (tmp)
	{
		while (tmp->next && (*(char *)tmp->next->content == ' '
			|| (*(char *)tmp->next->content == '\t')))
		{
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			ft_free_alloc(tmp2->content);
			ft_free_alloc(tmp2);
		}
			tmp = tmp->next;
	}
}

/**
 * @brief funcion que pone comillas "" a los strings para diferenciarlos 
 * del resto de tokens
 * @example hola || adios -> "hola" || "adios"
 */
void	put_quotes(t_list *list)
{
	char	*str;

	while (list)
	{
		if (!ft_is_special_token(((char *)list->content)))
		{
			str = ft_alloc_lst(ft_strlen_p((char *)list->content) + 3, 3);
			sprintf(str, "\"%s\"", (char *)list->content);
			ft_free_alloc(list->content);
			list->content = str;
		}
		list = list->next;
	}
}

void	ft_join_str_tokenizer_while(t_list *list)
{
	char	*tmpstr;

	tmpstr = (char *)list->next->content;
	list->next->content = ft_substr_ae(tmpstr, 1,
		ft_strlen_p(tmpstr) - 2);
	ft_free_alloc(tmpstr);
	tmpstr = (char *)list->content;
	list->content = ft_strjoin_ae((char *)list->content,
			(char *)list->next->content);
	ft_free_alloc(tmpstr);
	list->next = list->next->next;
}
/**
 * @brief funcion que une los strings que estan entre comillas
 * @example "hola mundo"' que tal '$VAR -> "hola mundo que tal var_content"
 * @param list lista de tokens
 * @return void
 */
void	ft_join_str_tokenizer(t_list *list)
{
	char	*tmpstr;

	while (list)
	{
		if (*(char *)list->content == '\"' || *(char *)list->content == '\'')
		{
			tmpstr = (char *)list->content;
			list->content = ft_substr_ae((char *)list->content, 1,
				ft_strlen_p((char *)list->content) - 2);
			ft_free_alloc(tmpstr);
			while (list->next && (*(char *)list->next->content == '\"'
				|| *(char *)list->next->content == '\''))
				ft_join_str_tokenizer_while(list);
			tmpstr = (char *)list->content;
			list->content = ft_alloc_lst(ft_strlen_p(tmpstr) + 3, 3);
			sprintf((char *)list->content, "\"%s\"", tmpstr);
			ft_free_alloc(tmpstr);
		}
		list = list->next;
	}
}

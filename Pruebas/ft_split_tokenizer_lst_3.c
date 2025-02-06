/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:50:10 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/06 17:38:05 by ide-dieg         ###   ########.fr       */
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

void	put_quotes(t_list *list)
{
	char	*str;

	while (list)
	{
		//printf("%s is special token: %d\n", (char *)list->content, ft_is_special_token((char *)list->content));
		if (!ft_is_special_token(((char *)list->content)))
		{
			str = ft_alloc_lst(ft_strlen_p((char *)list->content) + 3, 3);
			sprintf(str, "\"%s\"", (char *)list->content);
			list->content = str;
		}
		list = list->next;
	}
}

void	ft_join_str_tokenizer(t_list *list)
{
	char	*tmpstr;

	while (list)
	{
		if (*(char *)list->content == '\"' || *(char *)list->content == '\'')
		{
			list->content = ft_substr_ae((char *)list->content, 1,
				ft_strlen_p((char *)list->content) - 2);
			while (list->next && (*(char *)list->next->content == '\"'
					|| *(char *)list->next->content == '\''))
			{
				list->content = ft_strjoin_ae((char *)list->content,
						ft_substr_ae((char *)list->next->content, 1,
							ft_strlen_p((char *)list->next->content) - 2));
				list->next = list->next->next;
			}
			tmpstr = (char *)list->content;
			list->content = ft_alloc_lst(ft_strlen_p((char *)list->content) + 3, 3);
			//if (*(char *)list->content == '\"')
				sprintf((char *)list->content, "\"%s\"", tmpstr);//si se elimina la linea comentada superior indexar esta linea correctamente
		}
		list = list->next;
	}
}

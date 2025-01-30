/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:50:10 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/30 21:20:17 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_special_token(char *c);

void	put_quotes(t_list *list)
{
	char	*str;

	while (list)
	{
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
		}
		tmpstr = (char *)list->content;
		list->content = ft_alloc_lst(ft_strlen_p((char *)list->content) + 3, 3);
		sprintf((char *)list->content, "\"%s\"", tmpstr);
		list = list->next;
	}
}

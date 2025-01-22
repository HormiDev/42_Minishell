/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:58:26 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/22 20:28:35 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int	ft_is_special_token(char *c)
{
	if (!ft_strncmp_p(c, ">>", 2) || !ft_strncmp_p(c, "<<", 2)
		|| !ft_strncmp_p(c, "||", 2) || !ft_strncmp_p(c, "&&", 2))
		return (2);
	if (!ft_strncmp_p(c, ">", 1) || !ft_strncmp_p(c, "<", 1)
		|| !ft_strncmp_p(c, "|", 1) || !ft_strncmp_p(c, "(", 1)
		|| !ft_strncmp_p(c, ")", 1) || !ft_strncmp_p(c, "\"", 1)
		|| !ft_strncmp_p(c, "'", 1) || !ft_strncmp_p(c, "$", 1)
		|| !ft_strncmp_p(c, " ", 1) || !ft_strncmp_p(c, "\t", 1)
		|| !ft_strncmp_p(c, "\n", 1))
		return (1);
	return (0);
}

t_list	*ft_split_tokenizer_lst(char *str, t_list *env)
{
	t_list	*list;
	int		i;
	int 	start;

	list = NULL;
	i = 0;
	start = 0;
	while (str[i])
	{
		if (ft_is_special_token(&str[i]) == 2)
		{
			if (start != i)
				ft_lstadd_back(&list, ft_lstnew_ae(ft_substr_ae(str, start, i - 1)));
			ft_lstadd_back(&list, ft_lstnew_ae(ft_substr_ae(str, i, 2)));
			start = i + 2;
			i += 2;
		}
		else if (ft_is_special_token(&str[i]) == 1)
		{
			if (start != i)
				ft_lstadd_back(&list, ft_lstnew_ae(ft_substr_ae(str, start, i - 1)));
			ft_lstadd_back(&list, ft_lstnew_ae(ft_substr_ae(str, i, 1)));
			start = i + 1;
		}
		else
			i++;
	}
}
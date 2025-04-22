/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:58:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/01 21:04:58 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*ft_get_content_building(t_list *tks)
{
	t_list	*content;

	content
	if (*(char *)tks->content == '(')
			
}

t_building	*ft_new_building(t_list *tks)
{
	t_building	*node;
	t_list		*first_instruction;
	t_list		*last_instruction;

	first_instruction = tks;
	last_instruction = tks;
	while (tks && *(char *)tks->content != '(')
		tks = tks->next;
	node = ft_alloc_lst(sizeof(t_building), 4);
	node->content = ft_get_content_building(tks);
	return (node);
}

t_building	*ft_building_management(t_list *tks)
{
	t_building	*building;
	t_list		*first_instruction;

	first_instruction = tks;
	while (tks)
	{
		while (*(char *)tks->content != '&' && ft_strncmp_p(tks->content, "||", 2)
			&& *(char *)tks->content != '(')
			tks->next = tks;
		building = ft_new_building(first_instruction);
		tks = tks->next;
		first_instruction = tks;
	}
}

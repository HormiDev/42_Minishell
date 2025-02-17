/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:13:52 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/17 18:21:10 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_create_cmd(t_list *list)
{
	t_cmd	*new_cmd;
	

	new_cmd = ft_alloc_lst(sizeof(t_cmd), 4);
	return (new_cmd);
}
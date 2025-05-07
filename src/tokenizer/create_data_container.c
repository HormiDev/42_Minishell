/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data_container.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:50:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/07 14:36:23 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * type = 0 -> t_cmd
 * type = 1 -> char *
 * 
 * @param data
 * @param type
*/
t_data_container	*ft_new_data_container(void *data, int type)
{
	t_data_container	*data_container;

	data_container = ft_alloc_lst(sizeof(t_data_container), 4);
	data_container->data = data;
	data_container->type = type;
	return (data_container);
}

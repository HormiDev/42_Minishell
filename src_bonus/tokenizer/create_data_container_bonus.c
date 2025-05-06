/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data_container_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:09:43 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 21:10:16 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

/**
 * @brief Funcion que crea un contenedor de datos
 * type = 0 -> t_cmd
 * type = 1 -> char *
 * type = 2 -> parentesis
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

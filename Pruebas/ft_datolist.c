/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_datolist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:06:40 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/13 20:23:05 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef	struct s_env 
{
	char			*key;
	char			*value;
	char			*line;
	struct s_env	*next;
}			t_env;

t_env	*ft_atolist(char **env)
{
	t_env	*head;

	
}

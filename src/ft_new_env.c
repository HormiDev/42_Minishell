/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:28:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/13 22:04:48 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_new_env(char *envp)
{
	t_env	*hash;
	int		i;

	hash = (t_env *)ft_alloc_lst(sizeof(t_env), 3);
	i = 0;
	while (envp[i] != '=')
		i++;
	hash->name = ft_substr_ae(envp, 0, i);
	hash->value = ft_strdup_ae(envp + i + 1);
	return (hash);
}
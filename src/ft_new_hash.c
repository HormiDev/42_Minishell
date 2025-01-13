/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:11:51 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/13 22:08:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_export(char *envp)
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
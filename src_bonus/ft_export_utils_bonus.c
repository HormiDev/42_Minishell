/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:35:17 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 22:37:16 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

void	ft_export_shlvl(t_env *env)
{
	char	*tmp;
	int		number;

	number = ft_atoi_p(env->value);
	if (!ft_isnumber(env->value) || number < 0
		|| number > 1000)
	{
		ft_free_alloc(env->value);
		env->value = ft_strdup_ae("0");
		ft_free_alloc(env->full);
		tmp = ft_strjoin_ae(env->name, "=");
		env->full = ft_strjoin_ae(tmp, env->value);
		ft_free_alloc(tmp);
	}
	else
	{
		ft_free_alloc(env->value);
		env->value = ft_add_to_alloc_lst_e(ft_itoa(number));
		ft_free_alloc(env->full);
		tmp = ft_strjoin_ae(env->name, "=");
		env->full = ft_strjoin_ae(tmp, env->value);
		ft_free_alloc(tmp);
	}
}

void	ft_free_hash(t_env *hash)
{
	ft_free_alloc(hash->name);
	ft_free_alloc(hash->value);
	ft_free_alloc(hash->full);
	ft_free_alloc(hash);
}

t_env	*ft_create_hash(char *envp, int i)
{
	t_env	*hash;

	hash = (t_env *)ft_alloc_lst(sizeof(t_env), 3);
	hash->full = ft_strdup_ae(envp);
	hash->name = ft_substr_ae(envp, 0, i);
	hash->value = ft_strdup_ae(envp + i + 1);
	return (hash);
}

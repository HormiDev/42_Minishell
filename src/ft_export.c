/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:32:31 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/03 17:55:29 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_export(char *envp, t_list **envp_list)
{
	t_env	*hash;
	t_list	*tmp_list;
	int		i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	if (!envp[i])
		return ;
	hash = ft_create_hash(envp, i);
	tmp_list = *envp_list;
	while (tmp_list && (t_env *)tmp_list->content)
	{
		if (!ft_strncmp_p(((t_env *)tmp_list->content)->name, hash->name,
			ft_strlen_p(hash->name) + 1))
		{
			ft_free_hash((t_env *)tmp_list->content);
			tmp_list->content = hash;
			if (ft_strncmp_p(hash->name, "SHLVL", 6) == 0)
				ft_export_shlvl((t_env *)tmp_list->content);
			return ;
		}
		tmp_list = tmp_list->next;
	}
	ft_lstadd_back(envp_list, ft_lstnew_ae(hash));
}

char	**create_array_env_name(t_list *env_list)
{
	char	**array;
	int		i;

	array = (char **)ft_alloc_lst(sizeof(char *) * ft_lstsize(env_list) + 1, 3);
	i = 0;
	while (env_list)
	{
		if (ft_strncmp_p(((t_env *)env_list->content)->name, "_", 2))
		{
			array[i] = ((t_env *)env_list->content)->name;
			i++;
		}
		env_list = env_list->next;
	}
	array[i] = NULL;
	return (array);
}

void	ft_alpha_orderer(char **array)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strncmp_p(array[i], array[j], ft_strlen_p(array[j])) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_export_args(char **args, t_list **env_list, t_minishell *mini)
{
	int		i;
	char	**array;

	i = 0;
	if (ft_splitlen(args) == 0)
	{
		array = create_array_env_name(*env_list);
		ft_alpha_orderer(array);
		while (array[i])
		{
			ft_dprintf(mini->io_fd[1],
				"declare -x %s=\"%s\"\n", array[i],
				ft_getenv(array[i], *env_list));
			i++;
		}
		ft_free_alloc(array);
		return ;
	}
	while (args[i])
	{
		ft_export(args[i], env_list);
		i++;
	}
	ft_refresh_env_array(mini->envp, mini);
}

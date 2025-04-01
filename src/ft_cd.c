/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:47:36 by dagimeno          #+#    #+#             */
/*   Updated: 2025/04/01 19:21:31 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_modify_env(t_list **env, t_minishell *minishell, char *path)
{
	char	*tmp;

	tmp = ft_strjoin_ae("OLDPWD=", minishell->cwd);
	ft_export(tmp, env);
	ft_free_alloc(tmp);
	if (getcwd(minishell->cwd, PATH_MAX) == NULL)
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));//mejor comentario que el original
		ft_sprintf(minishell->cwd, "%s/%s", ft_getenv("OLDPWD", *env),
					path);
		minishell->exit_code = 1;
	}
	else
	{
		tmp = ft_strjoin_ae("PWD=", minishell->cwd);
		ft_export(tmp, env);
		ft_free_alloc(tmp);
	}
}

void	ft_cd(t_cmd *cmd, t_minishell *minishell)
{
	char	**args;
	char	*path;
	t_list	*env;
	
	env = minishell->envp;
	args = &cmd->args[1];
	if (!args[0])
		path = ft_getenv("HOME", env);
	else if (args[1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		minishell->exit_code = 1;
		return ;
	}
	else
		path = args[0];
	if (chdir(path) == -1)
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		minishell->exit_code = 1;
		return ;
	}
	ft_modify_env(&env, minishell, path);
	minishell->exit_code = 0;
}

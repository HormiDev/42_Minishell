/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:47:36 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/21 14:49:26 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(char **args, t_list **env, t_minishell *minishell)
{
	char	*path;

	if (!args[0])
		path = ft_getenv("HOME", *env);
	else if (args[1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	else
		path = args[0];
	if (chdir(path) == -1)
		ft_dprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
	else
	{
		//getcwd(minishell->cwd, PATH_MAX);//revisar para usar alloc lst
		ft_export(ft_strjoin_ae("OLDPWD=",  minishell->cwd), env);
		ft_export(ft_strjoin_ae("PWD=", getcwd(minishell->cwd, PATH_MAX)), env);
	}
}

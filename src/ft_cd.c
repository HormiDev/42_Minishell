/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:47:36 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/19 22:11:03 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>
/*
void	ft_cd(char *path, t_list **env, char **cwd)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = ft_strdup(pwd);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_export(ft_strjoin_ae("OLDPWD=",  oldpwd), env);
		ft_export(ft_strjoin_ae("PWD=", getcwd(NULL, 0)), env);
		getcwd(*cwd, 0);
	}
	free(pwd);
	free(oldpwd);
}*/

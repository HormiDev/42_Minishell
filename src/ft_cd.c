/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:47:36 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/20 22:30:08 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(char **args, t_list **env, t_minishell *minishell)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);//revisar si se puede hacer con minishell->cwd
	if (!args[0])
		path = ft_getenv("HOME", *env);
	else if (args[1])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	else
		path = args[0];
	if (chdir(path) == -1)
		ft_dprintf(2, "cd: %s: %s\n", path, strerror(errno));
	else
	{
		pwd = getcwd(NULL, 0);//revisar para usar alloc lst
		ft_export(ft_strjoin_ae("OLDPWD=",  oldpwd), env);
		ft_export(ft_strjoin_ae("PWD=", pwd), env);
		ft_strlcpy_p(minishell->cwd, pwd, ft_strlen(pwd) + 1);
		free(pwd);//revisar
	}
	free(oldpwd);
}

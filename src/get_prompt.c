/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:59:51 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/11 17:37:54 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_hostname(void)
{
	char *session_manager;
	char **split;
	char **split2;

	session_manager = getenv("SESSION_MANAGER");
	split = ft_split_ae(session_manager, '/');
	split2 = ft_split_ae(split[1], '.');
	return (ft_strdup_ae(split2[0]));
}
static char	*get_current(char *user_name)
{
	char	*cwd;
	char	**split;
	char	*join;
	int		i;

	cwd = getcwd(NULL, 0);
	split = ft_split_ae(cwd, '/');
	if (split[0] && !ft_strncmp_p(split[0], "home", 5) && split[1]
		&& !ft_strncmp_p(split[1], user_name, ft_strlen_p(user_name) + 1))
	{
		join = ft_strdup_ae("~");
		i = 2;
		while (split[i])
		{
			join = ft_strjoin_ae(join, "/");
			join = ft_strjoin_ae(join, split[i++]);
		}
		free(cwd);
		return (join);
	}
	return (cwd);
}
/*
static char	*get_current(char *user_name)
{
	char	*cwd[2];
	char	**split;
	char	*join;
	int		i;

	cwd[0] = getcwd(NULL, 0);
	user_name = ft_strjoin_ae("home/", user_name);
	printf("user_name = %s\n", user_name);
	cwd[1] = ft_strnstr(cwd[0], user_name, ft_strlen_p(cwd[0]));
	free(user_name);
	if (!cwd[1])
		return (cwd[0]);
	split = ft_split_ae(cwd[1], '/');
	join = ft_strdup_ae("~");
	i = 2;
	while (split[i])
	{
		join = ft_strjoin_ae(join, "/");
		join = ft_strjoin_ae(join, split[i++]);
	}
	return (join);
}*/

char	*get_prompt(void)
{
	char *user_name;
	char *host_name;
	char *cwd;
	char prompt[1024];

	user_name = getenv("USER");
	//ft_printf("user_name: %s\n", user_name);
	host_name = get_hostname();
	//ft_printf("host_name: %s\n", host_name);
	cwd = get_current(user_name);
	//ft_printf("cwd: %s\n", cwd);
	ft_sprintf(prompt, "%s%s@%s%s:%s%s%s$ ", BOLD, user_name, host_name, RESET, YELLOW, cwd, RESET);
	//printf("prompt: %s\n", prompt);
	free(cwd);
	return (ft_strdup_ae(prompt));
}
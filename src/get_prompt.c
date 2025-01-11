/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:59:51 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/11 14:36:49 by ide-dieg         ###   ########.fr       */
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

char	*get_prompt(void)
{
	char *user_name;
	char *host_name;
	char *cwd;
	char prompt[1024];

	user_name = getenv("USER");
	ft_printf("user_name: %s\n", user_name);
	host_name = get_hostname();
	ft_printf("host_name: %s\n", host_name);
	cwd = getcwd(NULL, 0);
	ft_printf("cwd: %s\n", cwd);
	ft_sprintf(prompt, "%s%s@%s%s:%s%s%s> %s", BOLD, user_name, host_name, RESET, YELLOW, cwd, RESET, RESET);
	free(cwd);
	return (ft_strdup(prompt));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:59:51 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/11 15:51:31 by dagimeno         ###   ########.fr       */
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
static char	*get_current(void)
{
	char	*cwd;
	char	**split;
	char	*join;
	int		i;

	cwd = getcwd(NULL, 0);
	if (!ft_strncmp_p(cwd, "home/", ft_strlen_p(cwd)) || !ft_strncmp_p(cwd, "/",  ft_strlen_p(cwd)))
		return (cwd);
	split = ft_split_ae(cwd, '/');
	if (!split[2])
		return ("~");
	join = ft_strjoin_p("~/", split[2]);
	i = 3;
	while (split[i])
		join = ft_strjoin_p(join, split[i++]);
	return (join);
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
	cwd = get_current();
	ft_printf("cwd: %s\n", cwd);
	ft_sprintf(prompt, "%s%s@%s%s:%s%s%s> %s", BOLD, user_name, host_name, RESET, YELLOW, cwd, RESET, RESET);
	free(cwd);
	return (ft_strdup(prompt));
}
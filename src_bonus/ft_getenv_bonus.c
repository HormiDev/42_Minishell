/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:37:23 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 22:37:45 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

char	*ft_getenv(char *needle, t_list *envp)
{
	int		len;

	len = ft_strlen_p(needle);
	while (envp)
	{
		if (ft_strncmp_p(((t_env *)envp->content)->name, needle, len + 1) == 0)
			return (((t_env *)envp->content)->value);
		envp = envp->next;
	}
	return (NULL);
}

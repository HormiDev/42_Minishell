/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:27:02 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/13 22:04:53 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

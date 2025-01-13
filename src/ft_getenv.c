/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:27:02 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/13 18:53:17 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getenv(char *needle, char **envp)
{
	int		i;
	int		len;

	len = ft_strlen_p(needle);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp_p(envp[i], needle, len) && envp[i][len + 1] != '=')
			return (&envp[i][len + 1]);
	}
	free(needle);
	return (NULL);
}

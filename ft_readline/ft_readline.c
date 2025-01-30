/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:30:03 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/30 21:20:17 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*ft_readline(char *prompt)
{
	char	*line;

	line = 0;
	if (prompt)
		write(1, prompt, ft_strlen(prompt));
	
	return (line);
}


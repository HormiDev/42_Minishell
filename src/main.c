/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:28:53 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/11 17:08:37 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char *line;
	char *prompt;

	while (1)
	{
		prompt = get_prompt();
		line = ft_input(prompt);
		free(prompt);
		if (!line)
			break;
		if (*line)
		{
			add_history(line);
			//ejecucion de Line
		}
		free(line);
	}
	readline(0);
	rl_clear_history();
	return (0);
}
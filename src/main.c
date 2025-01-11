/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:28:53 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/11 14:05:28 by ide-dieg         ###   ########.fr       */
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
		line = readline(prompt);
		if (!line)
			break;
		add_history(line);
		free(line);
	}
	readline(0);
	rl_clear_history();
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:37:02 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/19 21:40:44 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "../42_Libft/libft.h"

int main()
{
	char *line;


	while (1)
	{
		line = readline("prompt> ");
		printf("line: %s\n", line);
		if (!line)
			break;
		if (ft_strncmp_p(line, "re", 2) == 0)
		{
			sleep(5);
			rl_replace_line("adios", 0);
			rl_redisplay();
			sleep(1);
		}
		add_history(line);
		printf("line: %s\n", line);
		free(line);
	}
	readline(0);
	rl_clear_history();
	printf("History cleared\n");
	return (0);
}

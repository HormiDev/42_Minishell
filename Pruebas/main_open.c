/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:26:04 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/17 20:32:26 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	open("$HOME", O_RDONLY);
	perror("open");
	return (0);
}
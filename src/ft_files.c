/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:21:02 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/11 14:04:11 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_open_files(t_cmd *cmd, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (cmd->infiles[i])
	{
		if (minishell->io_fd[0] > 0)
			close(minishell->io_fd[0]);
		if (((t_redir *)(cmd->infiles[i]))->type == 0)
			minishell->io_fd[0] = open(((t_redir *)(cmd->infiles[i]))->file, O_RDONLY);
		if (minishell->io_fd[0] < 0)
		{
			perror(cmd->infiles[i]->file);//revisar
			strerror(errno);
			minishell->exit_code = 1;
			return ;
		}
		i++;
	}
	i = 0;
	while (cmd->outfiles[i])
	{
		if (minishell->io_fd[1] > 1)
			close(minishell->io_fd[1]);
		if (((t_redir *)(cmd->outfiles[i]))->type == 1)
			minishell->io_fd[1] = open(((t_redir *)(cmd->outfiles[i]))->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (((t_redir *)(cmd->outfiles[i]))->type == 2)
			minishell->io_fd[1] = open(((t_redir *)(cmd->outfiles[i]))->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (minishell->io_fd[1] < 0)
		{
			perror(cmd->outfiles[i]->file);//revisar
			strerror(errno);
			minishell->exit_code = 1;
			return ;
		}
		i++;
	}
}

void	ft_close_files(t_minishell *minishell)
{
	if (minishell->io_fd[0])
		close(minishell->io_fd[0]);
	if (minishell->io_fd[1] > 1)
		close(minishell->io_fd[1]);
	minishell->io_fd[0] = 0;
	minishell->io_fd[1] = 1;
}
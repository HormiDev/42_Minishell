/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:21:02 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/01 03:03:04 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_open_infiles(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->infiles[i])
	{
		if (cmd->io_fd[0] > 0)
			close(cmd->io_fd[0]);
		if (((t_redir *)(cmd->infiles[i]))->type == 0)
			cmd->io_fd[0] = open(((t_redir *)(cmd->infiles[i]))->file,
					O_RDONLY);
		if (cmd->io_fd[0] < 0)
		{
			perror(cmd->infiles[i]->file);//revisar
			strerror(errno);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	ft_open_outfiles(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->outfiles[i])
	{
		if (cmd->io_fd[1] > 1)
			close(cmd->io_fd[1]);
		if (((t_redir *)(cmd->outfiles[i]))->type == 1)
			cmd->io_fd[1] = open(((t_redir *)(cmd->outfiles[i]))->file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (((t_redir *)(cmd->outfiles[i]))->type == 2)
			cmd->io_fd[1] = open(((t_redir *)(cmd->outfiles[i]))->file,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->io_fd[1] < 0)
		{
			perror(cmd->outfiles[i]->file);//revisar
			strerror(errno);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_open_files(t_cmd *cmd)
{
	if (ft_open_infiles(cmd) == -1)
		return (-1);
	if (ft_open_outfiles(cmd) == -1)
		return (-1);
	return (0);
}

void	ft_close_files(t_cmd *cmd)
{
	if (cmd->io_fd[0])
		close(cmd->io_fd[0]);
	if (cmd->io_fd[1] > 1)
		close(cmd->io_fd[1]);
	cmd->io_fd[0] = 0;
	cmd->io_fd[1] = 1;
}

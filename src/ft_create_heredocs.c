/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:57:31 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/10 18:27:07 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_read_here_doc(char *limiter, int here_doc_fd)
{
	char	*line;

	ft_printf("%s > ", limiter);
	line = get_next_line(0);
	if (line && line[0] != 0)
		line[ft_strlen_p(line) - 1] = '\0';
	while (line && ft_strncmp_p(line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		ft_dprintf(here_doc_fd, "%s\n", line);
		free(line);
		ft_printf("%s > ", limiter);
		line = get_next_line(0);
		if (line)
			line[ft_strlen_p(line) - 1] = '\0';
	}
	if (line)
		free(line);
	else
	{
		ft_dprintf(2, "\nwarning: here-document at line 1 delimited by");
		ft_dprintf(2, " end-of-file (wanted «%s»)\n", limiter);
	}
}

void	ft_here_doc(char *limiter, char *file)
{
	int	here_doc_fd;

	here_doc_fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (here_doc_fd == -1)
	{
		perror("open");
		ft_alloc_lst(0, 0);
		exit(1);
	}
	ft_read_here_doc(limiter, here_doc_fd);
	close(here_doc_fd);
	get_next_line(-1);
}

void	ft_create_heredocs(t_list *cmd_list, t_minishell *minishell)
{
	int 	i;
	t_cmd	*cmd;
	char	heredoc[30];
	int		num_heredocs;

	num_heredocs = 0;
	while (cmd_list)
	{
		if (((t_data_container *)(cmd_list->content))->type == 0)
		{
			cmd = (t_cmd *)((t_data_container *)(cmd_list->content))->data;
			i = 0;
			while (cmd->infiles[i])
			{
				if (cmd->infiles[i]->type == 3)
				{
					ft_sprintf(heredoc, "/tmp/heredoc_%d", num_heredocs);
					ft_lstadd_back(&minishell->here_docs, ft_lstnew_ae(ft_strdup_ae(heredoc)));
					ft_here_doc(cmd->infiles[i]->file, ft_lstlast(minishell->here_docs)->content);
					ft_free_alloc(cmd->infiles[i]->file);
					cmd->infiles[i]->file = ft_lstlast(minishell->here_docs)->content;
					cmd->infiles[i]->type = 0;
					num_heredocs++;
				}
				i++;
			}
		}
		cmd_list = cmd_list->next;
	}
}

void	ft_clear_here_docs(t_minishell *minishell)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = minishell->here_docs;
	while (tmp)
	{
		tmp2 = tmp->next;
		unlink(tmp->content);
		ft_free_alloc(tmp->content);
		ft_free_alloc(tmp);
		tmp = tmp2;
	}
	minishell->here_docs = NULL;
}
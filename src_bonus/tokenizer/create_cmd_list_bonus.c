/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:01:50 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/07 13:30:31 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

//borrar funcion
void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("NULL\n");
		return ;
	}
	i = 0;
	if (cmd->infiles && cmd->infiles[i])
		printf(" infiles: ");
	else
		printf(" infiles: NULL ");
	while (cmd->infiles && cmd->infiles[i])
	{
		if ((((t_redir *)cmd->infiles[i])->type) == 0)
			printf("<%s ", cmd->infiles[i]->file);
		else if (((t_redir *)cmd->infiles[i])->type == 3)
			printf("<<%s ", cmd->infiles[i]->file);
		i++;
	}
	i = 0;
	if (cmd->outfiles && cmd->outfiles[i])
		printf(" outfiles: ");
	else
		printf(" outfiles: NULL ");
	while (cmd->outfiles && cmd->outfiles[i])
	{
		if (((t_redir *)cmd->outfiles[i])->type == 1)
			printf(">%s ", cmd->outfiles[i]->file);
		else if (((t_redir *)cmd->outfiles[i])->type == 2)
			printf(">>%s ", cmd->outfiles[i]->file);
		i++;
	}
	i = 0;
	printf(" [cmd: %s] ", cmd->cmd);
	printf(" args: ");
	while (cmd->args && cmd->args[i])
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	printf("\n");
}

void	ft_print_and_or_list(t_list **and_or_list)
{
	int i;

	i = 0;
	while (and_or_list[i])
	{
		ft_print_cmdlist(and_or_list[i]);
		i++;
	}
}

//borrar funcion
void	ft_print_cmdlist(t_list *cmds)
{
	int i=0;

	while (cmds)
	{
		if (((t_data_container *)cmds->content)->type == 0)
		{
			printf("%-4d", i);
			ft_print_cmd((t_cmd *)((t_data_container *)cmds->content)->data);
		}
		else if (((t_data_container *)cmds->content)->type == 1)
		{
			printf("%-4d", i);
			printf("%s\n", (char *)((t_data_container *)cmds->content)->data);	
		}
		else if (((t_data_container *)cmds->content)->type == 2)
		{
			ft_print_cmd((t_cmd *)((t_data_container *)cmds->content)->data);
			printf("%-4d\n   ((((((((((((((((((((((((((((((((((((((((((((((((\n", i);
			ft_print_and_or_list((t_list **)((t_cmd *)((t_data_container *)cmds->content)->data)->and_or_list);
			printf("   ))))))))))))))))))))))))))))))))))))))))))))))))\n");
		}
		i++;
		cmds = cmds->next;
	}
}

static void	ft_create_and_clear_cmds(t_list **list, t_list **cmds, t_list **tmp,
			int *is_cmd)
{
	if (*is_cmd)
	{
		ft_lstadd_back(cmds,
			ft_lstnew_ae(ft_new_data_container(ft_create_cmd(*tmp), 0)));
	}
	if (*list)
		ft_lstadd_back(cmds,
			ft_lstnew_ae(ft_new_data_container
				(ft_strdup_ae((*list)->content), 1)));
	if (*list)
	{
		*tmp = *list;
		*list = (*list)->next;
		(*tmp)->next = NULL;
		ft_free_alloc_lst_clear(tmp, ft_free_alloc);
	}
}

static void	ft_create_cmds_while(t_list **list, t_list **tmp2, int *is_cmd)
{
	while (*list)
	{
		if (!ft_strncmp_p((char *)(*list)->content, "|", 1)
			|| !ft_strncmp_p((char *)(*list)->content, "(", 1)
			|| !ft_strncmp_p((char *)(*list)->content, ")", 1)
			|| !ft_strncmp_p((char *)(*list)->content, "&&", 2)
			|| !ft_strncmp_p((char *)(*list)->content, "\n", 1))
		{
			if (*is_cmd)
				(*tmp2)->next = NULL;
			break ;
		}
		*is_cmd = 1;
		*tmp2 = *list;
		*list = (*list)->next;
	}
}

t_list	*ft_create_cmds(t_list *list)
{
	t_list	*cmds;
	t_list	*tmp;
	t_list	*tmp2;
	int		is_cmd;

	cmds = NULL;
	while (list)
	{
		tmp = list;
		tmp2 = list;
		is_cmd = 0;
		ft_create_cmds_while(&list, &tmp2, &is_cmd);
		ft_create_and_clear_cmds(&list, &cmds, &tmp, &is_cmd);
	}
	return (cmds);
}

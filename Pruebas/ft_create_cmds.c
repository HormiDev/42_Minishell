/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:13:52 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/19 18:49:19 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Funcion que cuenta el numero de redirecciones y comandos en una lista
 * 0 = <, 1 = >, 2 = cmd
 */
void	ft_count_arrays(t_list *list, int *cmd_redir_count)
{
	while (list)
	{
		if (!ft_strncmp_p((char *)list->content, "<", 1))
			cmd_redir_count[0]++;
		else if (!ft_strncmp_p((char *)list->content, ">", 1))
			cmd_redir_count[1]++;
		else
			cmd_redir_count[2]++;
		list = list->next;
	}
}

t_redir	*ft_create_redir(char *str)
{
	t_redir	*new_redir;
	
	new_redir = ft_alloc_lst(sizeof(t_redir), 4);
	if (!ft_strncmp_p(str, ">>", 2))
	{
		new_redir->type = 2;
		new_redir->file = ft_substr_ae(str, 3, ft_strlen_p(str) - 4);
	}
	else if (!ft_strncmp_p(str, ">", 1))
	{
		new_redir->type = 1;
		new_redir->file = ft_substr_ae(str, 2, ft_strlen_p(str) - 3);
	}
	else if (!ft_strncmp_p(str, "<<", 2))
	{
		new_redir->type = 3;
		new_redir->file = ft_substr_ae(str, 3, ft_strlen_p(str) - 4);
	}
	else
	{
		new_redir->type = 0;
		new_redir->file = ft_substr_ae(str, 2, ft_strlen_p(str) - 3);
	}
	return (new_redir);
}

void	ft_create_cmd_while(t_list *list, t_cmd *new_cmd, int *counts)
{
	if (!ft_strncmp_p((char *)list->content, "<", 1))
	{
		new_cmd->infiles[counts[0]] = ft_create_redir((char *)list->content);
		counts[0]++;
	}
	else if(!ft_strncmp_p((char *)list->content, ">", 1))
	{
		new_cmd->outfiles[counts[1]] = ft_create_redir((char *)list->content);
		counts[1]++;
	}
	else
	{
		new_cmd->args[counts[2]] = ft_substr_ae((char *)list->content, 1,
			ft_strlen_p((char *)list->content) - 2);
		counts[2]++;
	}
}

void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->infiles[i])
		printf(" infiles: ");
	else
		printf(" infiles: NULL ");
	while (cmd->infiles[i])
	{
		if ((((t_redir *)cmd->infiles[i])->type) == 0)
			printf("<%s ", cmd->infiles[i]->file);
		else if (((t_redir *)cmd->infiles[i])->type == 3)
			printf("<<%s ", cmd->infiles[i]->file);
		i++;
	}
	i = 0;
	if (cmd->outfiles[i])
		printf(" outfiles: ");
	else
		printf(" outfiles: NULL ");
	while (cmd->outfiles[i])
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
	while (cmd->args[i])
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	printf("\n");
}

t_cmd	*ft_create_cmd(t_list *list)
{
	t_cmd	*new_cmd;
	int 	counts[3];
	
	ft_memset(counts, 0, 3 * sizeof(int));
	new_cmd = ft_alloc_lst(sizeof(t_cmd), 4);
	ft_count_arrays(list, counts);
	new_cmd->args = ft_alloc_lst((counts[2] + 1) * sizeof(char *), 4);
	new_cmd->infiles = ft_alloc_lst((counts[0] + 1) * sizeof(t_redir *), 4);
	new_cmd->outfiles = ft_alloc_lst((counts[1] + 1) * sizeof(t_redir *), 4);
	ft_memset(counts, 0, 3 * sizeof(int));
	while (list)
	{
		ft_create_cmd_while(list, new_cmd, counts);
		list = list->next;
	}
	new_cmd->cmd = new_cmd->args[0];
	//ft_print_cmd(new_cmd);
	return (new_cmd);
}

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
		else
		{
			printf("%-4d", i);
			printf("%s\n", (char *)((t_data_container *)cmds->content)->data);	
		}
		i++;
		cmds = cmds->next;
	}
}
/**
 * @brief Funcion que crea un contenedor de datos
 * type = 0 -> t_cmd
 * type = 1 -> char *
 * 
 * @param data
 * @param type
*/
t_data_container *ft_new_data_container(void *data, int type)
{
	t_data_container *data_container;

	data_container = ft_alloc_lst(sizeof(t_data_container), 4);
	data_container->data = data;
	data_container->type = type;
	return (data_container);
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
		while (list)
		{
			if (!ft_strncmp_p((char *)list->content, "|", 1)
				|| !ft_strncmp_p((char *)list->content, "(", 1)
				|| !ft_strncmp_p((char *)list->content, ")", 1)
				|| !ft_strncmp_p((char *)list->content, "&&", 2)
				|| !ft_strncmp_p((char *)list->content, "\n", 1))
			{
				if (is_cmd)
					tmp2->next = NULL;
				break;
			}
			is_cmd = 1;
			tmp2 = list;
			list = list->next;
		}
		if (is_cmd)
			ft_lstadd_back(&cmds, ft_lstnew_ae(ft_new_data_container(ft_create_cmd(tmp), 0)));
		if (list)
			ft_lstadd_back(&cmds, ft_lstnew_ae(ft_new_data_container(ft_strdup_ae(list->content), 1)));
		//liberar lista tmp
		tmp = list;
		if (list)
			list = list->next;
		//liberar lista tmp
	}
	ft_print_cmdlist(cmds);
	ft_free_alloc_lst_clear(&list, ft_free_alloc);
	return (cmds);
}

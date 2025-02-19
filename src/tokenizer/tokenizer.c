/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:58:26 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/19 20:47:51 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//borrar funcion
void	ft_print(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s,", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
}

int	ft_check_redirections(t_list *list)
{
	while (list)
	{
		if ((*(char *)list->content == '>' || *(char *)list->content == '<')
			&& (!list->next || *(char *)list->next->content != '"'))
		{
			ft_print_syntax_error_message((char *)list->content);
			return (0);
		}
		list = list->next;
	}
	return (1);
}

void	ft_join_redirections(t_list *list)
{
	char	*tmp;
	t_list	*tmp_list;

	while (list)
	{
		if (*(char *)list->content == '>' || *(char *)list->content == '<')
		{
			tmp = ft_alloc_lst(ft_strlen_p((char *)list->content)
					+ ft_strlen_p((char *)list->next->content) + 3, 3);
			sprintf(tmp, "\"%s%s\"", (char *)list->content,
				(char *)list->next->content);
			ft_free_alloc(list->content);
			list->content = tmp;
			tmp_list = list->next;
			list->next = list->next->next;
			ft_free_alloc(tmp_list->content);
			ft_free_alloc(tmp_list);
		}
		list = list->next;
	}
}

static int	ft_tokenizer_while(char *str, t_list **list, int *i, int *start)
{
	int		size;

	size = ft_is_special_token(&str[*i]);
	if (size == -1)
	{
		ft_dprintf(2, "%sminishell: syntax error open quotes%s\n", RED, RESET);
		return (0);
	}
	if (size)
	{
		if (*i != 0)
		{
			if (*i - *start)
				ft_lstadd_back(list, ft_lstnew_ae(ft_substr_ae(str, *start,
							*i - *start)));
			ft_lstadd_back(list, ft_lstnew_ae(ft_substr_ae(str, *i, size)));
		}
		else
			ft_lstadd_back(list, ft_lstnew_ae(ft_substr_ae(str, *start, size)));
		(*start) = *i + size;
		(*i) += size;
	}
	else
		(*i)++;
	return (1);
}

t_list	*ft_tokenizer(char *str)
{
	t_list	*list;
	int		i;
	int		start;

	list = NULL;
	i = 0;
	start = 0;
	while (str[i])
	{
		if (!ft_tokenizer_while(str, &list, &i, &start))
			return (NULL);
	}
	if (i - start)
		ft_lstadd_back(&list, ft_lstnew_ae
			(ft_substr_ae(str, start, i - start)));
	ft_put_quotes(list);
	if (!ft_check_token_list(&list))
	{
		ft_free_alloc_lst_clear(&list, ft_free_alloc);
		return (NULL);
	}
	ft_remove_quotes(list);
	return (list);
}

//borrar funcion
int	main(void)
{
	t_list	*list;
	char	*line;

	//line = ft_input("minishell$ ");
	line = readline("minishell$ ");
	add_history(line);
	while (line)
	{
		list = ft_tokenizer(line);
		if (list)
		{
			ft_print(list);
			ft_create_cmds(list);
		}
		free(line);
		//line = ft_input("minishell$ ");
		line = readline("minishell$ ");
		if (!ft_strncmp_p(line, "exit", 4))
			break ;
		add_history(line);
	}
	free(line);
	rl_clear_history();
	ft_alloc_lst(0, 0);
	return (0);
}

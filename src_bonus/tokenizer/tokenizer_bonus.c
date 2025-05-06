/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:22:23 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 21:22:27 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

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
			ft_sprintf(tmp, "\"%s%s\"", (char *)list->content,
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

char	*ft_search_variable(char *str, t_minishell *mini)
{
	t_list	*tmp;

	if (str[0] == 0)
		return (ft_strdup_ae("$"));
	if (str[0] == '?')
		return (ft_add_to_alloc_lst_e(ft_itoa(mini->exit_code)));
	tmp = mini->envp;
	while (tmp)
	{
		if (ft_strncmp_p(((t_env *)tmp->content)->name,
				str, ft_strlen_p(str) + 1) == 0)
			return (ft_strdup_ae(((t_env *)tmp->content)->value));
		tmp = tmp->next;
	}
	return (ft_strdup_ae(""));
}

t_list	*ft_tokenizer(char *str, t_minishell *minishell)
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
	ft_unquoted_dollar_variable_converter(list, minishell);
	ft_put_quotes(list);
	if (!ft_check_token_list(&list, minishell))
	{
		ft_free_alloc_lst_clear(&list, ft_free_alloc);
		return (NULL);
	}
	ft_remove_quotes(list);
	return (list);
}

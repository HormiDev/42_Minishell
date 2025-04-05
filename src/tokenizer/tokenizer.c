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
		if (ft_strncmp_p(((t_env *)tmp->content)->name, str, ft_strlen_p(str) + 1) == 0)
			return (ft_strdup_ae(((t_env *)tmp->content)->value));
		tmp = tmp->next;
	}
	return (ft_strdup_ae(""));
}

int	ft_end_var(char *str)
{
	int		i;

	i = 1;
	if (str[i] == '?')
		return (i + 1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

void	ft_unquoted_dollar_variable_converter(t_list *list, t_minishell *mini)
{
	char *dollar;
	char *var;
	int var_end;
	t_list *tmp;
	char **split_var;

	while (list)
	{
		if (ft_strncmp_p((char *)list->content, "$", 2) == 0)
		{
			list = list->next;
			continue ;
		}
		dollar = ft_strchr_p((char *)list->content, '$');
		if (dollar && *(char *)list->content != '\''
			&& *(char *)list->content != '\"')
		{
			if (*(char *)list->content != '$')
			{
				var = ft_strdup_ae(dollar);
				dollar[0] = '\0';
				tmp = list->next;
				list->next = ft_lstnew_ae(var);
				list->next->next = tmp;
				list = list->next;
				dollar = ft_strchr_p((char *)list->content, '$');
			}
			var_end = ft_end_var(dollar);
			if (dollar[var_end] != 0)
			{
				tmp = list->next;
				list->next = ft_lstnew_ae(ft_strdup_ae(&dollar[var_end]));
				list->next->next = tmp;
				dollar[var_end] = '\0';
			}
			var = ft_search_variable(&dollar[1], mini);
			ft_free_alloc(list->content);
			if (*var)
			{
				if (ft_strchr_p(" \t\n\r\f\v", var[0]))
				{
					list->content = ft_strdup_ae(" ");
					tmp = list->next;
					list->next = ft_lstnew_ae(ft_strdup_ae(""));
					list->next->next = tmp;
					list = list->next;
				}
				else
					list->content = ft_strdup_ae("");
				if (ft_strchr_p(" \t\n\r\f\v", var[ft_strlen_p(var) - 1]))
				{
					tmp = list->next;
					list->next = ft_lstnew_ae(ft_strdup_ae(" "));
					list->next->next = tmp;
				}
				split_var = ft_split_chars_ae(var, " \t\n\r\f\v");
				var_end = 0;
				while (split_var[var_end])
				{
					tmp = list->next;
					list->next = ft_lstnew_ae(split_var[var_end]);
					list->next->next = tmp;
					list = list->next;
					var_end++;
					if (split_var[var_end])
					{
						tmp = list->next;
						list->next = ft_lstnew_ae(ft_strdup_ae(" "));
						list->next->next = tmp;
						list = list->next;
					}
				}
			}
			else
			{
				ft_free_alloc(var);
				list->content = ft_strdup_ae("");
			}
		}
		list = list->next;
	}
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

//borrar funcion
/*int	main(void)
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
*/
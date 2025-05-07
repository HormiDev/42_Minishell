/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:07:05 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/18 15:43:25 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	*ft_parse_var(char *str, int *i, t_minishell *mini)
{
	size_t	len;
	char	*var;

	if (str[0] == '?')
	{
		(*i)++;
		return (ft_add_to_alloc_lst_e(ft_itoa(mini->exit_code)));
	}
	len = 0;
	while (str[len] == '_' || ft_isalnum(str[len]))
	{
		len++;
		(*i)++;
	}
	if (len == 0)
		return ("$");
	var = ft_substr_ae(str, 0, len);
	return (ft_getenv(var, mini->envp));
}

static void	ft_put_single_quotes(t_list *list)
{
	char	*str;

	if (*(char *)list->content == ' ' || *(char *)list->content == '\t')
		list = list->next;
	while (list
		&& (*(char *)list->content == '\'' || *(char *)list->content == '\"'))
	{
		if (*(char *)list->content == '\"'
			&& ft_strchr((char *)list->content, '$'))
		{
			str = ft_substr_ae((char *)list->content, 1,
					ft_strlen_p((char *)list->content) - 2);
			ft_sprintf(list->content, "\'%s\'", str);
			ft_free_alloc(str);
		}
		list = list->next;
	}
}

static char	*ft_split_and_join(char *str, char *var, int *i)
{
	char	*substr[2];
	char	*jointed_str;

	substr[0] = ft_substr_ae(str, 0, i[1]);
	substr[1] = ft_strjoin_ae(substr[0], var);
	jointed_str = ft_strjoin_ae(substr[1], &str[i[0]]);
	i[0] = ft_strlen_p(substr[1]);
	ft_free_alloc(substr[0]);
	ft_free_alloc(substr[1]);
	return (jointed_str);
}

void	ft_dollar_variable_converter(t_list *list, t_minishell *mini)
{
	int		i[2];
	char	*var;

	while (list)
	{
		if (!ft_strncmp_p((char *)list->content, "<<", 2) && list->next)
			ft_put_single_quotes(list->next);
		if (*(char *)list->content != '\'')
		{
			i[0] = 0;
			while (((char *)list->content)[i[0]])
			{
				if (((char *)list->content)[i[0]++] == '$')
				{
					i[1] = i[0] - 1;
					var = ft_parse_var(&((char *)list->content)[i[0]],
							&i[0], mini);
					if (!ft_strncmp_p(var, "$", 2))
						continue ;
					list->content = ft_split_and_join(list->content, var, i);
				}
			}
		}
		list = list->next;
	}
}

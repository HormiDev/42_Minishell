/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:58:26 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/24 14:00:33 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

int	ft_manage_spaces(char *c)
{
	int	size;

	size = 0;	
	while (!ft_strncmp_p(c, " ", 1) || !ft_strncmp_p(c, "\t", 1))
	{
		c++;
		size++;
	}
	return (size);
}

int	ft_manage_quotes(char *c)
{
	int		size;
	char	quote;

	size = 1;
	quote = *c;
	c++;
	while (*c != quote)
	{
		if (*c == '\0')
			return (-1);
		c++;
		size++;
	}
	return (++size);
}

int	ft_is_special_token(char *c)
{
	int	size;

	size = 0;
	if (!ft_strncmp_p(c, ">>", 2) || !ft_strncmp_p(c, "<<", 2)
		|| !ft_strncmp_p(c, "||", 2) || !ft_strncmp_p(c, "&&", 2))
		return (2);
	if (!ft_strncmp_p(c, ">", 1) || !ft_strncmp_p(c, "<", 1)
		|| !ft_strncmp_p(c, "|", 1) || !ft_strncmp_p(c, "(", 1)
		|| !ft_strncmp_p(c, ")", 1) || !ft_strncmp_p(c, "$", 1)
		|| !ft_strncmp_p(c, "\n", 1))
		return (1);
	if (!ft_strncmp_p(c, " ", 1) || !ft_strncmp_p(c, "\t", 1))
		size = ft_manage_spaces(c);
	if (!ft_strncmp_p(c, "'", 1) || !ft_strncmp_p(c, "\"", 1))
		size = ft_manage_quotes(c);
	return (size);
}

void ft_print (t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s,", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
}

t_list	*ft_split_tokenizer_lst(char *str/*, t_list *envp*/)
{
	t_list	*list;
	int		i;
	int 	start;
	int		size;

	list = NULL;
	i = 0;
	start = 0;
	while (str[i])
	{
		size = ft_is_special_token(&str[i]);
		if (size == -1)
		{
			ft_dprintf(2, "%sminishell: syntax error open quotes%s\n", RED, RESET);
			return (NULL);
		}
		if (size)
		{
			if (i != 0)
			{
				if (i - start)
					ft_lstadd_back(&list, ft_lstnew_ae(ft_substr_ae(str, start, i - start)));
				ft_lstadd_back(&list, ft_lstnew_ae(ft_substr_ae(str, i, size)));
			}
			else
				ft_lstadd_back(&list, ft_lstnew_ae(ft_substr_ae(str, start, size)));
			start = i + size;
			i += size;
		}
		else
			i++;	
	}
	if (i - start)
		ft_lstadd_back(&list, ft_lstnew_ae(ft_substr_ae(str, start, i - start)));
	return (list);
}

int main()
{
	t_list *list;
	char *line;

	line = readline("minishell$ ");
	add_history(line);
	while(line)
	{
		list = ft_split_tokenizer_lst(line);
		if (list)
			ft_print(list);
		line = readline("minishell$ ");
		add_history(line);
	}
	rl_clear_history();
	ft_alloc_lst(0,0);
	return (0);
}
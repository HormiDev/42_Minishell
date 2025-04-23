
#include "../../include/minishell.h"

static char	*ft_get_var(char *dollar, t_list **list, t_minishell *mini)
{
	char	*var;
	t_list	*tmp;
	int		var_end;

	if (*(char *)(*list)->content != '$')
	{
		var = ft_strdup_ae(dollar);
		dollar[0] = '\0';
		tmp = (*list)->next;
		(*list)->next = ft_lstnew_ae(var);
		(*list)->next->next = tmp;
		*list = (*list)->next;
		dollar = ft_strchr_p((char *)(*list)->content, '$');
	}
	var_end = ft_end_var(dollar);
	if (dollar[var_end] != 0)
	{
		tmp = (*list)->next;
		(*list)->next = ft_lstnew_ae(ft_strdup_ae(&dollar[var_end]));
		(*list)->next->next = tmp;
		dollar[var_end] = '\0';
	}
	return (ft_search_variable(&dollar[1], mini));
}

static void	ft_split_loop(t_list **list, char **split_var)
{
	t_list	*tmp;
	int		var_end;

	var_end = 0;
	while (split_var[var_end])
	{
		tmp = (*list)->next;
		(*list)->next = ft_lstnew_ae(split_var[var_end]);
		(*list)->next->next = tmp;
		*list = (*list)->next;
		var_end++;
		if (split_var[var_end])
		{
			tmp = (*list)->next;
			(*list)->next = ft_lstnew_ae(ft_strdup_ae(" "));
			(*list)->next->next = tmp;
			*list = (*list)->next;
		}
	}
}

static void	ft_split_var(char *var, t_list **list)
{
	t_list	*tmp;
	char	**split_var;

	if (ft_strchr_p(" \t\n\r\f\v", var[0]))
	{
		(*list)->content = ft_strdup_ae(" ");
		tmp = (*list)->next;
		(*list)->next = ft_lstnew_ae(ft_strdup_ae(""));
		(*list)->next->next = tmp;
		*list = (*list)->next;
	}
	else
		(*list)->content = ft_strdup_ae("");
	if (ft_strchr_p(" \t\n\r\f\v", var[ft_strlen_p(var) - 1]))
	{
		tmp = (*list)->next;
		(*list)->next = ft_lstnew_ae(ft_strdup_ae(" "));
		(*list)->next->next = tmp;
	}
	split_var = ft_split_chars_ae(var, " \t\n\r\f\v");
	ft_split_loop(list, split_var);
}

static void	ft_man_dollar_var(t_list *list, char *dollar, t_minishell *mini)
{
	char	*var;

	var = ft_get_var(dollar, &list, mini);
	ft_free_alloc(list->content);
	if (*var)
		ft_split_var(var, &list);
	else
	{
		ft_free_alloc(var);
		list->content = ft_strdup_ae("");
	}
}

void	ft_unquoted_dollar_variable_converter(t_list *list, t_minishell *mini)
{
	char	*dollar;

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
			ft_man_dollar_var(list, dollar, mini);
		list = list->next;
	}
}


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

void	ft_unquoted_dollar_variable_converter(t_list *list, t_minishell *mini)
{
	char	*dollar;
	char	*var;
	int		var_end;
	t_list	*tmp;
	char	**split_var;

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

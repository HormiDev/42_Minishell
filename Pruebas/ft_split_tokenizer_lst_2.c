/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:07:05 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/24 20:08:07 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_getenv_2(char *needle/*, t_list *envp*/)
{
	if (*needle == 0)
		return (NULL);
	return (ft_strdup_ae("SOY_UNA_VARIABLE"));
}

char	*ft_parse_var(char *str)
{
	size_t	len;
	char	*var;

	len = 0;
	printf("STR: %s\n", str);
	while (str[len] && str[len] != ' '
		&& str[len] != '\t' && str[len] != '$')
		len++;
	printf("Len: %zu\n", len);
	if (len == 0)
		return ("$");
	printf("LEN: %zu\n", len);
	var = ft_substr_ae(str, 0, len);
	printf("VAR: %s\n", var);
	if (!ft_strncmp_p(var, "?", 1))
		return (ft_getenv_2(var));//hay que cambiar el valor de retorno de esta linea, se usa el ft_getenv solo para pruebas
	return (ft_getenv_2(var));
}

char	*split_and_join(char *str, char *var)
{
	int		len;

	len = 0;
	while (str[len] != '$')
		len++;
	len++;
	return (ft_strjoin_ae(ft_strjoin_ae(ft_substr_ae(str, 0, len), var), &str[len]));
}

void	dollar_variable_converter(t_list *list)
{
	int		i;
	char	*var;
	t_list	*tmp;

	tmp = list;
	while (list)
	{
		if (*(char *)list->content != '\'')
		{

			i = 0;
			while (((char *)list->content)[i])
			{
				if (((char *)list->content)[i] == '$')
				{
					printf("ENTRO\n");
					var = ft_parse_var(&((char *)list->content)[i + 1]);
					printf("var: %s\n", var);
					list->content = split_and_join(list->content, var);
				}
				i++;
			}
		}
		list = list->next;
	}
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

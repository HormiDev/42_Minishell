/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:07:05 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/24 21:36:46 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_getenv_2(char *needle)
{
	if (*needle == 0)
		return (NULL);
	return (ft_strdup_ae("SOY_UNA_VARIABLE_DE_PRUEBA"));
}

char	*ft_parse_var(char *str, int *i)
{
	size_t	len;
	char	*var;

	len = 0;
	(*i)++;
	while (str[len] && str[len] != ' ' && str[len] != '"'
		&& str[len] != '\t' && str[len] != '$')
	{
		len++;
		(*i)++;
	}
	if (len == 0)
		return ("$");
	var = ft_substr_ae(str, 0, len);
	if (!ft_strncmp_p(var, "?", 1))
		return (ft_getenv_2(var));//hay que cambiar el valor de retorno de esta linea, se usa el ft_getenv solo para pruebas
	return (ft_getenv_2(var));
}

char	*split_and_join(char *str, char *var, int i)
{
	int		len;
	char	*substr;

	len = 0;
	while (str[len] != '$')
		len++;
	substr = ft_substr_ae(str, 0, len);
	return (ft_strjoin_ae(ft_strjoin_ae(substr, var), &str[i]));
}

void	dollar_variable_converter(t_list *list)
{
	int		i;
	char	*var;

	//t_list *tmp = list;
	while (list)
	{
		if (*(char *)list->content != '\'')
		{
			i = 0;
			while (((char *)list->content)[i])
			{
				if (((char *)list->content)[i] == '$')
				{
					var = ft_parse_var(&((char *)list->content)[i + 1], &i);
					list->content = split_and_join(list->content, var, i);
				}
				else
					i++;
			}
		}
		list = list->next;
	}
	/*while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}*/
}

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

//borrar esta funcion
/*static char	*ft_getenv_2(char *needle)
{
	if (*needle == 0)
		return (NULL);
	return (ft_strdup_ae("SOY_UNA_VARIABLE_DE_PRUEBA"));
}*/

/**
* @brief Funcion que obtiene el nombre de la variable de entorno
* @example $HOME, -> HOME
* @param str Cadena de texto
* @param i Indice de la cadena de texto
* @return char* Nombre de la variable de entorno
*/
static char	*ft_parse_var(char *str, int *i, t_minishell *mini)
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
			sprintf(list->content, "\'%s\'", str);
			ft_free_alloc(str);
		}
		list = list->next;
	}
}

static char	*ft_split_and_join(char *str, char *var, int i)
{
	int		len;
	char	*substr;
	char	*jointed_str;

	len = 0;
	while (str[len] != '$')
		len++;
	substr = ft_substr_ae(str, 0, len);
	jointed_str = ft_strjoin_ae(ft_strjoin_ae(substr, var), &str[i]);
	ft_free_alloc(substr);
	return (jointed_str);
}

/**
* @brief Funcion que convierte las variables de entorno en su valor
* @example $HOME -> /home/user
* @param list Lista de tokens
* @return void
*/
void	ft_dollar_variable_converter(t_list *list, t_minishell *mini)
{
	int		i;
	char	*var;

	while (list)
	{
		if (!ft_strncmp_p((char *)list->content, "<<", 2) && list->next)
			ft_put_single_quotes(list->next);
		if (*(char *)list->content != '\'')
		{
			i = 0;
			while (((char *)list->content)[i])
			{
				if (((char *)list->content)[i] == '$')
				{
					i++;
					var = ft_parse_var(&((char *)list->content)[i], &i, mini);
					list->content = ft_split_and_join(list->content, var, i);
					i = ft_strlen_p(var);
				}
				else
					i++;
			}
		}
		list = list->next;
	}
}

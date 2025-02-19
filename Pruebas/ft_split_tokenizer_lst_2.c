/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:07:05 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/18 15:43:25 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_getenv_2(char *needle)
{
	if (*needle == 0)
		return (NULL);
	return (ft_strdup_ae("SOY_UNA_VARIABLE_DE_PRUEBA"));
}

/**
* @brief Funcion que obtiene el nombre de la variable de entorno
* @example $HOME, -> HOME
* @param str Cadena de texto
* @param i Indice de la cadena de texto
* @return char* Nombre de la variable de entorno
*/
char	*ft_parse_var(char *str, int *i)
{
	size_t	len;
	char	*var;

	len = 0;
	(*i)++;
	while (str[len] == '_' || ft_isalnum(str[len]))
	{
		len++;
		(*i)++;
	}
	if (len == 0)
		return ("$");
	var = ft_substr_ae(str, 0, len);
	if (!ft_strncmp_p(var, "?", 1))
		return (ft_getenv_2(var));//hay que cambiar el valor de retorno de esta linea, se usa el ft_getenv solo para pruebas
	return (ft_getenv_2(var));//aqi lo mism, hay que pasar el ft_getenv original
}

char	*ft_split_and_join(char *str, char *var, int i)
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
void	ft_dollar_variable_converter(t_list *list)
{
	int		i;
	char	*var;

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
					list->content = ft_split_and_join(list->content, var, i);
					ft_free_alloc(var);
				}
				else
					i++;
			}
		}
		list = list->next;
	}
}

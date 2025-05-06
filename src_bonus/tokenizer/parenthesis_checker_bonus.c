/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_checker_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:18:44 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 21:18:46 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

/**
 * @file ft_parenthesis_checker.c
 * @brief Verifica si hay instrucciones después de los tokens.
 * 
 * Esta función se encarga de analizar una secuencia de tokens y determinar si
 * existen instrucciones válidas antes del cierra de paréntesis.
 * 
 * @param tks Puntero a la estructura de tokens que se va a analizar.
 */
int	ft_check_instructions_after_parenthesis(t_list *tks)
{
	int		parenthesis;
	char	*content;

	parenthesis = 0;
	while (tks)
	{
		content = (char *)tks->content;
		if (*content == ')')
			parenthesis++;
		else if (parenthesis > 0 && (*content == '"'
				|| *content == '\'' || *content == '('))
		{
			ft_print_syntax_error_message(tks->content);
			return (1);
		}
		else if (*content == '&' || *content == '|')
			parenthesis = 0;
		tks = tks->next;
	}
	return (0);
}

/**
 * @file ft_parenthesis_checker.c
 * @brief Verifica si hay instrucciones antes de los tokens.
 * 
 * Esta función se encarga de analizar una secuencia de tokens y determinar si
 * existen instrucciones válidas antes de la apertura de paréntesis.
 * 
 * @param tks Puntero a la estructura de
 */
int	ft_check_instructions_before_parenthesis(t_list *tks)
{
	int	instructions;

	instructions = 0;
	while (tks)
	{
		if (*(char *)tks->content == '"' || *(char *)tks->content == '\''
			|| *(char *)tks->content == ')')
			instructions++;
		if (*(char *)tks->content == '|' || *(char *)tks->content == '&')
			instructions = 0;
		if (instructions > 0 && *(char *)tks->content == '(')
		{
			ft_print_syntax_error_message(tks->content);
			return (1);
		}
		tks = tks->next;
	}
	return (0);
}

/**
 * @file ft_parenthesis_checker.c
 * @brief Verifica si hay operadores lógicos dentro de los paréntesis.
 * 
 * Esta función se encarga de analizar una secuencia de tokens y determinar si
 * existen operadores lógicos dentro de los paréntesis.
 * 
 * @param tks Puntero a la estructura de tokens que se va a analizar.
 */
int	ft_are_logic_operators_inside_parenthesis(t_list *tks)
{
	int	open_parenthesis;

	open_parenthesis = 1;
	while (open_parenthesis)
	{
		if (*(char *)tks->content == '(')
			open_parenthesis++;
		if (*(char *)tks->content == ')')
			open_parenthesis--;
		if (open_parenthesis == 1
			&& (*(char *)tks->content == '&'
				|| !ft_strncmp_p(tks->content, "||", 2)))
			return (1);
		tks = tks->next;
	}
	return (0);
}

/**
 * @file ft_parenthesis_checker.c
 * @brief Verifica si hay paréntesis redundantes.
 * 
 * Esta función se encarga de analizar una secuencia de tokens y determinar si
 * existen paréntesis redundantes.
 * 
 * @param tks Puntero a la estructura de tokens que se va a analizar.
 */
int	ft_check_for_redundant_parenthesis(t_list *tks)
{
	while (tks)
	{
		if (*(char *)tks->content == '(')
		{
			if (!ft_are_logic_operators_inside_parenthesis(tks->next))
			{
				ft_print_syntax_error_message(tks->content);
				return (1);
			}
		}
		tks = tks->next;
	}
	return (0);
}

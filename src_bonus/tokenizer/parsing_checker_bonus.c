/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:16:20 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 21:16:33 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	ft_print_syntax_error_message(char *token)
{
	ft_dprintf(2, "%sminishell: syntax error near unexpected token `%s'%s\n",
		RED, token, RESET);
}

/**
 * @file ft_parenthesis_checker.c
 * @brief Verifica si hay paréntesis abiertos y cerrados.
 * 
 * Esta función se encarga de analizar una secuencia de tokens y determinar si
 * existen paréntesis abiertos y cerrados. Si hay un paréntesis cerrado sin un
 * paréntesis abierto, se imprime un mensaje de error.
 * 
 * @param tks Puntero a la estructura de tokens que se va a analizar.
 */
int	ft_check_parenthesis(t_list *tks)
{
	int	parenthesis;
	int	strings;

	parenthesis = 0;
	strings = 0;
	while (tks)
	{
		if (*(char *)tks->content == '\'' || *(char *)tks->content == '"')
			strings++;
		if (*(char *)tks->content == '(')
		{
			parenthesis++;
			strings = 0;
		}
		if (*(char *)tks->content == ')')
		{
			if (!strings)
				return (-1);
			parenthesis--;
		}
		if (parenthesis < 0)
			break ;
		tks = tks->next;
	}
	return (parenthesis);
}

/**
 * @file ft_parenthesis_checker.c
 * @brief Verifica si hay instrucciones después de los tokens.
 * 
 * Esta función se encarga de analizar si despues de un string o un cierre de
 * paréntesis hay un operador lógico o de redirección. |, ||, &&.
 * 
 * @param tks Puntero a la estructura de tokens que se va a analizar.
 */
int	ft_verify_correct_order_onwards(t_list *tks)
{
	int		instructions_after;

	instructions_after = 0;
	while (tks)
	{
		if (*(char *)tks->content == '"' || *(char *)tks->content == '\''
			|| *(char *)tks->content == ')')
			instructions_after++;
		if (*(char *)tks->content == '&' || *(char *)tks->content == '|')
		{
			if (instructions_after <= 0)
			{
				ft_print_syntax_error_message(tks->content);
				return (1);
			}
			instructions_after = 0;
		}
		tks = tks->next;
	}
	return (0);
}

/**
 * @file ft_parenthesis_checker.c
 * @brief Verifica si hay instrucciones después de los tokens.
 * 
 * Esta función se encarga de analizar si antes de un string o un apertura de
 * paréntesis hay un operador lógico o de redirección. |, ||, &&, <, >, >>, <<.
 * 
 * @param tks Puntero a la estructura de tokens que se va a analizar.
 */
int	ft_check_tokens_after_special_found(t_list *tks, int *instructions_last)
{
	while (tks)
	{
		if (*(char *)tks->content == '"' || *(char *)tks->content == '\''
			|| *(char *)tks->content == '(')
			(*instructions_last)++;
		if (*(char *)tks->content == '&' || *(char *)tks->content == '|'
			|| *(char *)tks->content == '<' || *(char *)tks->content == '>')
		{
			if (*instructions_last <= 0)
			{
				ft_print_syntax_error_message(tks->content);
				return (1);
			}
			*instructions_last = 0;
		}
		if (!tks->next)
			return (0);
		tks = tks->next;
	}
	return (0);
}

/**
 * @file ft_parenthesis_checker.c
 * @brief Verifica si hay instrucciones después de los tokens.
 * 
 * Esta función se encarga de analizar una secuencia de tokens y determinar si
 * existen instrucciones válidas después de los tokens de |, ||, &&.
 * 
 * @param tks Puntero a la estructura de tokens que se va a analizar.
 */
int	ft_verify_correct_order_backwards(t_list *tks)
{
	int		instructions_last;

	instructions_last = 0;
	while (tks && (*(char *)tks->content != '&'
			&& *(char *)tks->content != '|'))
		tks = tks->next;
	if (!tks)
		return (0);
	if (tks->next)
	{
		tks = tks->next;
		if (ft_check_tokens_after_special_found(tks, &instructions_last))
			return (1);
	}
	if (instructions_last <= 0)
	{
		ft_print_syntax_error_message(tks->content);
		return (1);
	}
	return (0);
}

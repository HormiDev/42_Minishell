/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:47:45 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/21 17:59:52 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_minisplit(char *str, char c)
{
	char	**array;
	int		i;
	int		j;
	int		k;

	array = ft_alloc_lst(sizeof(char *), 3);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			k = i;
			while (str[i] && str[i] != c)
				i++;
			array[j] = ft_substr_ae(str, k, i - k);
			j++;
		}
	}
	array[j] = NULL;
	return (array);
}
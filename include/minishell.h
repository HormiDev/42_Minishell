/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:34:17 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/13 20:25:12 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../42_Libft/libft.h"
# include "colors.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef	struct s_envp 
{
	char			*key;
	char			*value;
	char			*line;
	struct s_envp	*next;
}	t_envp;

typedef struct s_minishell
{
	char			*user;
	char			*host;
	char			*cwd;
	char			prompt[1024];// revisar tamaño maximo posible
	char			**envp;// cambiar a formato lista
	//t_envp			*envp;
}	t_minishell;

t_minishell	*ft_loading_minishell(char **envp);
char		*ft_getenv(char *needle, char **envp);
void		ft_update_prompt(t_minishell *minishell);

#endif


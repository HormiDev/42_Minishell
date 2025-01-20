/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:34:17 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/20 22:01:06 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../42_Libft/libft.h"
# include "colors.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <errno.h>

typedef	struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_minishell
{
	char			*user;
	char			*host;
	char			cwd[PATH_MAX];
	char			cwd_short[PATH_MAX];
	char			prompt[PATH_MAX + 1024];// revisar tamaño maximo posible
	t_list			*envp;
}	t_minishell;

typedef struct s_tree
{
	char			*commands;
	struct s_tree	*branches;
}	t_tree;

void		clean_and_exit(int exit_code);
void		ft_array_to_list(char **envp, t_list **envp_list);
void		ft_cd(char **args, t_list **env, t_minishell *minishell);
void		ft_echo(char **args);
void		ft_export(char *envp, t_list **envp_list);
t_minishell	*ft_loading_minishell(char **envp);
char		*ft_getenv(char *needle, t_list *envp);
void		ft_update_prompt(t_minishell *minishell);
void		ft_print_env(t_list *env);
void		ft_export(char *envp, t_list **envp_list);
void		ft_export_args(char **args, t_list **env_list);
void		ft_exit(char **arg);
void		ft_pwd(t_minishell *minishell);
void		ft_unset(char *envp, t_list **env_list);
void		ft_unset_args(char **args, t_list **env_list);
void		mini_exec(char *command, char **args, t_minishell *minishell);
void		ft_parsing_and_exec(char *line, t_minishell *minishell);

#endif


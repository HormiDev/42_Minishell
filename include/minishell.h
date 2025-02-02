/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:34:17 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/02 20:58:13 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../42_Libft/libft.h"
# include "colors.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <sys/wait.h>
# include <errno.h>

typedef	struct s_env
{
	char	*name;
	char	*value;
	char	*full;
}	t_env;

typedef struct s_minishell
{
	char			*line;
	char			*user;
	char			*host;
	char			cwd[PATH_MAX];
	char			cwd_short[PATH_MAX];
	char			prompt[PATH_MAX + 1024];// revisar tamaño maximo posible
	int				exit_code;
	t_list			*envp;
	char			**envp_array;
}	t_minishell;

typedef struct s_building
{
	t_list	*content;
	int		id;
	int		id_parent;
	int		level;
	int		status;
	int		separator;  //el tipo de separador que sigue al nodo, puede ser 0(no hay separador), 1(&&) o 2(||) 0  
	int		redirection; //el tipo de accion a ejecutar 0(nada), 1 (|), 2 (<), 3(>), 4(<<), 5(>>)
	struct s_building	*upper_floor;
	struct s_building	*lower_floor;
	struct s_building	*next;
	struct s_building	*prev;
}	t_building;

void		clean_and_exit(int exit_code);
void		ft_array_to_list(char **envp, t_list **envp_list);
void		ft_cd(char **args, t_list **env, t_minishell *minishell);
void		ft_echo(char **args);
char		**ft_refresh_env_array(t_list *list, char **env_array);
void		ft_export(char *envp, t_list **envp_list);
t_minishell	*ft_loading_minishell(char **envp);
char		*ft_getenv(char *needle, t_list *envp);
void		ft_update_prompt(t_minishell *minishell);
void		ft_print_env(t_list *env);
void		ft_export(char *envp, t_list **envp_list);
void		ft_export_args(char **args, t_list **env_list, t_minishell *mini);
void		ft_exit(char **arg);
void		ft_pwd(t_minishell *minishell);
void		ft_unset(char *envp, t_list **env_list);
void		mini_exec(char *command, char **args, t_minishell *minishell);
void		ft_parsing_and_exec(t_minishell *minishell);
char		*ft_search_in_path(char *cmd, t_list *envp);
void		ft_unset_args(char **args, t_list **env_list, t_minishell *mini);

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:34:17 by dagimeno          #+#    #+#             */
/*   Updated: 2025/03/10 19:47:30 by ide-dieg         ###   ########.fr       */
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

/**
 * @brief Estructura para almacenar los datos de redirecciones
 * 
 * @param file Nombre del archivo
 * @param type Tipo de redirección
 * 
 * @note type puede ser 0 (<), 1 (>), 2 (>>), 3 (<<)
 */
typedef struct s_redir
{
	char	*file;
	int		type;
}	t_redir;

typedef struct s_data_container
{
	void	*data;
	int		type;
}	t_data_container;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	t_redir	**infiles;
	t_redir	**outfiles;
}	t_cmd;

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
	int				io_fd[2];
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

void				clean_and_exit(int exit_code);
void				ft_array_to_list(char **envp, t_list **envp_list);
void				ft_cd(char **args, t_list **env, t_minishell *minishell);
void				ft_echo(char **args, t_minishell *mini);
void				ft_refresh_env_array(t_list *list, t_minishell *minishell);
void				ft_export(char *envp, t_list **envp_list);
void				ft_free_hash(t_env *hash);
void				ft_init_env(t_minishell *minishell);
void				ft_init_shlvl(t_minishell *minishell);
int					ft_isnumber(char *str);
t_minishell			*ft_loading_minishell(char **envp);
char				*ft_getenv(char *needle, t_list *envp);
void				ft_print_env(t_list *env, int fd);
void				ft_update_prompt(t_minishell *minishell);
void				ft_export(char *envp, t_list **envp_list);
void				ft_export_args(char **args, t_list **env_list,
						t_minishell *mini);
void				ft_exit(char **arg, t_minishell *minishell);
void				ft_pwd(t_minishell *minishell);
void				ft_unset(char *envp, t_list **env_list);
void				mini_exec(t_cmd *cmd, t_minishell *minishell);
void				ft_parsing_and_exec(t_minishell *minishell);
void				ft_remove_spaces(t_list **list);
char				*ft_search_in_path(char *cmd, t_minishell *minishell);
void				ft_unset_args(char **args, t_list **env_list,
						t_minishell *mini);
void				ft_open_files(t_cmd *cmd, t_minishell *minishell);
void				ft_close_files(t_minishell *minishell);

//tokenizer
int					ft_is_special_token(char *c);
void				ft_print_syntax_error_message(char *token);
int					ft_check_token_list(t_list **list, t_minishell *minishell);
void				ft_dollar_variable_converter(t_list *list,
						t_minishell *minishell);
void				ft_join_str_tokenizer(t_list *list);
void				ft_put_quotes(t_list *list);
int					ft_check_parenthesis(t_list *tks);
int					ft_verify_correct_order_onwards(t_list *tks);
void				ft_print_syntax_error_message(char *token);
int					ft_verify_correct_order_backwards(t_list *tks);
int					ft_check_instructions_after_parenthesis(t_list *tks);
int					ft_check_instructions_before_parenthesis(t_list *tks);
int					ft_check_for_redundant_parenthesis(t_list *tks);
void				ft_remove_quotes(t_list *list);
t_cmd				*ft_create_cmd(t_list *list);
t_data_container	*ft_new_data_container(void *data, int type);
void				ft_join_redirections(t_list *list);
int					ft_check_redirections(t_list *list);
t_list				*ft_create_cmds(t_list *list);
t_list				*ft_tokenizer(char *str, t_minishell *minishell);

#endif


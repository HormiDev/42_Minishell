/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:34:17 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/07 14:32:09 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# include "../42_Libft/libft.h"
# include "colors.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>

/**
 * @note type can be 0 (<), 1 (>), 2 (>>), 3 (<<)
 */
typedef struct s_redir
{
	char	*file;
	int		type;
}	t_redir;

/**
 * @note can be 0 (t_cmd), 1 (char *)
 */
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
	int		io_fd[2];
	t_list	**and_or_list;
}	t_cmd;

typedef struct s_env
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
	char			prompt[PATH_MAX + 1024];
	int				exit_code;
	t_list			*envp;
	char			**envp_array;
	int				**pipeline;
	t_list			*here_docs;
	int				history_fd;
}	t_minishell;

void				clean_and_exit(int exit_code);
void				ft_array_to_list(char **envp, t_list **envp_list);
void				ft_cd(t_cmd *cmd, t_minishell *minishell);
void				ft_echo(t_cmd *cmd, t_minishell *mini);
void				ft_execute(t_cmd *cmd, t_minishell *minishell);
void				ft_execute_builtin(t_cmd *cmd, t_minishell *minishell);
void				ft_refresh_env_array(t_list *list, t_minishell *minishell);
void				ft_free_hash(t_env *hash);
void				ft_init_env(t_minishell *minishell);
void				ft_init_shlvl(t_minishell *minishell);
int					ft_isnumber(char *str);
int					ft_isbuiltin(char *command);
t_minishell			*ft_loading_minishell(char **envp);
char				*ft_getenv(char *needle, t_list *envp);
void				ft_print_env(t_list *env, int fd, t_minishell *mini);
void				ft_update_prompt(t_minishell *minishell);
int					ft_export(char *envp, t_list **envp_list);
void				ft_export_args(t_cmd *cmd, t_minishell *mini);
void				ft_export_shlvl(t_env *env);
t_env				*ft_create_hash(char *envp, int i);
void				ft_free_hash(t_env *hash);
void				ft_exit(char **arg, t_minishell *minishell);
void				ft_pwd(t_cmd *cmd, t_minishell *minishell);
void				ft_unset(char *envp, t_list **env_list);
void				mini_exec(t_cmd *cmd, t_minishell *minishell);
void				ft_parsing_and_exec(t_minishell *minishell);
int					ft_pipe_counter(t_list *token_list);
void				ft_pipex_and_exec(t_minishell *mini, t_list *token_list);
void				ft_remove_spaces(t_list **list);
char				*ft_search_in_path(char *cmd, t_minishell *minishell);
void				ft_unset_args(char **args, t_list **env_list,
						t_minishell *mini);
int					ft_open_files(t_cmd *cmd);
void				ft_close_files(t_cmd *cmd);
int					ft_pipeline(t_minishell *minishell, t_cmd **cmds,
						int num_pipes);
void				ft_close_pipes(t_minishell *minishell);
void				ft_error_dprintf(t_minishell *minishell);
void				ft_create_heredocs(t_list *cmd_list,
						t_minishell *minishell);
void				ft_clear_here_docs(t_minishell *minishell);
void				ft_config_signals(void);
void				ft_config_signals_in_exec(void);
void				ft_init_history(t_minishell *minishell);
void				ft_save_heredocs(t_list *cmd_list, t_minishell *minishell);
void				ft_config_signals_in_heredoc(void);

//tokenizer
char				*ft_parse_var(char *str, int *i, t_minishell *mini);
int					ft_is_special_token(char *c);
void				ft_print_syntax_error_message(char *token);
int					ft_check_token_list(t_list **list, t_minishell *minishell);
void				ft_dollar_variable_converter(t_list *list,
						t_minishell *minishell);
int					ft_end_var(char *str);
void				ft_join_str_tokenizer(t_list *list);
void				ft_put_quotes(t_list *list);
int					ft_check_parenthesis(t_list *tks);
int					ft_verify_correct_order_onwards(t_list *tks);
void				ft_print_syntax_error_message(char *token);
int					ft_verify_correct_order_backwards(t_list *tks);
int					ft_check_instructions_after_parenthesis(t_list *tks);
int					ft_check_instructions_before_parenthesis(t_list *tks);
void				ft_remove_quotes(t_list *list);
t_cmd				*ft_create_cmd(t_list *list);
t_data_container	*ft_new_data_container(void *data, int type);
void				ft_join_redirections(t_list *list);
int					ft_check_redirections(t_list *list);
t_list				*ft_create_cmds(t_list *list);
char				*ft_search_variable(char *str, t_minishell *mini);
t_list				*ft_tokenizer(char *str, t_minishell *minishell);
void				ft_unquoted_dollar_variable_converter(t_list *list,
						t_minishell *mini);
//bonus
t_list				*ft_capsule_parentesis(t_list *tk_list);
int					ft_and_or_counter(t_list *token_list);
t_cmd				*fill_info(t_list **open,
						t_list **after_close, t_list **tk_list);
t_list				**ft_split_and_or(t_list *token_list);
int					ft_count_pipes(t_list *token_list);
int					ft_pipe_counter(t_list *token_list);
void				ft_manage_wildcards(t_list *list);
void				ft_process_wildcards(char *dir, char *str, t_list **list);
int					ft_number_of_wildcards(char *wildcard);
char				*ft_get_wildcard_search(char *str, char **wildcard,
						char *needle, int *numbers);
void				ft_free_array_content(void **array,
						void (*free_func)(void *));
void				ft_order_wildcards(t_list *list);
void				ft_and_or(t_minishell *mini, t_list **and_or_list);
void				ft_and_or_exec(t_cmd *cmd, t_minishell *minishell);

#endif

# 42_Minishell

funciones permitidas
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, kill, exit, getcwd, chdir, stat,
lstat, fstat, unlink, execve, dup, dup2, pipe,
opendir, readdir, closedir, strerror, perror,
isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,
tcgetattr, tgetent, tgetflag, tgetnum, tgetstr,
tgoto, tputs


proteccion de argc ? ok
proteccion de argv ? ok
proteccion de envp ko

crear ft_getenv() ok
gestionar carga s_minishell ok
gestionar carga s_minishell sin envp ko

implementar env ko
implementar unset ko
implementar export ok
implementar exit ko
implementar echo ko
implementar cd ko
implementar pwd ko

cambiar envp a formato de lista y modificar ft_getenv() ok

si tenemos tiempo y ganas gestionar que si no hay env cree uno con el el pwd, SHLVL y _

gestion de sintaxis erronea ej () (echo hola && (echo hola))
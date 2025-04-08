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

si tenemos tiempo y ganas gestionar que si no hay env cree uno con el el pwd, SHLVL y _ ok

gestion de sintaxis erronea ej () (echo hola && (echo hola)) ok

No hay que gestionar paréntesis más allá de para discernir prioridades de ejecución. ok

gestionar SHLVL (idea, que export guarde la variable iterandola +1 o a 0 si algun caracaracter es no es numerico y que env lo imprima -1  excepto si es 0) ok?

ft_join_str_tokenizer revisar para liberar ok

analizar posibles soluciones a esta mierda ok
	export HOLA=">hola"
	echo hola $HOLA		imprime "hola >hola"
	echo hola >$HOLA	crea fichero >hola y escribe dentro hola
posible solucion al jointear las redireccines con los strings no quitar las comillas del string y añadir unas extra
ejemplo:	 > "str"	">"str""

NOTA: la creacion de la estructura s_data_container para el ultimo paso de la tokenizacion (el listado de s_cmd) ha sido una brillante idea que de haberseme ocurrido antes se podia haber facilitado mucho y hacer mas eciciente toda la tokenizacion, pero en principio nos quedamos con la funcional y mejorable version actual

filename maximo admitido por bash 256

checkeo de redirecciones para la ejecucion  "bash: /home/ide-dieg: Es un directorio"  "bash: $HOLA: redireccionamiento ambiguo"

revisar exit codes emitidos por exit

buscar solucion a que hacer con el path en caso de que no exista el envairoment al cargar la minishell
	opcion facil (leer del fichero del path y guardarlo en en env)
	opcion dificil(leer del fichero del path y guardarlo en una variable de respaldo, que la ejecucion lea tambien de esa variable de respaldo y tanto unset como export modifiquen esa variable a parte del env)

Hacer que el heredoc imprima el valor de las variables de entorno
que las variables de entorno en el parseo sean spliteadas

El fd de el historial queda abierto al cerrar la minishell 
	Opcion1: asegurarse de que se cierre en todas las posibles salidas
	Opcion2: abrir y cerrar el fd cada vez que se tenga que usar
#include <stdio.h>
#include "../42_Libft/libft.h"

char	*ft_getenv(char *needle, char **envp);

int main(int argc, char **argv, char **envp)
{
	argc = 0;
	argv = NULL;
	printf("USER: %s\n", ft_getenv("USER", envp));
	printf("HOME: %s\n", ft_getenv("HOME", envp));
	printf("PATH: %s\n", ft_getenv("PATH", envp));
	printf("PWD: %s\n", ft_getenv("PWD", envp));
}
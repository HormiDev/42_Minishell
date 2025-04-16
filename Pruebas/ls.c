/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:11:34 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/14 13:02:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <dirent.h> // Necesario para opendir, readdir, closedir

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    int i;


    if (argc < 2)
    {
        // Abrir el directorio actual
        dir = opendir(".");
        if (dir == NULL) // Comparar con NULL, no con -1
        {
            perror("opendir");
            return 1;
        }

        // Leer las entradas del directorio
        while ((entry = readdir(dir)) != NULL)
        {
            printf("%s\n", entry->d_name); // Imprimir el nombre de cada entrada
        }

        // Cerrar el directorio
        if (closedir(dir) == -1)
        {
            perror("closedir");
            return 1;
        }
        return 0;
    }
    i = 1;
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        dir = opendir(argv[i]);
        if (dir == NULL) // Comparar con NULL, no con -1
        {
            perror("opendir");
            return 1;
        }

        // Leer las entradas del directorio
        while ((entry = readdir(dir)) != NULL)
        {
            printf("%s\n", entry->d_name); // Imprimir el nombre de cada entrada
        }

        // Cerrar el directorio
        if (closedir(dir) == -1)
        {
            perror("closedir");
            return 1;
        }
        i++;
    }
    return 0;
}

//opendir, readdir, closedir
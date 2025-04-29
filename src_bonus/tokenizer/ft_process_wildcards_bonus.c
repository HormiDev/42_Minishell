#include "../../include/minishell.h"

static int	ft_free_and_leave(char **wildcard_split,
	char *wildcard_copy, int ret)
{
	ft_free_array_content((void **)wildcard_split, ft_free_alloc);
	ft_free_alloc(wildcard_split);
	ft_free_alloc(wildcard_copy);
	return (ret);
}

/**
 * numbers[0] = iterator
 * numbers[1] = number of wildcards
 * numbers[2] = ends with wildcard
 */
static int	ft_needle_search_loop(char *wildcard, char *str,
	int number_of_wildcards, int ends_with_wildcard)
{
	char	**wildcard_split;
	char	*wildcard_search;
	char	*wildcard_copy;
	int		nums[3];

	wildcard_split = ft_split_ae(wildcard, 1);
	wildcard_copy = ft_strdup_ae(wildcard);
	nums[0] = -1;
	nums[1] = number_of_wildcards;
	nums[2] = ends_with_wildcard;
	while (wildcard_split[++nums[0]])
	{
		wildcard_search = ft_get_wildcard_search(str, &wildcard,
				wildcard_split[nums[0]], nums);
		if ((wildcard_search == NULL) || (nums[0] == 0
				&& *wildcard_copy != 1 && wildcard_search != &str[0])
			|| (wildcard_split[nums[0] + 1] == 0
				&& wildcard_copy[ft_strlen_p(wildcard_copy) - 1] != 1
				&& wildcard_search != &str[ft_strlen_p(str)
					- ft_strlen_p(wildcard_split[nums[0]])]))
			return (ft_free_and_leave(wildcard_split, wildcard_copy, 0));
		str = wildcard_search + ft_strlen_p(wildcard_split[nums[0]]);
	}
	return (ft_free_and_leave(wildcard_split, wildcard_copy, 1));
}

static int	ft_check_wildcard(char *str, char *wildcard)
{
	int		number_of_wildcards;
	int		ends_with_wildcard;

	number_of_wildcards = ft_number_of_wildcards(wildcard);
	if (wildcard[ft_strlen_p(wildcard) - 1] == 1)
		ends_with_wildcard = 1;
	else
		ends_with_wildcard = 0;
	return (ft_needle_search_loop(wildcard, str,
			number_of_wildcards, ends_with_wildcard));
}

void	ft_process_wildcards(char *dir, char *str, t_list **list)
{
	DIR				*directory;
	struct dirent	*entry;
	int				hidden_file;

	directory = opendir(dir);
	if (str == NULL || *str == '\0' || list == NULL || directory == NULL)
		return ;
	hidden_file = 0;
	if (str[0] == '.')
		hidden_file = 1;
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (hidden_file == 0 && (entry->d_name[0] == '.'
				|| ft_strncmp_p(entry->d_name, ".", 2) == 0
				|| ft_strncmp_p(entry->d_name, "..", 3) == 0))
			;
		else if (ft_check_wildcard(entry->d_name, str))
			ft_lstadd_back(list, ft_lstnew_ae(ft_strdup_ae(entry->d_name)));
		entry = readdir(directory);
	}
	if (closedir(directory) == -1)
		perror("closedir");
}

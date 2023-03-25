/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:07:36 by araymond          #+#    #+#             */
/*   Updated: 2023/03/24 14:51:55 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* Checks if files are valid or can be created, then checks if the commands are
valid commands. Frees pipex and exits on failure or proceeds from calling if
successful. */
void	error_check(char **argv, t_pipex *s_pipex)
{
	if (ft_strncmp(argv[1], argv[4], ft_strlen(argv[1])) == 0)
		error_message(s_pipex);
	s_pipex->cmd1 = ft_split(argv[2], ' ');
	s_pipex->cmd2 = ft_split(argv[3], ' ');
	if (!s_pipex->cmd1 || !s_pipex->cmd2)
		error_message(s_pipex);
	s_pipex->infile = argv[1];
	s_pipex->outfile = argv[4];
}

// Gets the PATH env variable.
char	*envp_search(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		path = ft_strnstr(envp[i], "PATH", ft_strlen(envp[i] + 1));
		if (path)
			break ;
		i++;
	}
	return (ft_strchr(path, '/'));
}

// Handles the big stuff.
void	parse_args(char **argv, char **envp, t_pipex *s_pipex)
{
	char	*path;
	int		i;

	i = 0;
	path = envp_search(envp);
	if (!path)
		error_message(s_pipex);
	s_pipex->paths = ft_split(path, ':');
	if (!s_pipex->paths)
		error_message(s_pipex);
	error_check(argv, s_pipex);
	pipe_process(s_pipex);
}

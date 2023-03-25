/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:35:59 by araymond          #+#    #+#             */
/*   Updated: 2023/03/25 09:34:24 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_message(t_pipex *s_pipex)
{
	clear_pipex(s_pipex);
	perror("Error");
	exit(EXIT_FAILURE);
}

//Joins the path and the command together with a '/'.
char	*join_command(char *path, char *cmd)
{
	int		i;
	int		j;
	char	*new;

	if (!path || !cmd)
		return (NULL);
	i = 0;
	j = 0;
	new = ft_calloc(sizeof(new), (ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!new)
		return (NULL);
	while (path[i])
	{
		new[i] = path[i];
		i++;
	}
	new[i++] = '/';
	while (cmd[j])
		new[i++] = cmd[j++];
	return (new);
}

t_pipex	*initiate_pipex(void)
{
	t_pipex	*s_pipex;

	s_pipex = malloc(sizeof(t_pipex));
	if (!s_pipex)
		return (NULL);
	s_pipex->paths = NULL;
	s_pipex->cmd1 = NULL;
	s_pipex->cmd2 = NULL;
	return (s_pipex);
}

void	clear_pipex(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	if (s_pipex)
	{
		if (s_pipex->paths)
			free_strstr(s_pipex->paths);
		if (s_pipex->cmd1)
			free_strstr(s_pipex->cmd1);
		if (s_pipex->cmd2)
			free_strstr(s_pipex->cmd2);
		free(s_pipex);
	}
}

void	close_fds(int *tab)
{
	close(tab[0]);
	close(tab[1]);
}

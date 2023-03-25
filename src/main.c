/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:07:37 by araymond          #+#    #+#             */
/*   Updated: 2023/03/24 16:17:22 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_strstr(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
		i++;
	while (i >= 0)
		free(strstr[i--]);
	free(strstr);
}

void	open_files(t_pipex *s_pipex)
{
	s_pipex->fds[0] = open(s_pipex->infile, O_RDONLY);
	if (s_pipex->fds[0] == -1)
		error_message(s_pipex);
	s_pipex->fds[1] = open(s_pipex->outfile, \
		O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (s_pipex->fds[1] == -1)
	{
		close(s_pipex->fds[0]);
		error_message(s_pipex);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*s_pipex;

	if (argc == 5)
	{
		s_pipex = initiate_pipex();
		if (!s_pipex)
			error_message(s_pipex);
		parse_args(argv, envp, s_pipex);
		clear_pipex(s_pipex);
		exit(EXIT_SUCCESS);
	}
	else
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

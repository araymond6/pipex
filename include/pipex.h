/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:09:13 by araymond          #+#    #+#             */
/*   Updated: 2023/03/24 15:27:09 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

# define SUCCESS 1
# define ERROR 0

typedef struct s_pipex
{
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	int		fds[2];
	int		pipe[2];
	pid_t	child[2];
	char	*infile;
	char	*outfile;
}	t_pipex;

// Parsing
void	parse_args(char **argv, char **envp, t_pipex *s_pipex);

// Meat N' Bones
void	pipe_process(t_pipex *s_pipex);

// Utils
void	error_message(t_pipex *s_pipex);
t_pipex	*initiate_pipex(void);
void	clear_pipex(t_pipex *s_pipex);
char	*join_command(char *path, char *cmd);
void	close_fds(int *tab);
void	open_files(t_pipex *s_pipex);
void	free_strstr(char **strstr);

#endif
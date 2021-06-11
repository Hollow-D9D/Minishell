/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_ximichit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:50:13 by tharutyu          #+#    #+#             */
/*   Updated: 2021/06/09 15:47:17 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char *builtin_str[] = 
{
	"cd",
	"exit",
	"pwd",
	"echo",
	"env",
	"export",
	"unset",
	"error"
};

int (*builtin_func[]) (t_checks *, int) = {
	&to_cd,
	&to_exit,
	&to_pwd,
	&to_echo,
	&to_env,
	&to_export,
	&to_unset,
	&to_error
};

int builtins_count() 
{
	return sizeof(builtin_str) / sizeof(char *);
}

int		ft_export_char(int c)
{
	if ((c >= '0' && c <= '9') || (c > 95 && c < 123) || (c > 64 && c < 91))
		return (1);
	return (0);
}

int ft_var_len(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i + 1);
}

int ft_word_len(char *line) //valid function  menak imaci vor quoteri tvern ela hashvum
{
	int i;
	int q; //quote
	int dq; //double quote

	i = 0;
	q = 0;
	dq = 0;
	while(line[i])  //zut nayuma vor 1 bar vercni, minchev seperator space kam el \0
	{
		if(!dq && line[i] == '\'')  //quote-handled
			q = !q;
		if(!q && line[i] == '\"')
			dq = !dq;
		if(q || dq || (!ft_check_char(SPACES, line[i]) //nayuma minchev seperator kam space, ete quoteri meja ignora anum dranq u sharunakuma hashvel
			&& !ft_check_char(SEPERATORS, line[i])))
		i++;
		else 
			break;
	}
	return (i);
}

void	free_args(t_checks *check)
{
	int i;
	int j;

	i = 0;
	while(i < check->argc)
	{
		j = 0;
		while(check->coms[i].pr[j])
		{
			free(check->coms[i].pr[j]);
			j++;
		}
		i++;
	}
	free(check->coms);
}

int check_input_redir(t_checks *check, int j)
{
	int i;
	pid_t pid;
	int status;

	i = j + 1;
	while(i < check->argc && !check->coms[i].is_process)
	{
		pid = fork();
		if (pid == 0)
		{
			if(check->coms[i].lsep == 2)
			{
				dup2(check->coms[i].file_d, STDIN_FILENO);
				dup2(check->coms[j].fd[1], STDOUT_FILENO);
				if (execve(check->coms[j].pr[0], check->coms[j].pr, check->env) == -1) 
    			{
    				my_errno(errno, check);
       			perror("exec failed");
       			exit(EXIT_FAILURE);
    			}
    			close (STDIN_FILENO);
    			close (STDOUT_FILENO);
    			exit(EXIT_FAILURE);
			}
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
			perror("negative pid");
		else 
  		{
    		do
    		{
      			waitpid(pid, &status, WUNTRACED); // означает  возвращать  управление также для остановленных дочерних процессов, о чьем
              									//статусе еще не было сообщено.
   			}
    		while (!WIFEXITED(status) && !WIFSIGNALED(status)); // WIFEXITED(status) не равно нулю, если дочерний процесс нормально завершился.	// 
  		}
  		i++;
	}
	return (1);
}

int check_output_redir(t_checks *check, int j, int flag)
{
	int i;
	int fl;
	pid_t pid;
	int status;

	fl = 0;
	i = j + 1;
	while(i < check->argc && !check->coms[i].is_process)
	{
		pid = fork();
		if (pid == 0) 
  	{
			if(check->coms[i].lsep > 2)
			{
				fl = 1;
				dup2(check->coms[i].file_d, STDOUT_FILENO);
				if(flag)
				dup2(check->coms[j].fd[0], STDIN_FILENO);
				if (execve(check->coms[j].pr[0], check->coms[j].pr, check->env) == -1) 
    			{
    				my_errno(errno, check);
       				perror("exec failed");
       				exit(EXIT_FAILURE);
    			}
    			close (STDIN_FILENO);
    			close (STDOUT_FILENO);
    			exit(EXIT_FAILURE);
			}
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
			perror("negative pid");
		else 
  	{
				do
 				{
      			waitpid(pid, &status, WUNTRACED); // означает  возвращать  управление также для остановленных дочерних процессов, о чьем
              									//статусе еще не было сообщено.
   			}
    		while (!WIFEXITED(status) && !WIFSIGNALED(status)); // WIFEXITED(status) не равно нулю, если дочерний процесс нормально завершился.	// 
		}
  		i++;
	}
	return (fl);
}

int execute(t_checks *check, int j) //  ./ - ov u aranc dra execute normala anum, tencel petqa mez?
{
	pid_t pid;
	int status;
	int fl;
	int fl1;

	fl = 0;
	pipe(check->coms[j].fd);
	if (!check->coms[j].pr[1])
  		fl = check_input_redir(check, j);
  	fl1 = check_output_redir(check, j, fl);
  	if(!fl1)
  	{
  		pid = fork();
  		if (pid == 0) 
  		{
  			if(fl)
  				dup2(check->coms[j].fd[0], STDIN_FILENO);
 				if (execve(check->coms[j].pr[0], check->coms[j].pr, check->env) == -1) 
				{
					perror("exec failed");
					exit(EXIT_FAILURE);
				}
				if(fl)
					close(STDIN_FILENO);
				exit(EXIT_FAILURE);
			}
			else if (pid < 0)
				perror("negative pid");
			else 
  		{
    		do
    		{
      		waitpid(pid, &status, WUNTRACED); // означает  возвращать  управление также для остановленных дочерних процессов, о чьем
  	   	   									 									//статусе еще не было сообщено.
   			}
    		while (!WIFEXITED(status) && !WIFSIGNALED(status)); // WIFEXITED(status) не равно нулю, если дочерний процесс нормально завершился.	// 
  		}
  	}
  // 	if (check->coms[j].pr[1])
  // 	{
  				// if (execve(check->coms[j].pr[0], check->coms[j].pr, check->env) == -1) 
    		// 	{
    		// 		my_errno(errno, check);
      //  				perror("exec failed");
    		// 	}
    		// 	exit(EXIT_SUCCESS);
  //   		}
  //   		fl = 1;
  //   		if (check->coms[i + 1].lsep == 2)
  //   			dup2(check->coms[i + 1].file_d, STDIN_FILENO);
 	// 		else if (check->coms[i + 1].lsep > 2)
 	// 			dup2(check->coms[i + 1].file_d, STDOUT_FILENO);
  //   		if (execve(check->coms[j].pr[0], check->coms[j].pr, check->env) == -1) 
  //   		{
  //   			my_errno(errno, check);
  //      			perror("exec failed");
  //   		}
  //   	if (!fl && execve(check->coms[j].pr[0], check->coms[j].pr, check->env) == -1) 
  //   	{
  //   		my_errno(errno, check);
  //      		perror("exec failed");
  //   	}
  //   	close(STDIN_FILENO);
  //   	exit(EXIT_FAILURE);
  // 		}
  // 	else if (pid < 0) 
  // 	{
  //  		perror("negative pid");
  // 	} 
  // 	else 
  // 	{
  //   	do 
  //   	{
  //     		waitpid(pid, &status, WUNTRACED); // означает  возвращать  управление также для остановленных дочерних процессов, о чьем
  //             									//статусе еще не было сообщено.
  //  		}
  //   	while (!WIFEXITED(status) && !WIFSIGNALED(status)); // WIFEXITED(status) не равно нулю, если дочерний процесс нормально завершился.	// 
  // 		if (check->coms[j].pr[1])
  // 			break;
  // 	}
  // 	i++; 													//   WIFSIGNALED(status)  возвращает    истинное   значение,   если   дочерний   процесс   завершился   из-за
 	// }										//неперехваченного сигнала.
  return (0);
}

int builtin(t_checks *check)
{
	int i;
	int j;

	j = 0;
	while(j < check->argc)
	{
		if(check->coms[j].is_process)
		{
			i = 0;
			while (i < builtins_count())
			{
				if (check->coms[j].is_process)
					if (ft_strcmp(check->coms[j].pr[0], builtin_str[i]) == 0)
					{
						check->rtn = (*builtin_func[i])(check, j);
						if (j + 1 == check->argc)
							return (0);
						break ;
					}
				i++;
			}
			if (i == builtins_count())
				execute(check, j);
		}
		j++;
	}
	return (0);
}

void	close_files(t_checks *check)
{
	int i;

	i = 0;
	while (i < check->argc)
	{
		if(!check->coms[i].is_process)
			close(check->coms[i].file_d);
		i++;
	}
}

int		main(int argc, char **argv, char **envp)
{
	char *line;
	int status;
	// int pid;
	// int	cpid;
	(void)argv;
	(void)argc;
	t_checks check;
	// if (feof(stdin))  // cntrl + D , bayc chi ashkhatum boozeh
	// {
	// 	exit(0);
	// }
	init_envp (envp, &check);
	signal(SIGINT, my_int); // ctrl + C //
	signal(SIGQUIT, my_quit); // ctrl + \ //
	check.rtn = 5;
	status = 1;
	while (status)
	{
		write(1, "Shell> ", 7); //command prompt
		zero_checks(&check); //zroyacnuma
		get_next_line(0, &line); //input 
		parse_args(&check, line); // parse lines
		treat_files(&check);
		builtin(&check);
		//status = exec_args(&check);
		close_files(&check);
		free_args(&check);
	}
	return (0);
}
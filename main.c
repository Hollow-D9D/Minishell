/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:50:13 by tharutyu          #+#    #+#             */
/*   Updated: 2021/06/14 03:42:33 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lyuboy no such filei jamanak 127
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
		free(check->coms[i].pr);
		i++;
	}
	free(check->coms);
}


char *ft_strjoini_gev(char const *s1, char const *s2)
{
    char	*dest;
	int		i;
	int     one;
	int     two;
	

	if (!(s1 && s2))
	    return(NULL);
	else
	    one = ft_strlen(s1);
    	two = ft_strlen(s2);
	    dest = (char*)malloc(sizeof(char) * (one + two + 1));
	    if (dest == NULL)
		    return (NULL);
  	i = -1 ;
	while (s1[++i])
        dest[i] = s1[i];
    	i = -1;
	while (s2[++i])
    {
        dest[one] = s2[i];
        one++;
    }
	dest[one] = '\0';
	return(dest);
}


int execute(t_checks *check, int j) //  ./ - ov u aranc dra execute normala anum, tencel petqa mez?
{
	
	pid_t pid;
	// int status;
	int i;
	int fl;
	char **path;
	int p;
	char *pstr;
	char *tmp;

	path = NULL;
	p = 0;
	fl = 0;
	i = j + 1;
	path = find_path(check);
  	pid = fork();
	if (pid == 0) 
  	{
  		while(i < check->argc && !check->coms[i].is_process)
  		{
    		if (check->coms[i].lsep == 2)
    		{
    			if(!check->coms[j].pr[1])
   					dup2(check->coms[i].file_d, STDIN_FILENO);
    		}
   			else if (check->coms[i].lsep > 2)
   			{
   				fl = 1;
 				dup2(check->coms[i].file_d, STDOUT_FILENO);
   			}
    		i++;
    	}
    	if (check->coms[j].pr[0][0] == '/')
    	{
    		execve(check->coms[j].pr[0], check->coms[j].pr, check->env);
    	}
    	else
	      	while (path[p])
	    	{
	    		tmp = ft_strjoini_gev(path[p], "/");
				pstr = ft_strjoini_gev(tmp, check->coms[j].pr[0]);
				//printf("STRLEN==%lu\n", ft_strlen(pstr));
				if ((execve(pstr, check->coms[j].pr, check->env)) != -1)
	  			{
	  				free(tmp);
	  				free(pstr);
	  				break ;
	  			}
	  			free(tmp);
	  			free(pstr);
	  			p++;
	  		}
  		printf("minishell: command not found: %s\n", check->coms[j].pr[0]);
  		g_err = 127;
    	exit(EXIT_FAILURE);
    }
  	else if (pid < 0) 
  	{
   		perror("negative pid");
  	} 
  	else 
  	{
  		// close(STDIN_FILENO);
      		wait(0); // означает  возвращать  управление также для остановленных дочерних процессов, о чьем								//статусе еще не было сообщено.
      }
  return (0);
}

int check_pipe(t_checks *check, int j)
{
	int i;

	i = j;
	if(check->coms[j].rsep > 1)
	{
		i++;
		while(!check->coms[i].is_process)
			i++;
	}
	if(check->coms[j].rsep == 1 || (i != j && check->coms[i].lsep == 1))
	{
		pipe(check->coms[j].fd);
		check->pid = fork();
		if(check->pid < 0)
			printf("fuck this shit i'm out\n");
		if (check->pid == 0)
		{
			// if(j && check->coms[j - 1].rsep == 1)
			// 	check->coms[j].fd[1] = dup(check->coms[j - 1].fd[1]);
			// else
			dup2(check->coms[j].fd[1], STDOUT_FILENO);
			// close(check->coms[j].fd[1]);
			close(check->coms[j].fd[0]);
			return (2);
		}
		else
		{
			// printf("valod on service in check_pipe\n");
			// printf("valod on service in check_pipe\n");
			// if(j && check->coms[j - 1].rsep == 1)
			// 	check->coms[j].fd[0] = dup(check->coms[j - 1].fd[0]);
			// else
			dup2(check->coms[j].fd[0], STDIN_FILENO);
			close(check->coms[j].fd[1]);
			// close(check->coms[j].fd[0]);
			return (1);
		}
	}
	return (0);
}

int builtin(t_checks *check)
{
	int i;
	int j;
	int pipe;
	// int status;

	j = 0;
	while(j < check->argc)
	{
		if(check->coms[j].is_process)
		{
			pipe = check_pipe(check, j);
			// printf("pid pipe%d j = %d\n", pipe, j);
			if (pipe == 1)
			{
				// printf("valod on service\n");
				check->is_child = 0;
				while(wait(0) != -1 || errno != ECHILD)
					;
				// wait((check->pid + 1));
    		j++;
				continue ;
			}
			else if (pipe == 2)
			{
				check->is_child = 1;
			}
			// printf("%d\n", check->is_child);
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
			if (check->is_child)
				exit(EXIT_FAILURE);
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
	(void)argv;
	(void)argc;
	t_checks check;
	int n;

	check.fd[0] = dup(STDIN_FILENO);
	check.fd[1] = dup(STDOUT_FILENO);
	init_envp (envp, &check);
	signal(SIGINT, my_int); // ctrl + C //
	signal(SIGQUIT, my_quit); // ctrl + \ //
	status = 1;
	while (status)
	{
		write(1, "Shell> ", 7); //command prompt
		zero_checks(&check); //zroyacnuma
		n = get_next_line(0, &line); //input 
		if (!n)
		{	
			g_err = 0;
			write(1, "exit\n", 5);
			exit(0);
		}
		parse_args(&check, line); // parse lines
		treat_files(&check);
		builtin(&check);
		//status = exec_args(&check);
		close_files(&check);
		free_args(&check);
		dup2(check.fd[0], STDIN_FILENO);
		dup2(check.fd[1], STDOUT_FILENO);
	}
	return (0);
}

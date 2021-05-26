/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:50:13 by tharutyu          #+#    #+#             */
/*   Updated: 2021/05/26 15:12:31 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//GEV ERROR HANDLING PETQA ARVI HENC HIMA ES PARSING EM ANUM 

// bin path == /Users/gamirjan/.brew/bin/
// bin path == /Users/gamirjan/.brew/bin/
// bin path == /usr/local/bin/
// bin path == /usr/bin/
// bin path == /bin/
// bin path == /usr/sbin/
// bin path == /sbin/
// bin path == /usr/local/munki/
// bin path == /Users/gamirjan/.rvm/bin/

// cikl petqa anenq bolor patherov man ga xosqi mkdir@ ete gtni ashxati ete che false, minchev chisht path@ gtni
#include "minishell.h"

char *builtin_str[] = 
{
	"cd",
	"exit",
	"pwd",
	"echo",
	"env",
	"export",
	"unset"
};

int (*builtin_func[]) (t_checks *) = {
	&to_cd,
	&to_exit,
	&to_pwd,
	&to_echo,
	&to_env,
	&to_export,
	to_unset
};


int builtins_count() 
{
	return sizeof(builtin_str) / sizeof(char *);
}

int to_unset(t_checks *check) // de unseti hmar hla vor petqa exportn ashkhatel
{
	if (check->coms[0].pr[1] == NULL)  // ete mi argumenta petqa es tpi
	{
		write(1, "unset: not enough arguments\n", 28);
		return(0);
	}
	else
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

char **ft_add_env_var(char *str, char **env)
{
	t_checks 	temp;
	char 		**newenv;
	int 		i; 
	int 		j;
	
	i = 0;
	j = 0;
	while(env[i])
		i++;
	i++;
	init_envp(env, &temp);
	while(env[j])
	{
		free(env[j]);
		++j;
	}
	free(env);
	newenv = malloc((i + 1) * sizeof(char *));
	j = 0;
	while(temp.env[j])
	{
		newenv[j] = ft_strdup(temp.env[j]);
		++j;
	}
	newenv[j++] = ft_strdup(str);
	newenv[j] = NULL;
	j = 0;
	while(temp.env[j])
	{
		free(temp.env[j]);
		++j;
	}
	free(temp.env);
	// free_args(&temp);
	return newenv;
}

int to_export(t_checks *check)
{
	int i;
	int j;

	i = 1;
	if (check->coms[0].pr[1] == NULL) // ete mi argumenta petqa env@ tpi
		return (to_env(check));
	else 
		while (check->coms[0].pr[i])
		{
			j = 0;
			while (check->env[j])
			{
				if (!ft_strncmp(check->env[j], check->coms[0].pr[i], ft_var_len(check->env[j], '=')))
				{
					printf("%d\n", ft_var_len(check->env[j], '='));
					free(check->env[j]);
					check->env[j] = ft_strdup(check->coms[0].pr[i]);
					break ;
				}
				j++;
			}
			if (check->env[j])
			{
				i++;
				continue ;
			}
			check->env = ft_add_env_var(check->coms[0].pr[i], check->env);
			i++;
		}
	return (0);
}

int to_env(t_checks *check) // mer envna ughaki malloci pah@ garlakhaca
{
	int i;
	i = 0;

	while (check->env[i])
	{
		write(1, check->env[i], ft_strlen(check->env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
int to_echo(t_checks *check)
{
	int i;
	int nflag;

	nflag = 0;
	i = 1;
	if (ft_strcmp(check->coms[0].pr[1], "-n") == 0)
	{
		i++;
		nflag = 1;
	}
	while(check->coms[0].pr[i])
	{
		write(1, check->coms[0].pr[i], ft_strlen(check->coms[0].pr[i]));
		write(1, " ", 1);
		i++;
	}
	if (!nflag)
		write(1, "\n", 1);
	return (0);
}

int to_pwd(t_checks *check)
{
	char buffer[1024];
	getcwd(buffer, 1024);
	printf("%s\n", buffer);
	return (0);
}

int to_exit(t_checks *check)
{
	exit(0);
}

int to_cd(t_checks *check)
{
	if (check->coms[0].pr[1] == NULL) 
	{
		fprintf(stderr, "sh: expected argument to \"cd\"\n");
  	} 
	else 
	{
		if (chdir(check->coms[0].pr[1]) != 0) 
    	{
      		perror("lsh");
   		}
  	}
  	return (1);
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
			// printf("valod: %d\n", check->argc);
			free(check->coms[i].pr[j]);
			j++;
		}
		
		// free(check->coms[i].pr);
		i++;
	}
	free(check->coms);
}

int		arg_count_base(char *line, t_checks *check, char *base)  //complete I think, stuguma qani process es pass arel
{
	int i;
	int n;

	n = 1;
	i = 0;
	while (line[i])
	{
		if (!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if (!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if (!check->dquote && !check->quote)
		{
			if (ft_check_char(base, line[i]))
				n++;
		}
		i++;
	}
	return (n);
}

int		word_count_base(char *line, t_checks *check, char *base, int num)  //complete I think, stuguma qani process es pass arel
{
	int i;
	int n;

	n = 1;
	i = 0;
	while (i < num - 1)
	{
		if (!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if (!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if (!check->dquote && !check->quote)
		{
			if (ft_check_char(base, line[i]))
			{
				n++;
				while (line[i] && ft_check_char(base, line[i]))
					i++;
				continue ;
			}
		}
		i++;
	}
	return (n);
}

// void		give_seperator(t_checks *check)
// {

// }

void ft_trim_quotes(char *str) //done test ara vorovhetev trucik em nayel, norme chi ancnum mek el
{
	int i;
	int q;
	int dq;
	int j;
	char *buff;

	j = 0;
	i = 0;
	q = 0;
	dq = 0;
	buff = malloc(sizeof(char) * ft_strlen(str));
	while(str[i])
	{
		if(!dq && str[i] == '\'')
		{
			q = !q;
			i++;
			continue;
		}
		if(!q && str[i] == '\"')
		{
			dq = !dq;
			i++;
			continue;
		}
		buff[j] = str[i];
		i++;
		j++;
	}
	free(str);
	str = ft_strdup(buff);
	free(buff);
}

void		get_process(char *line, int n, t_checks *check, int j)
{
	int i;
	char *tmp;
	int num;
	int z;

	i = check->index;
	while (ft_check_char(SPACES, line[i]))
		i++;
	num = word_count_base(line + i, check, SPACES, n);
	check->coms[j].pr = malloc(sizeof(char *) * (num + 1));
	check->coms[j].pr[num] = NULL;
	z = 0;
	while(z < num)
	{
		while (ft_check_char(SPACES, line[i]))
			i++;
		check->coms[j].pr[z] = ft_substr(line, i, ft_word_len(line + i));
		ft_trim_quotes(check->coms[j].pr[z]);
		i += ft_word_len(line + i);
		z++;
	}
}

void	parse_args(t_checks *check, char *line)
{
	int i;
	int j;

	i = -1;
	j = 0;
	check->argc = arg_count_base(line, check, SEPERATORS); //malloci hamar petqa vor imanas qani processi tegh es bacum
	check->coms = ft_calloc(sizeof(t_process), check->argc);
	while (line[++i])  //anavarta der mtacum em sra vra
	{
		if(!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if(!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if(!check->dquote && !check->quote && ft_check_char(SEPERATORS, line[i])) // seperatori conditionna test arac chi
		{
			get_process(line, i, check, j); //veradarcnuma tiv vor i-n iran chkorcni
			j++; //processneri indexna
			while(ft_check_char(SEPERATORS, line[i]))
				i++;
			check->index = i;
			continue ;
		}
	}
	//write(1, envp[0], ft_strlen(envp[0]));
	get_process(line, i, check, j);
}

void	zero_checks(t_checks *check)
{
	check->index = 0;
	check->argc = 0;
	check->is_process = 0;
	check->quote = 0;
	check->dquote = 0;
	check->pipe = 0;
	check->redir = 0;
	check->great = 0;
	check->less = 0;
	check->scolon = 0;
}

int execute(t_checks *check)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) 
  	{
    	if (execve(check->coms[0].pr[0], check->coms[0].pr, check->env) == -1) 
    	{
      		perror("error ara");
    	}
    	exit(EXIT_FAILURE);
  	} 
  	else if (pid < 0) 
  	{
   		perror("error ara");
  	} 
  	else 
  	{
    	do 
    	{
      		waitpid(pid, &status, WUNTRACED);
   		}
    	while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return (1);
}

int builtin(t_checks *check)
{
	int i;
	i = 0;

	if (check->coms->pr == NULL)
	{
		return (1);
	}
	while (i < builtins_count())
	{
		if (ft_strcmp(check->coms[0].pr[0], builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(check);
		}
		i++;
	}
	return (execute(check));
}

void 	init_envp(char **envp, t_checks *check)
{
	int e;
	e = 0;

	while (envp[e])
		e++;
	check->env = malloc(sizeof(char *) * (e + 1)); /// es petqa normal malloc arvi asenq
	check->env[e] = NULL;
	e = 0;
	while (envp[e])
	{
		check->env[e] = ft_strdup(envp[e]);
		e++;
	}
}

int		main(int argc, char **argv, char **envp)
{
	char *line;
	int status;
	int pid;
	int	cpid;
	t_checks check;

	init_envp (envp, &check);
	signal(SIGINT, my_int); // ctrl + C //
	signal(SIGQUIT, my_quit); // ctrl + \ //
	status = 1;
	while (status)
	{
		write(1, "Shell> ", 7); //command prompt
		zero_checks(&check); //zroyacnuma
		get_next_line(0, &line); //input 
		parse_args(&check, line); // parse lines 
		builtin(&check);
		//status = exec_args(&check);
		free_args(&check);
	}
	return (0);
}

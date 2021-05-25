/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:50:13 by tharutyu          #+#    #+#             */
/*   Updated: 2021/05/25 13:22:32 by tharutyu         ###   ########.fr       */
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

// path == /usr/bin/mkdir
// param0 == mkdir
//   param1 hayaastan
//   param2 (null)
#include "minishell.h"

char *builtin_str[] = 
{
	"cd",
	"exit",
	"pwd",
	"echo",
	"env"
};

int (*builtin_func[]) (t_checks *) = {
	&to_cd,
	&to_exit,
	&to_pwd,
	&to_echo,
	&to_env
};


int builtins_count() 
{
	return sizeof(builtin_str) / sizeof(char *);
}

int to_env(t_checks *check)
{
	// int i;
	// i = 0;

	// while (check->env[i])
	// {
	// 	write(1, check->env[i], ft_strlen(check->env[i]));
	// 	write(1, "\n", 1);
	// 	i++;
	// }
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

void	parse_args(t_checks *check, char *line, char **envp)
{
	int i;
	int j;
	int e;

	i = -1;
	j = 0;
	e = 0;
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
	check->env = malloc(10000); /// es petqa normal malloc arvi asenq
	while (envp[e])
	{
		check->env[e] = envp[e];
		// write(1, check->env[e], ft_strlen(check->env[e]));
		// write(1, "\n", 1);
		e++;
	}
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
    	if (execve(check->coms->pr[0], check->coms->pr, check->env) == -1) 
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

int		main(int argc, char **argv, char **envp)
{
	char *line;
	int status;
	int pid;
	int	cpid;
	t_checks check;

	signal(SIGINT, my_int); // ctrl + C //
	signal(SIGQUIT, my_quit); // ctrl + \ //
	status = 1;
	while (status)
	{
		write(1, "Shell> ", 7); //command prompt
		zero_checks(&check); //zroyacnuma
		get_next_line(0, &line); //input 
		parse_args(&check, line, envp); // parse lines 
		builtin(&check);
		//status = exec_args(&check);
		free_args(&check);
	}
	return (0);
}

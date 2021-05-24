/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:50:13 by tharutyu          #+#    #+#             */
/*   Updated: 2021/05/22 23:05:11 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//GEV ERROR HANDLING PETQA ARVI HENC HIMA ES PARSING EM ANUM 

// bin path == /Users/gamirjan/Desktop/ls/lolp/builtins/bin/
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

int to_cd(char **args);
int to_exit(char **args);

char *builtin_str[] = 
{
	"cd",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&to_cd,
	&to_exit
};

typedef	struct	s_process
{
	char	*pr; //process name
	char	*args; //arguments
	int		fd[2]; //input output for pipe
	char	lsep; //left seperator
	char	rsep; //right seperator 
	int		rtnv; //process return value
}				t_process;

typedef struct	s_checks
{
	int			argc;
	int			is_process; //stuguma arajin barna te che
	int			quote; //stuguma ' baca te che
	int			dquote; //stuguma " baca te che
	int			pipe; //stuguma | ka te che ??
	int			scolon; //stuguma ; ka te che ??
	int			great; //stuguma > ka te che ??
	int			less; //stuguma < ka te che ??
	int			redir; //stuguma >> ka te che??
	int			index; //petqa vor haskananq parsingi vaxt ura hasel
	t_process	*coms; //mer commandnerna 
	char		**env; //mer popoxakannerna $
}				t_checks;

int builtins_count() 
{
	return sizeof(builtin_str) / sizeof(char *);
}

int to_exit(char **args)
{
  return 0;
}

int to_cd(char **args)
{
  if (args[1] == NULL) 
  {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } 
  else 
  {
    if (chdir(args[1]) != 0) 
    {
      perror("lsh");
    }
  }
  return 1;
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

	i = 0;
	while(i < check->argc)
	{
		if(check->coms[i].pr)
			free(check->coms[i].pr);
		if(check->coms[i].args)
			free(check->coms[i].args);
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
	while(line[i])
	{
		if(!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if(!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if(!check->dquote && !check->quote)
		{
			if(ft_check_char(base, line[i]))
				n++;
		}
		i++;
	}
	return (n);
}

// void		give_seperator(t_checks *check)
// {

// }

void		get_process(char *line, int n, t_checks *check, int j)
{
	int i;
	char *tmp;

	i = check->index;
	while (ft_check_char(SPACES, line[i]))
 		i++;
	check->coms[j].pr = ft_substr(line + i, 0, ft_word_len(line + i));
	// i += ft_word_len(line + i);
	// while (i < n)
	// {
	// 	while (ft_check_char(SPACES, line[i]))
	// 		i++;
	// 	tmp = ft_substr(line + i, 0, ft_word_len(line + i));
	// 	tmp = ft_strjoin(tmp, " ");
	// 	check->coms[j].args = ft_strjoin(check->coms[j].args, tmp);
	// 	free(tmp);
	// 	i += ft_word_len(line + i);
	// }
	check->coms[j].args = ft_substr(line + i, 0, n);
	// give_seperator(check,);                    //parse pipes redirections and so on for processes arden sksuma input output irar kapel. fork anel ev ayln
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
		// printf("parse_args\n");
		if(!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if(!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if(!check->dquote && !check->quote && ft_check_char(SEPERATORS, line[i])) // seperatori conditionna test arac chi
		{
			//printf("mta es anter tegh@\n");
			get_process(line, i, check, j); //veradarcnuma tiv vor i-n iran chkorcni
			j++; //processneri indexna
			while(ft_check_char(SEPERATORS, line[i]))
				i++;
			check->index = i;
			continue ;
		}
	}
	get_process(line, i, check, j);
	printf("j :%d\n", j);
	// for(int k = 0; k < check->argc; k++)
	// {
	// 	printf("Process name: %s\n", check->coms[k].pr);
	// 	printf("Process args: %s\n", check->coms[k].args);
	// }
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

int execute(t_checks *check, char **envp)
{
	pid_t pid;
	int status;

	printf("args = %s\n", check->coms[0].args);
	pid = fork();
	if (pid == 0) 
  	{
    	if (execve(check->coms[0].pr, &check->coms[0].args, envp) == -1) 
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

int builtin(t_checks *check, char **env)
{
	int i;
	i = 0;

	if (check->coms->pr == NULL)
	{
		return (1);
	}
	while (i < builtins_count())
	{
		if (ft_strcmp(check->coms->pr, builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(&check->coms->args); // 2rd popoxakan@ petqa mer erkchap@ lini;
		}
		i++;
	}
	return (execute(check, env));
}

int		main(int argc, char **argv, char **envp)
{
	char *line;
	int status;
	int pid;
	int	cpid;
	t_checks check;

	status = 1;
	while (status)
	{
		write(1, "Shell> ", 7); //command prompt
		zero_checks(&check); //zroyacnuma
		get_next_line(0, &line); //input 
		parse_args(&check, line); // parse lines 
		builtin(&check, envp);
		//status = exec_args(&check);
		free_args(&check);
	}
	signal(SIGINT, my_int); // ctrl + C //
	signal(SIGQUIT, my_quit); // ctrl + \ //
	return (0);
}

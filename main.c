/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:50:13 by tharutyu          #+#    #+#             */
/*   Updated: 2021/06/02 14:32:03 by tharutyu         ###   ########.fr       */
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
	"unset"
};

int (*builtin_func[]) (t_checks *, int) = {
	&to_cd,
	&to_exit,
	&to_pwd,
	&to_echo,
	&to_env,
	&to_export,
	&to_unset
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

char **ft_delete_env_var(int k, char **env)
{
	t_checks 	temp;
	char 		**newenv;
	int 		i; 
	int 		j;
	
	i = 0;
	j = 0;
	while(env[i])
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
	i = 0;
	while(temp.env[j])
	{
		if(j != k)
		{
			newenv[i] = ft_strdup(temp.env[j]);
			i++;
		}
		j++;
	}
	newenv[i] = NULL;
	j = 0;
	while(temp.env[j])
	{
		free(temp.env[j]);
		++j;
	}
	free(temp.env);
	return (newenv);
}

int to_unset(t_checks *check, int p) // mer unsetn a kayfot funkcia a
{
	int i;
	int j;

	i = 1;
	if (check->coms[p].pr[1] == NULL)  // ete mi argumenta petqa es tpi
	{
		write(1, "unset: not enough arguments\n", 28);
		return (0);
	}
	else
		while (check->coms[p].pr[i])
		{
			j = 0;
			while (check->env[j])
			{
				if (!ft_strncmp(check->env[j], check->coms[p].pr[i], ft_var_len(check->env[j], '=')))
				{
					check->env = ft_delete_env_var(j, check->env);
				}
				j++;
			}
			i++;
		}	

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
	
	if (!ft_isalpha(str[0]) && (str[0] != '_' ))
	{
		printf("export: not an identifier: %c\n", str[0]);
		return (env);
	}
	i = 1;
	while (str[i] != '\0' && str[i] != '=') ///ste petqa return ani het gna erkrord exportn ani voch te segfault ta 2 argumenti depqum gandon@@@
	{
		if (!ft_export_char(str[i]))
		{			
			printf("export: not valid in this context: %s\n", str);
			return (env);
		}
		i++;
	}
	i = 0;
	j = 0;
	while(env[i])
		i++;
	i++;
	init_envp(env, &temp);
	while(env[j])
	{
		free(env[j]);
		j++;
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
	return (newenv);
}

int to_export(t_checks *check, int p)
{
	int i;
	int j;

	i = 1;
	if (check->coms[p].pr[1] == NULL) // ete mi argumenta petqa env@ tpi
		return (to_env(check, p));
	else
		while (check->coms[p].pr[i])
		{
			j = 0;
			while (check->env[j])
			{
				if (!ft_strncmp(check->env[j], check->coms[p].pr[i], ft_var_len(check->env[j], '=')))
				{
					free(check->env[j]);
					check->env[j] = ft_strdup(check->coms[p].pr[i]);
					break ;
				}
				j++;
			}
			if (check->env[j])
			{
				i++;
				continue ;
			}
			check->env = ft_add_env_var(check->coms[p].pr[i], check->env);
			i++;
		}
	return (0);
}

int to_env(t_checks *check, int p) // mer envna ughaki malloci pah@ garlakhaca
{
	int i;
	i = 0;

	(void)p;
	while (check->env[i])
	{
		write(1, check->env[i], ft_strlen(check->env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
int to_echo(t_checks *check, int p)
{
	int i;
	int nflag;

	nflag = 0;
	i = 1;
	if (!check->coms[p].pr[1])
	{
		write (1, "\n", 1);
		return (0);
	}
	if (ft_strcmp(check->coms[p].pr[1], "-n") == 0)
	{
		i++;
		nflag = 1;
	}
	while(check->coms[p].pr[i])
	{
		write(1, check->coms[p].pr[i], ft_strlen(check->coms[p].pr[i]));
		write(1, " ", 1);
		i++;
	}
	if (!nflag)
		write(1, "\n", 1);
	return (0);
}

int to_pwd(t_checks *check, int p)
{
	
	(void)p;
	(void)check;
	char buffer[1024];
	getcwd(buffer, 1024);
	printf("%s\n", buffer);
	return (0);
}

int to_exit(t_checks *check, int p)
{
	(void)check;
	p = 0;
	exit(1);
}

void	ft_change_pwd(t_checks *check, char *buff)
{
	int i;
	char *tmp;

	i = 0;
	while(check->env[i] && ft_strncmp("PWD=", check->env[i], 4))
		i++;
	if (check->env[i])
	{
		free(check->env[i]);
		check->env[i] = ft_strdup("PWD=");
		check->env[i] = ft_strjoin(check->env[i], buff);
	}
	else
	{
		tmp = ft_strdup("PWD=");
		tmp = ft_strjoin(tmp, buff);
		//printf("%s\n", tmp);
		check->env = ft_add_env_var(tmp, check->env);
	}
}

int to_cd(t_checks *check, int p)
{
	int 	i;
	char 	buff[1024];

	i = 0;
	if (check->coms[p].pr[1] == NULL) 
	{
		while (check->env[i] && ft_strncmp("HOME=", check->env[i], 5))
			i++;
		if(!check->env[i])
			return (printf("NO HOME\n"));
		if (chdir(check->env[i] + 5) != 0) 
    	{
      		perror("lsh");
   		}
  	} 
	else 
	{
		if (chdir(check->coms[p].pr[1]) != 0) 
    	{
      		perror("lsh");
   		}
  	}
  	getcwd(buff, 1024);
  	ft_change_pwd(check, buff);
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
			free(check->coms[i].pr[j]);
			j++;
		}
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

int		word_count_base(char *line, t_checks *check, char *base, int num)  //complete I think. Word count
{
	int i;
	int n;

	n = 1;
	i = 0;
	while (i < num)
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
				if (i == num)
					n--;
				continue ;
			}
		}
		i++;
	}
	return (n);
}

int		ft_check_rtn(char *str, char **buff, t_checks *check)
{
	char *tmp;

	if (str[1] == '?')
	{
		tmp = ft_itoa(check->rtn);
		*buff = ft_strjoin(*buff, tmp);
		free (tmp);
		return (2);
	}
	else
		return (0);
}

int		ft_get_var(char **envp, char *str, char **buff)
{
	int i;
	int z;
	char *tmp;

	i = 1;
	//	if(ft_isdigit(str[i]))
		//error;
	while(ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if(i == 1)
		*buff = ft_strjoin(*buff, "$");
	if(i == 1)
		return(1);
	tmp = malloc(sizeof(char) * (i + 1));
	tmp = ft_substr(str, 1, i - 1);
	tmp = ft_strjoin(tmp, "=");
	z = 0;
	while(envp[z])
	{
		if(!ft_strncmp(tmp, envp[z], i))
		{
			free(tmp);
			tmp = ft_strdup(envp[z] + i);
			break;
		}
		z++;
	}
	if(envp[z])
		*buff = ft_strjoin(*buff, tmp);
	free(tmp);
	return (i);
}

void ft_trim_quotes(char **str1, t_checks *check) //done test ara vorovhetev trucik em nayel, norme chi ancnum mek el
{
	int i;
	char *buff;
	char *tmp;
	char *str;

	str = *str1;
	i = 0;
	tmp = malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	buff = malloc(sizeof(char));
	buff[0] = '\0';
	while(str[i])
	{
		if(!check->dquote && str[i] == '\'')
		{
			check->quote = !check->quote;
			i++;
			continue;
		}
		if(!check->quote && str[i] == '\"')
		{
			check->dquote = !check->dquote;
			i++;
			continue;
		}
		// printf("c: %c  q: %d\n", str[i], check->quote);
		if((str[i] == '$') && !check->quote)
		{
			if(ft_check_rtn(str + i, &buff, check) == 2)
				i += 2;
			else
				i += ft_get_var(check->env, str + i, &buff);
			continue ;
		}
		tmp[0] = str[i];
		buff = ft_strjoin(buff, tmp);
		i++;
	}
	free(tmp);
	free(*str1);
	*str1 = ft_strdup(buff);
	free(buff);
}

int		ft_give_sep(char *str, t_checks *check, int j)
{
	if ((str[0] != '>' && ft_check_char(SEPERATORS, str[1])))
	{
		printf("syntax error near unexpected token %c\n", str[0]);
		return (1);
	}
	if (str[0] == ';' || !str[0])
		check->coms[j].rsep = 0;
	else if (str[0] == '>' && str[1] == '>')
		check->coms[j].rsep = 2;
	else if (str[0] == '>')
		check->coms[j].rsep = 1;
	else if (str[0] == '|')
		check->coms[j].rsep = 3;
	else if (str[0] == '<')
		check->coms[j].rsep = 4;
	if ((j + 1) != check->argc)
		check->coms[j + 1].lsep = check->coms[j].rsep;
	return (0);

}

void		get_process(char *line, int n, t_checks *check, int j)
{
	int i;
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
		ft_trim_quotes(&check->coms[j].pr[z], check);
		i += ft_word_len(line + i);
		z++;
	}
	if(ft_give_sep(line + n, check, j))
		return ;
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
	get_process(line, i, check, j);
}

void	zero_checks(t_checks *check)
{
	check->index = 0;
	check->argc = 0;
	check->is_process = 0;
	check->quote = 0;
	check->dquote = 0;
}

int execute(t_checks *check, int j)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) 
  	{
    	if (execve(check->coms[j].pr[0], check->coms[j].pr, check->env) == -1) 
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
      		waitpid(pid, &status, WUNTRACED); // означает  возвращать  управление также для остановленных дочерних процессов, о чьем
              									//статусе еще не было сообщено.
   		}
    	while (!WIFEXITED(status) && !WIFSIGNALED(status)); // WIFEXITED(status) не равно нулю, если дочерний процесс нормально завершился.	// 
  } 													//   WIFSIGNALED(status)  возвращает    истинное   значение,   если   дочерний   процесс   завершился   из-за
 															//неперехваченного сигнала.
  return (1);
}

int builtin(t_checks *check)
{
	int i;
	int j;

	j = 0;
	while(j < check->argc)
	{
		i = 0;
		while (i < builtins_count())
		{
			if (ft_strcmp(check->coms[j].pr[0], builtin_str[i]) == 0)
			{
				check->rtn = (*builtin_func[i])(check, j);
				if (j + 1 == check->argc)
					return (0);
				i++;
				break ;
			}
			i++;
		}
		if (i == builtins_count())
			execute(check, j);
		j++;
	}
	return (0);
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
	// int pid;
	// int	cpid;
	(void)argv;
	(void)argc;
	t_checks check;

	init_envp (envp, &check);
	signal(SIGINT, my_int); // ctrl + C //
	signal(SIGQUIT, my_quit); // ctrl + \ //
	check.rtn = 0;
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
	if (feof(stdin))  // cntrl + D , bayc chi ashkhatum boozeh
	{
		exit(0);
	return (0);
	}
	return (0);
}

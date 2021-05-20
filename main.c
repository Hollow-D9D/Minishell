/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:50:13 by tharutyu          #+#    #+#             */
/*   Updated: 2021/05/21 00:53:26 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//GEV ERROR HANDLING PETQA ARVI HENC HIMA ES PARSING EM ANUM 


#include "minishell.h"

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

int ft_word_len(char *line) //valid function  menak imaci vor quoteri tvern ela hashvum
{
	int i;
	int q; //quote
	int dq; //double quote

	printf("%c\n", line[0]);
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

int		get_process(char *line, int n, t_checks *check, int j)
{
	int i;

	i = -1;
	while(++i < n)
	{
		if (!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if (!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if (!check->dquote && !check->quote && !ft_check_char(SPACES, line[i]))
		{
			if (!check->is_process)  //check if first word, as the first word represents the process        nayuma arajinna(processna) te che
			{
				check->coms[j].pr = ft_substr(line, i, ft_word_len(line+i)); //vercnuma process@ qcuma struct stegh zagvozdka ka qani vor es mtacum em chishta verjnakan count imanal u heto malloc anel, dranic heto nor parse anel
				check->is_process = 1;
			}
			//else
				//parse_process_arg(line+i);  //parse process arguments    processi argumentnerna parse anum
		}
	}
	return 1;
	//give_seperator();                    //parse pipes redirections and so on for processes arden sksuma input output irar kapel. fork anel ev ayln
}

void	parse_args(t_checks *check, char *line)
{
	int i;
	int j;

	i = -1;
	j = 0;
	check->argc = arg_count_base(line, check, SEPERATORS); //malloci hamar petqa vor imanas qani processi tegh es bacum
	check->coms = malloc(sizeof(t_process) * check->argc);
	while (line[++i])  //anavarta der mtacum em sra vra
	{
		// while(line[i] && !check->dquote && !check->quote && !ft_check_char(SEPERATORS, line[i])) //skip until the seperator to take one process and parse
		// {
		// 	if (!check->dquote && line[i] == '\'')  //quote-handled
		// 	check->quote = !check->quote;
		// 	if (!check->quote && line[i] == '\"')
		// 	check->dquote = !check->dquote;
		// 	i++;
		// }
		// i = give_checks(line, i, check, j);  //parse anum 1 process@
		// check->index = i; //index@ petqa vor 
		if(!check->dquote && line[i] == '\'')  //quote-handled
			check->quote = !check->quote;
		if(!check->quote && line[i] == '\"')
			check->dquote = !check->dquote;
		if(!check->dquote && !check->quote && !ft_check_char(SEPERATORS, line[i])) // seperatori conditionna test arac chi
		{
			i = get_process(line, i, check, j); //veradarcnuma tiv vor i-n iran chkorcni
			j++; //processneri indexna
			continue ;
		}
		i++;
	}
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

int		main(int argc, char **argv, char **envp)
{
	char *line;
	int status;

	status = 1;
	/*
	t_checks check;
	char *line;
	int status;
	int pid;
	int	cpid;

	pid = fork();
	if (pid != 0)
		cpid = wait(NULL);
	status = 1;
	printf("%d\n", getpid());
	//ini_checks(&check);  //checkerna talis seperatorneri mek el spaceri
	while (status)
	{
		write(1, "SUPERCOOL SHELL >", 17); //command prompt
		zero_checks(&check); //zroyacnuma
		get_next_line(0, &line); //input 
		//parse_args(&check, line); // parse lines 
		//status = exec_args(&check);
	}
	*/
	while (status)
	{
		write(1, "SUPERCOOL SHELL >", 17); //command prompt
		get_next_line(0, &line); //input 
		printf("%d\n", ft_word_len(line));
	}
	return (0);
}

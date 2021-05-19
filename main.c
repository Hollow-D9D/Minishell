/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:50:13 by tharutyu          #+#    #+#             */
/*   Updated: 2021/05/15 04:03:01 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//GEV ERROR HANDLING PETQA ARVI HENC HIMA ES PARSING EM ANUM 


#include "minishell.h"

typedef	struct	s_process
{
	char	*pr; //process name
	char	*args; //arguments
	int		fd[2]; //input output for pipe
	int		rtnv; //process return value
}				t_process;

typedef struct	s_checks
{
	char		*checks; //seperatornerna
	char		*spaces; //space...
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

// int ft_len_char(char *line, t_checks *check)
// {
// 	int i;

// 	while(line[i] && !ft_check_char(line[i], check->spaces) && !ft_check_char(line[i], check->checks))  //zut nayuma vor 1 bar vercni, minchev seperator space kam el \0
// 		i++;
// 	return (i);
// }

// int		give_checks(char *line, int n, t_checks *check, int j)
// {
// 	int i;

// 	i = -1;
// 	while(++i < n)
// 	{
// 		while(!ft_check_char(line[i], check->spaces)) //skip spaces
// 			i++;
// 		if(!check->is_process)  //check if first word, as the first word represents the process        nayuma arajinna(processna) te che
// 		{
// 			check->comms[j].pr = ft_substr(line+i, ft_len_char(line+i, check)); //vercnuma process@ qcuma struct stegh zagvozdka ka qani vor es mtacum em chishta verjnakan count imanal u heto malloc anel, dranic heto nor parse anel
// 			check->is_process = 1;
// 		}
// 		else
// 			parse_process_arg(line+i);  //parse process arguments    processi argumentnerna parse anum
// 	}
// 	give_seperator();                    //parse pipes redirections and so on for processes arden sksuma input output irar kapel. fork anel ev ayln
// }

// int		arg_count(char *line, t_checks *check)  //complete I think, stuguma qani process es pass arel
// {
// 	int i;
// 	int n;

// 	n = 1;
// 	i = 0;
// 	while(line[i])
// 	{
// 		if(!check->dquote && line[i] == '\'')  //quote-handled
// 			check->quote = !check->quote;
// 		if(!check->quote && line[i] == '\"')
// 			check->dquote = !check->dquote;
// 		if(!check->dquote && !check->quote)
// 		{
// 			if(ft_check_char(check->checks, line[i]))
// 				n++;
// 		}
// 		i++;
// 	}
// 	return (n);
// }

// void	parse_args(t_checks *check, char *line)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	j = 0;
// 	check->argc = arg_count(line, check); //malloci hamar petqa vor imanas qani processi tegh es bacum
// 	check->coms = malloc(sizeof(t_process) * check->args);
// 	while (line[++i])  //anavarta der mtacum em sra vra
// 	{
// 		while(line[i] && !check->dquote && !check->quote && !ft_check_char(check->checks, line[i])) //skip until the seperator to take one process and parse
// 		{
// 			if (!check->dquote && line[i] == '\'')  //quote-handled
// 			check->quote = !check->quote;
// 			if (!check->quote && line[i] == '\"')
// 			check->dquote = !check->dquote;
// 			i++;
// 		}
// 		i = give_checks(line, i, check, j);  //parse anum 1 process@
// 		check->index = i; //index@ petqa vor 
// 		j++;
// 	}
// }

// void	zero_checks(t_checks *check)
// {
// 	check->index = 0;
// 	check->argc = 0;
// 	check->is_process = 0;
// 	check->quote = 0;
// 	check->dquote = 0;
// 	check->pipe = 0;
// 	check->redir = 0;
// 	check->great = 0;
// 	check->less = 0;
// 	check->scolon = 0;
// }

// void	ini_checks(t_checks *check)
// {
// 	check->checks = ft_strdup("><|;");
// 	check->spaces = ft_strdup("\t\r\v\f ");
// }

int		main(int argc, char **argv, char **envp)
{
	// t_checks check;
	char *line;
	int status;

	status = 1;
	signal(SIGINT, my_int); // ctrl + C //
	signal(SIGQUIT, my_quit); // ctrl + \ //
	// ini_checks(&check);  //zroyacnuma u checkerna talis seperatorneri mek el spaceri
	while (status)
	{
		write(1, "SUPERCOOL SHELL >", 17); //command prompt
		// zero_checks(&check);
		if(!get_next_line(0, &line)) //input
			break; 
		// parse_args(&check, line); // parse lines 
		//status = exec_args(&check);
	}
	printf("Valod\n");
	return (0);
}

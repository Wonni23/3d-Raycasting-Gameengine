/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:33:31 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/17 19:33:52 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_including_letter(t_parse *parse, char *s)
{
	int	i;
	int	coma_c;

	i = -1;
	coma_c = 0;
	if (s[0] == ',')
		exit_parse(NULL, 1, \
			"C or F must have 3 intergers separeted by a coma", parse);
	while (s[++i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ',' && s[i] != ' ' \
		&& !(s[i] > 8 && s[i] < 14))
			exit_parse(NULL, 1, \
			"C or F must not contain any characters", parse);
		if (s[i] == ',')
			coma_c++;
	}
	if (coma_c < 2)
		exit_parse(NULL, 1, \
			"C or F must have 3 intergers separeted by a coma", parse);
}

void	check_spaces_between_digits(t_parse *parse, char *s)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (ft_isdigit(s[i]))
		{
			if (s[i + 1] == ' ')
			{
				j = i + 1;
				while (s[j] == ' ')
					j++;
				if (ft_isdigit(s[j]))
					exit_parse(NULL, 1, \
					"Space exists between digits", parse);
			}
		}
	}
}

void	num_vars_check_3(int *num, int *val)
{
	(*num)++;
	(*val)++;
}

void	num_vars_check_2(t_parse *parse, char *file, int *num)
{
	while(ft_isspace(*file))
		file++;
	if (!ft_strncmp(file, "NO", 2))
		num_vars_check_3(num, &parse->has_n);
	else if (!ft_strncmp(file, "SO", 2))
		num_vars_check_3(num, &parse->has_s);
	else if (!ft_strncmp(file, "WE", 2))
		num_vars_check_3(num, &parse->has_w);
	else if (!ft_strncmp(file, "EA", 2))
		num_vars_check_3(num, &parse->has_e);
	else if (!ft_strncmp(file, "F", 1))
		num_vars_check_3(num, &parse->has_f);
	else if (!ft_strncmp(file, "C", 1))
		num_vars_check_3(num, &parse->has_c);
}

int	num_vars_check(t_parse *parse)
{
	int	num;
	int	i;

	i = -1;
	num = 0;
	parse->has_n = 0;
	parse->has_s = 0;
	parse->has_e = 0;
	parse->has_w = 0;
	parse->has_c = 0;
	parse->has_f = 0;
	while (parse->file[++i])
		num_vars_check_2(parse, parse->file[i], &num);
	if (num == 6 && parse->has_n == 1 && parse->has_s == 1 \
		&& parse->has_e == 1 && parse->has_w == 1 \
		&& parse->has_c == 1 && parse->has_f == 1)
		return (0);
	else
		return (1);
}

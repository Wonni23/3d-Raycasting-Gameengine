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

void	check_image_order(t_parse *parse, char *s)
{
	if (*s == 'N')
		parse->num_vars = 0;
	if (*s == 'S')
		parse->num_vars = 1;
	if (*s == 'W')
		parse->num_vars = 2;
	if (*s == 'E')
		parse->num_vars = 3;
}

int	num_vars_check(t_parse *parse)
{
	int	num;
	int	i;

	i = -1;
	num = 0;
	while (parse->file[++i])
	{
		if (!ft_strncmp(parse->file[i], "NO", 2)
			|| !ft_strncmp(parse->file[i], "SO", 2)
			|| !ft_strncmp(parse->file[i], "WE", 2)
			|| !ft_strncmp(parse->file[i], "EA", 2)
			|| !ft_strncmp(parse->file[i], "F", 1)
			|| !ft_strncmp(parse->file[i], "C", 1))
			num++;
	}
	if (num == 6)
		return (0);
	else
		return (1);
}

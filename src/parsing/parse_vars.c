/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:51:01 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/05 23:41:19 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	fill_color(t_cub *cub, t_parse *parse, char *s)
{
	int	i;
	int	rgb[3];

	i = -1;
	rgb[++i] = ft_atoi(s);
	if (rgb[i] > 255 || rgb[i] < 0)
		exit_parse(cub, 1, \
			"atoi overflow only can accept between 0 and 255", parse);
	while (++i < 3)
	{
		while (ft_isdigit(*s))
			s++;
		if (*s != ',')
			exit_parse(cub, 1, \
			"C or F must have 3 intergers separeted by a coma", parse);
		s++;
		rgb[i] = ft_atoi(s);
		if (rgb[i] > 255 || rgb[i] < 0)
			exit_parse(cub, 1, \
			"atoi overflow only can accept between 0 and 255", parse);
	}
	i = 255;
	return (i << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

static int	fill_args(t_cub *cub, t_parse *parse, char *s, int path_i, color_i)
{
	char	*str;

	if (ft_strncmp(s, "C", 1) && ft_strncmp(s, "F", 1))
	{
		if (path_i > 3)
			return (1);
		s += 2;
		str = ft_strtrim(s, " \n\t");
		if (!str)
			return (1);
		parse->path_to_img[path_i] = ft_strdup(str);
		free_arr(str);
		if (!parse->path_to_img[path_i])
			return (1);
	}
	else
	{
		s += 1;
		while (ft_isspace(*s))
			s++;
		cub->img.colors[color_i] = fill_color(cub, parse, s);
	}
	return (0);
}

static int	find_args(t_cub *cub, t_parse *parse, char *s, char *compare)
{
	int	color_i;

	color_i = -1;
	if (ft_strncmp(s, compare, ft_strlen(compare)))
	{
		if (!ft_strncmp(s, "C", 1))
			color_i = 1;
		else if (!ft_strncmp(s, "F", 1))
			color_i = 0;
		else
			cub->img.order[++parse->num_vars] = compare[0];
		if (fill_args(parse, s, parse->num_vars, color_i))
			exit_parse(cub, 1, "Error with malloc", parse);
		return (0);
	}
	return (1);
}

static int	choose_var(t_cub *cub, t_parse *parse, char *s)
{
	if (!find_args(cub, parse, s, "NO"))
		return (0);
	else if (!find_args(cub, parse, s, "SO"))
		return (0);
	else if (!find_args(cub, parse, s, "WE"))
		return (0);
	else if (!find_args(cub, parse, s, "EA"))
		return (0);
	else if (!find_args(cub, parse, s, "F"))
		return (0);
	else if (!find_args(cub, parse, s, "C"))
		return (0);
	return (1);
}

int	get_vars(t_cub *cub, t_parse *parse)
{
	int	i;
	int	j;
	int	num_vars;

	parse->path_to_img = ft_calloc(sizeof(char *) * 5);
	if (!parse->path_to_img)
		exit_parse(cub, 1, "Error with malloc", parse);
	num_vars = 0;
	i = -1;
	while (parse->file[++i] && num_vars != 6)
	{
		j = -1;
		while (parse->file[i][++j])
		{
			if (!ft_isspace(parse->file[i][j]) && parse->file[i][j])
			{
				if (choose_var(cub, &parse->file[i][j]))
					exit_parse(cub, 1, "Invalid key", parse);
				num_vars++;
				break ;
			}
		}
	}
	return (i);
}

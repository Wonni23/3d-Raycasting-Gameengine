/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:48:04 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/05 23:39:53 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	counting_lines(t_parse *parse, int y)
{
	int	count_lines;

	count_lines = 0;
	while (parse->file[y])
	{
		count_lines++;
		y++;
	}
	return (count_lines);
}

static void	get_map(t_cub *cub, t_parse *parse, int y)
{
	int	i;
	int	num_lines;

	while (parse->file[y])
	{
		if (ft_strlen(parse->file[y]) > 1)
			break ;
		y++;
	}
	num_lines = counting_lines(parse, y);
	cub->map.map = ft_calloc(num_lines + 1, sizeof(char *));
	if (!cub->map.map)
		exit_parse(cub, 1, "malloc with map", parse);
	i = -1;
	while (parse->file[y])
	{
		cub->map.map[++i] = ft_strdup(parse->file[y]);
		if (!cub->map.map[i])
			exit_parse(cub, 1, "malloc with map", parse);
		y++;
	}
}

void	parse_file(t_cub *cub, t_parse *parse)
{
	int	y;
	int	i;

	parse->path_to_img = ft_calloc(5, sizeof(char *));
	if (!parse->path_to_img)
		exit_parse(NULL, 1, "Error with malloc", parse);
	y = get_vars(cub, parse);
	i = -1;
	while (parse->path_to_img[++i])
		;
	if (i != 4)
		exit_parse(NULL, 1, "must contain NO SO WE EA path to the files" \
		, parse);
	get_map(cub, parse, y);
}

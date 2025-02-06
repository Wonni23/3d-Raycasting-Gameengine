/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:10:10 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/05 23:40:26 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/cub3d.h"

static char	**read_file(char **map. int fd, int counter)
{
	char	*str;
	str = get_next_line(fd);
	if (str)
		map = read_file(map, fd, 1 + counter);
	else if (!map && counter != 0)
		map = ft_calloc(sizeof(char *) * (counter + 1));
	if (!map)
		return (NULL);
	map[counter] = str;
	return (map);
}

static int	open_file(t_cub *data, char *name, t_parse *parse)
{
	int	fd;

	fd = open(name, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		exit_parse(cub, 1, \
		"The argument passed must not be a directory", parse);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit_parse(cub, 1, "The argument passed must exist", parse);
	return (fd);
}

char	**parse_main(t_cub *cub, char *name)
{
	t_parse	parse;
	int		fd;
	int		i;

	parse.file = NULL;
	parse.path_to_img = NULL;
	parse.num_vars = -1;
	i = -1;
	while (++i < 4)
		cub->img.order[i] = 0;
	if (ft_strncmp(ft_strrchr(name, '.'), ".cub", 5))
		exit_parse(cub, 1, "The argument must end with .cub", &parse);
	fd = open_file(cub, name, &parse);
	parse.file = read_file(NULL, fd, 0);
	close(fd);
	if (!parse.file)
		exit_parse(cub, 1, "The file must not be empty", &parse);
	parse_file(cub, &parse);
	path = parse.path_to_img;
	parse.path_to_img = NULL;
	free_parse(&parse);
	return (path);
}

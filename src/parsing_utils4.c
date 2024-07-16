/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:50:58 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/15 14:30:28 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	char_to_int(char c)
{
	if (c == '1')
		return (WALL);
	if (c == '0')
		return (FLOOR);
	if (c == 'N')
		return (N);
	if (c == 'S')
		return (S);
	if (c == 'E')
		return (E);
	if (c == 'W')
		return (W);
	if (c == ' ')
		return (NOTHING);
	return (-1);
}

void	trim_whitespace(char **line)
{
	char	*end;

	while (ft_isspace((unsigned char)**line))
		(*line)++;
	end = *line + ft_strlen(*line) - 1;
	while (end > *line && ft_isspace((unsigned char)*end))
		end--;
	end[1] = '\0';
}

int process_map_line(t_map *map, char *line, int y)
{
    int j = 0;
    char c;
    int line_length;
    int boundary_error;

    line_length = strlen(line);
    boundary_error = 0;
    while (j < line_length)
	{
        c = line[j];
        if (!valid_char(c))
		{
            printf("Error: Unexpected character '%c' at position %d\n", c, j);
            return 1;
        }
        map->mapp[y * map->mapx + j] = char_to_int(c);
        if ((y == 0 || y == map->mapy - 1 || j == 0 || j == line_length - 1) && char_to_int(c) == FLOOR)
		{
            boundary_error = 1;
        }
        j++;
    }
    if (boundary_error)
	{
        printf("Error: '0' found at border.\n");
        return 1;
    }
    return 0;
}


int parse_map(t_map *map, char **lines)
{
    int i;
    char *line;

	i = 0;
    if (get_map_dimensions(map, lines) == -1)
	{
        printf("Error\nCould not get map dimensions\n");
        return (-1);
    }
    map->mapp = malloc(sizeof(int) * (map->mapx * map->mapy));
    if (!map->mapp)
        return (ENOMEM);
    while (lines[i])
	{
        line = lines[i];
        if (process_map_line(map, line, i) != 0)
            return 1;
        i++;
    }
    int y = 0;
    while (y < map->mapy)
	{
        int line_length = strlen(lines[y]);
        int j = line_length;
        while (j < map->mapx)
		{
            map->mapp[y * map->mapx + j] = WALL;
            j++;
        }
        y++;
    }
    return 0;
}

int get_map_dimensions(t_map *map, char **lines) {
    int x;
	int y;
    char *line;

    map->mapx = 0;
    map->mapy = 0;
    y = 0;
    while (lines[y])
	{
        line = lines[y];
        trim_whitespace(&line);
        x = strlen(line);
        if (x > map->mapx) map->mapx = x;
			map->mapy++;
        y++;
    }
    if (map->mapx > 0 && map->mapy > 0)
        return 0;
    return -1;
}






/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:59:31 by fluchten          #+#    #+#             */
/*   Updated: 2023/04/23 17:15:00 by fluchten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ft_mlx_pixel_put draws a pixel of specified color on the image
at the x and y position */
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/* get_line_height calculates the height of the line to be draw on the screen */
int	get_line_height(t_data *data)
{
	return ((int)(data->win_h / data->ray.perpwalldist));
}

/* get_lowest_pixel calculates the lowest pixel to fill
in the current band */
int	get_lowest_pixel(t_data *data, int line_height)
{
	int	draw_start;

	draw_start = -line_height / 2 + data->win_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	return (draw_start);
}

/* get_highest_pixel calculates the highest pixel to fill
in the current band */
int	get_highest_pixel(t_data *data, int line_height)
{
	int	draw_end;

	draw_end = line_height / 2 + data->win_h / 2;
	if (draw_end >= data->win_h)
		draw_end = data->win_h - 1;
	return (draw_end);
}

/* get_color returns the color value of a specific pixel in a texture */
int	get_color(t_data *data, int x, int y, int i)
{
	return (*(int *)(data->mat[i].addr + (y * data->mat[i].line_length + x
			*(data->mat[i].bpp / 8))));
}

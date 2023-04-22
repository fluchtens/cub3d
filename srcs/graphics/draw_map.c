/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:20:26 by fluchten          #+#    #+#             */
/*   Updated: 2023/04/22 17:32:52 by fluchten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_material(t_data *data, t_ray *ray, int start, int line_height)
{
	if (ray->side == 0)
		ray->wall_x = data->ray.y + ray->perpwalldist * ray->ray_dir_y;
	else
		ray->wall_x = data->ray.x + ray->perpwalldist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = ray->wall_x * data->game.mat_px;
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = data->game.mat_px - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = data->game.mat_px - ray->tex_x - 1;
	ray->step = 1.0 * data->game.mat_px / line_height;
	ray->tex_pos = (start - data->win_h / 2
			+ line_height / 2) * ray->step;
}

static void	draw_material(t_data *data, int x, int texture)
{
	int	color;

	color = get_color(data, data->ray.tex_x, data->ray.tex_y, texture);
	ft_mlx_pixel_put(&data->img, x, data->ray.start, color);
}

void	draw_map(t_data *data, t_ray *ray, int x)
{
	int	line_height;

	line_height = get_line_height(data);
	ray->start = get_lowest_pixel(data, line_height);
	ray->end = get_highest_pixel(data, line_height);
	get_material(data, ray, ray->start, line_height);
	while (ray->start < ray->end)
	{
		ray->tex_y = (int)ray->tex_pos & (data->game.mat_px - 1);
		ray->tex_pos += ray->step;
		if (ray->side == 1 && ray->ray_dir_y < 0)
			draw_material(data, x, SO);
		else if (ray->side == 1 && ray->ray_dir_y > 0)
			draw_material(data, x, NO);
		else if (ray->side == 0 && ray->ray_dir_x < 0)
			draw_material(data, x, WE);
		else if (ray->side == 0 && ray->ray_dir_x > 0)
			draw_material(data, x, EA);
		ray->start++;
	}
}
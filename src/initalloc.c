/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:33:41 by amylle            #+#    #+#             */
/*   Updated: 2024/06/24 23:34:08 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <pthread.h>

bool	checkinput(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	if (argc != 5 && argc != 6)
		return (false);
	while (argv[++j])
	{
		i = -1;
		while (argv[j][++i])
			if (ft_isdigit(argv[j][i]) == 0)
				return (false);
	}
	return (true);
}

int	init_values(t_data *data, char **argv, int argc)
{
	data->philo_num = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->meal_num = ft_atoi(argv[5]);
		if (data->meal_num <= 0)
			return (error("Invalid input", NULL));
	}
	else
		data->meal_num = -1;
	if (data->philo_num <= 0 || data->philo_num > 200 || data->die_time < 0 \
		|| data->eat_time < 0 || data->sleep_time < 0)
		return (error("Invalid input", NULL));
	data->dead = 0;
	data->num_finished_eating = 0;
	return (0);
}

//init to NULL so you can safely free all incase of malloc error
int	alloc_data(t_data *data)
{
	int	i;

	data->forks = NULL;
	data->tid = NULL;
	data->philos = NULL;
	data->forks = malloc(data->philo_num * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (error("Malloc error: forks", data));
	data->tid = malloc(data->philo_num * sizeof(pthread_t));
	if (!data->tid)
		return (error("Malloc error: tid", data));
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	if (!data->philos)
		return (error("Malloc error: philos structs", data));
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (error("Pthread init fail", data));
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (error("Pthread init fail", data));
	i = -1;
	while (++i < data->philo_num)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error("Mutex init fail", data));
	return (0);
}

int	init_philos(t_data *data)
{
	int		i;

	data->philos[0].l_fork = data->forks[data->philo_num - 1];
	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].data = data;
		if (i != 0)
			data->philos[i].l_fork = data->forks[i - 1];
		data->philos[i].r_fork = data->forks[i];
		data->philos[i].num = i + 1;
		data->philos[i].eating = 0;
		data->philos[i].eating = 0;
		data->philos[i].time_to_starve = data->die_time;
		if (pthread_mutex_init(&data->philos[i].lock, NULL))
			return (error("Pthread init philo lock error", data));
	}
	return (0);
}

int	init_data(t_data *data, char **argv, int argc)
{
	if (init_values(data, argv, argc) == 1)
		return (1);
	if (alloc_data(data) == 1)
		return (1);
	if (init_philos(data) == 1)
		return (1);
	return (0);
}

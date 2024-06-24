/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:32:05 by amylle            #+#    #+#             */
/*   Updated: 2024/06/24 23:32:07 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <pthread.h>

//idk how to fix the uninitialized mutex error
void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num && data->forks && data->philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
	if (data->tid)
		free (data->tid);
	if (data->forks)
		free (data->forks);
	if (data->philos)
		free (data->philos);
}

int	error(char *str, t_data *data)
{
	if (data)
		pthread_mutex_lock(&data->write);
	printf("%s\n", str);
	if (data)
	{
		pthread_mutex_unlock(&data->write);
		free_data(data);
	}
	return (1);
}

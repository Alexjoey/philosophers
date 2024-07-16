/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:46:51 by amylle            #+#    #+#             */
/*   Updated: 2024/06/24 16:51:42 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

unsigned long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (error("gettimeofday error", NULL));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(useconds_t time)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num && data->forks)
		pthread_mutex_destroy(&data->forks[i]);
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

void	message(char *s, t_philo *p)
{
	pthread_mutex_lock(&p->data->write);
	pthread_mutex_lock(&p->data->lock);
	if (p->data->dead == 0)
	{
		printf("%llu %d %s\n", get_time() - p->data->start_time, p->num, s);
		if (s[0] == 'd' && p->data->dead == 0)
			p->data->dead = 1;
	}
	pthread_mutex_unlock(&p->data->lock);
	pthread_mutex_unlock(&p->data->write);
}

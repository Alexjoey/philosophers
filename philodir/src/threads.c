/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:10:40 by amylle            #+#    #+#             */
/*   Updated: 2024/06/24 16:51:43 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <pthread.h>

void	eat(t_philo *philo)
{
	if (philo->data->philo_num == 1)
	{
		message("has taken a fork", philo);
		ft_usleep(philo->data->die_time + 1);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->eating = 1;
	philo->eat_count++;
	philo->time_to_starve = get_time() + philo->data->die_time;
	pthread_mutex_unlock(&philo->eat_mutex);
	message("is eating", philo);
	ft_usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*state_checker(void *param)
{
	t_philo	*p;

	p = (t_philo *)param;
	while (pthread_mutex_lock(&p->data->lock) >= 0 && (p->data->dead == 0))
	{
		pthread_mutex_unlock(&p->data->lock);
		pthread_mutex_lock(&p->eat_mutex);
		if (get_time() >= p->time_to_starve && p->eating == 0)
			message("died", p);
		pthread_mutex_unlock(&p->eat_mutex);
		pthread_mutex_lock(&p->eat_mutex);
		if (p->eat_count == p->data->meal_num)
		{
			p->eat_count++;
			pthread_mutex_lock(&p->data->lock);
			p->data->num_finished_eating++;
			if (p->data->num_finished_eating == p->data->philo_num)
				p->data->dead = 1;
			pthread_mutex_unlock(&p->data->lock);
		}
		pthread_mutex_unlock(&p->eat_mutex);
		ft_usleep(1);
	}
	pthread_mutex_unlock(&p->data->lock);
	return ((void *) 0);
}

void	*routine(void	*param)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)param;
	data = philo->data;
	philo->time_to_starve = data->die_time + get_time();
	if (philo->num % 2)
		ft_usleep(philo->data->eat_time / 5);
	if (pthread_create(&philo->tid_philo, NULL, &state_checker, philo))
		return ((void *) 1);
	while (pthread_mutex_lock(&data->lock) >= 0 && data->dead == 0)
	{
		pthread_mutex_unlock(&data->lock);
		eat(philo);
		message("is sleeping", philo);
		ft_usleep(data->sleep_time);
		message("is thinking", philo);
	}
	pthread_mutex_unlock(&data->lock);
	if (pthread_detach(philo->tid_philo))
		return ((void *) 1);
	return ((void *) 0);
}

int	thread_init(t_data *data)
{
	int			i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->philo_num)
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error("error whilst creating routine threads", data));
	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->tid[i], NULL))
			return (error("error whilst joining threads", data));
	return (0);
}

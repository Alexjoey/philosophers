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
	if (philo->l_fork == philo->r_fork)
		return ;
	pthread_mutex_lock(philo->l_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_starve = get_time() + philo->data->die_time;
	message("is eating", philo);
	philo->eat_count++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*mealchecker(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	while (data->dead == 0)
		if (data->num_finished_eating == data->philo_num)
			data->dead = 1;
	return ((void *)0);
}

void	*state_checker(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_starve && philo->eating == 0)
			message("died", philo);
		if (philo->eat_count == philo->data->meal_num)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->num_finished_eating++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *) 0);
}

void	*routine(void	*param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->time_to_starve = philo->data->die_time + get_time();
	if (pthread_create(&philo->tid_philo, NULL, &state_checker, philo))
		return ((void *) 1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		message("is sleeping", philo);
		ft_usleep(philo->data->sleep_time);
		message("is thinking", philo);
	}
	if (pthread_join(philo->tid_philo, NULL))
		return ((void *) 1);
	return ((void *) 0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	data->start_time = get_time();
	if (data->meal_num > 0)
		if (pthread_create(&t0, NULL, &mealchecker, data))
			return (error("error whilst creating mealchecker", data));
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error("error whilst creating supervisor threads", data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->tid[i], NULL))
			return (error("error whilst joining threads", data));
	if (data->meal_num > 0)
		if (pthread_join(t0, NULL))
			return (error("error whilst joining threads", data));
	return (0);
}

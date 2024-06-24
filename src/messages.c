/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:23:35 by username          #+#    #+#             */
/*   Updated: 2024/06/13 14:24:46 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	message(char *str, t_philo *p)
{
	pthread_mutex_lock(&p->data->write);
	if (p->data->dead == 0)
	{
		printf("%llu %d %s\n", get_time() - p->data->start_time, p->num, str);
		if (!ft_strncmp(str, "died", 4) && p->data->dead == 0)
			p->data->dead = 1;
	}
	pthread_mutex_unlock(&p->data->write);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:00:05 by amylle            #+#    #+#             */
/*   Updated: 2024/06/13 14:00:11 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/inc/libft.h"
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

typedef	struct s_data t_data;
//just prototyping for s_philo

typedef struct	s_philo
{
	t_data			*data;
	pthread_t		tid_philo;
	int				num;
	int				eat_count;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	lock;
	unsigned long	time_to_starve;
	int				eating;
}					t_philo;

typedef struct	s_data
{
	pthread_t		*tid;
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meal_num;
	int				dead;
	int				num_finished_eating;
	int				start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
}		t_data;

int		init_data(t_data *data, char **argv, int argc);
int		error(char *str, t_data *data);
void	free_data(t_data *data);
#endif

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
typedef struct	s_philo
{

}		t_philo;

typedef struct	s_params
{
	int		philo_num;
	int		meal_num;
	int		dead;
	int		finished;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		t_start;
	t_philo	*philos;
}		t_params;

#endif

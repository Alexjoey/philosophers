/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:08:50 by username          #+#    #+#             */
/*   Updated: 2024/06/24 16:22:29 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (checkinput(argc, argv) == false)
		return (error("Invalid input", NULL));
	if (init_data(&data, argv, argc) == 1)
		return (1);
	if (thread_init(&data))
		return (1);
	free_data(&data);
	return (0);
}

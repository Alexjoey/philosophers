/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:08:50 by username          #+#    #+#             */
/*   Updated: 2024/06/13 14:12:56 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

int	main(int argc, char **argv)
{
	t_data	data;

	if (checkinput(argc, argv) == false)
		return (error("Invalid input", NULL));
	if (init_data(&data, argv, argc) == 1)
		return (1);
	free_data(&data);	
	return (0);
}

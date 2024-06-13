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

#include "../includes/philo.h"

bool	checkinput(char **argv)
{
	int	i;
	int	j;

	j = 0;
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
	if (argc == 5 || argc == 6)
	{
		if (checkinput(argv) == false)
		{
			ft_printf("invalid input\n");
			return (0);
		}
		
	}
	else
		ft_printf("wrong argument amount\n");
}

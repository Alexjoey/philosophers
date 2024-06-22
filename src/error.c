#include "../inc/philo.h"

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
	ft_printf("%s\n", str);
	if (data)
		free_data(data);
	return (1);
}

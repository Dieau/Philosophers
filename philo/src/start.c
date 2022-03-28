/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:34:21 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/03 16:31:30 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Initialisation des philosophes
// Deux fonctions par manque de place
void	*init_philo(t_data *args)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->nbr_philo);
	if (!philos)
		return (NULL);
	philo_generator(args, philos, i);
	return (NULL);
}

void	philo_generator(t_data *args, t_philo *philos, int i)
{
	while (i < args->nbr_philo)
	{
		philos[i].philo_id = i;
		philos[i].nbr_philo = args->nbr_philo;
		philos[i].eatings_total = 0;
		philos[i].eatings_total_goal = args->nbr_of_eating;
		philos[i].time_to_eat = args->time_to_eat;
		philos[i].time_to_sleep = args->time_to_sleep;
		philos[i].time_to_die = args->time_to_die;
		philos[i].last_eating = ft_time();
		philos[i].life_timer = args->time_to_die;
		philos[i].stop = 0;
		philos[i].left_fork = \
			&args->forks[philos[i].philo_id];
		philos[i].right_fork = \
			&args->forks[(philos[i].philo_id + 1) % args->nbr_philo];
		philos[i].data = args;
		i++;
	}
	args->all_philos = philos;
}

// Initialisation des mutex
void	*init_mutex(t_data *args)
{
	int				nbr_ph;
	pthread_mutex_t	*mutex;

	nbr_ph = args->nbr_philo;
	mutex = malloc(sizeof(pthread_mutex_t) * nbr_ph);
	if (!mutex)
		return (NULL);
	while (nbr_ph--)
		pthread_mutex_init(&mutex[nbr_ph], NULL);
	pthread_mutex_init(&args->lock_print, NULL);
	args->forks = mutex;
	return (NULL);
}

// Initialisation des threads
void	*init_threads(t_data *args)
{
	int			nbr_ph;
	pthread_t	*threads;
	pthread_t	s_tid;

	nbr_ph = args->nbr_philo;
	threads = malloc(sizeof(pthread_t) * nbr_ph);
	if (!threads)
		return (NULL);
	while (nbr_ph--)
		pthread_create(&threads[nbr_ph], \
			NULL, routine, (void *)&args->all_philos[nbr_ph]);
	pthread_create(&s_tid, NULL, surveillance, (void *)args->all_philos);
	pthread_join(s_tid, NULL);
	args->tids = threads;
	return (NULL);
}

// Remplit la struct avec les arguments
int	init_args(t_data *args, int argc, char **argv)
{
	args->nbr_philo = ft_atol(argv[1]);
	args->time_to_die = ft_atol(argv[2]);
	args->time_to_eat = ft_atol(argv[3]);
	args->time_to_sleep = ft_atol(argv[4]);
	args->dead = 0;
	if (argc == 6)
		args->nbr_of_eating = ft_atol(argv[5]);
	if (argc == 5)
	{
		if (args->nbr_philo < 1)
			return (0);
		args->nbr_of_eating = -1;
	}
	if (argc == 6)
	{
		if (args->nbr_of_eating < 1)
			return (0);
	}
	return (0);
}

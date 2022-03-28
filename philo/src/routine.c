/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:35:00 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/11 12:38:50 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Vérifie si le philosophe a atteint son objectif de repas
// Si il est atteint, on flag un stop que les autres philos verront
int	eatings_counter(t_philo *philo)
{
	int	full;
	int	i;

	if (philo->eatings_total != -1
		&& philo->eatings_total_goal > 0)
	{
		full = 1;
		i = -1;
		while (++i < philo->nbr_philo)
			if (philo[i].eatings_total < philo->eatings_total_goal)
				full = 0;
		if (full == 1)
		{
			i = -1;
			while (i < philo[i].nbr_philo)
			{
				philo[i].stop = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

// Print un msg dans un mutex lock pour la mort d'un philosophe
// Envoie le flag stop aux autres philosophes
void	dead_philo(t_philo *philo, int i)
{
	philo->data->dead = 1;
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d died\n", ft_time() - philo->start_time,
		philo[i].philo_id + 1);
	i = -1;
	while (i < philo[i].nbr_philo)
	{
		philo[i].stop = 1;
		i++;
	}
}

// On vérifie que les philosophes ont encore du temps de vie
// Si son temps de vie est écoulé, on le déclare mort
// Si le goal est atteint ou flag stop, ne fait rien
void	*surveillance(void *args)
{
	t_philo	*philo;
	long	time_now;
	int		i;

	philo = (t_philo *)args;
	i = 0;
	while (philo[i].stop == 0)
	{
		i = -1;
		while (++i < philo->nbr_philo)
		{
			time_now = ft_time();
			if (time_now - philo[i].last_eating > \
			philo[i].life_timer)
			{
				dead_philo(philo, i);
				pthread_mutex_unlock(&philo->lock_print);
				return (NULL);
			}
		}
		if (eatings_counter(philo) || philo->stop)
			return (NULL);
	}
	return (NULL);
}

// Handler pour la routine de vie des philosophes
// Reactualise leurs temps de départ
// Appelle les actions dans l'ordre logique
void	*routine(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	philo->last_eating = ft_time();
	philo->start_time = ft_time();
	while (!philo->data->dead)
	{
		if (philo->data->dead || philo->stop || eatings_counter(philo))
			return (NULL);
		grab_forks_even(philo);
		if (philo->data->dead || philo->stop || eatings_counter(philo))
			return (NULL);
		eating(philo);
		if (philo->data->dead || philo->stop || eatings_counter(philo))
			return (NULL);
		sleeping(philo);
		if (philo->data->dead || philo->stop || eatings_counter(philo))
			return (NULL);
		thinking(philo);
		if (philo->data->dead || philo->stop || eatings_counter(philo))
			return (NULL);
	}
	return (NULL);
}

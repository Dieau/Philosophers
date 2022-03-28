/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:34:02 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/11 12:51:55 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Si le philo est "pair", il prend la fork à droite en premier
// Si il est "impair", il prend d'abord la fork de gauche
// Pour éviter un deadlock
void	grab_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->lock_print);
	if (philo->stop != 1)
	{
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->philo_id + 1);
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->philo_id + 1);
	}
	pthread_mutex_unlock(&philo->lock_print);
}

void	grab_forks_even(t_philo *philo)
{
	if ((philo->philo_id) % 2 == 0 && philo->philo_id + 1 != philo->nbr_philo)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->lock_print);
		if (philo->stop != 1)
		{
			printf("%ld %d has taken a fork\n", \
				ft_time() - philo->start_time, philo->philo_id + 1);
			printf("%ld %d has taken a fork\n", \
				ft_time() - philo->start_time, philo->philo_id + 1);
		}
		pthread_mutex_unlock(&philo->lock_print);
	}
	else
		grab_forks_odd(philo);
}

// Print msg et timestamp dans un lock mutex
// Actualise le dernier timer de repas
// Se met en pause sur une durée time_to_eat
void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is eating\n", \
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	philo->eatings_total += 1;
	philo->last_eating = ft_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// Print msg et timestamp dans un lock mutex
// Se met en pause sur une durée time_to_sleep
void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is sleeping\n", \
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	ft_usleep(philo->time_to_sleep);
}

// Print msg  et timestamp dans un lock mutex
void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is thinking\n", \
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
}

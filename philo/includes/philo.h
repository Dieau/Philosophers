/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:37:07 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/03 16:04:52 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "philo.h"

struct	s_data;

typedef struct s_philo
{
	int				philo_id;
	int				eatings_total;
	int				eatings_total_goal;
	time_t			last_eating;
	int				nbr_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	time_t			life_timer;
	int				stop;
	time_t			start_time;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nbr_philo;
	int				philo_id;
	time_t			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	int				nbr_of_eating;
	pthread_mutex_t	*forks;
	pthread_t		*tids;
	pthread_mutex_t	lock_print;
	t_philo			*all_philos;
}					t_data;

void		grab_forks_even(t_philo *philo);
void		grab_forks_odd(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
long		ft_time(void);
void		ft_usleep(int ms);
long long	ft_atol(const char *str);
int			ft_is_digit(char *str);
int			eatings_counter(t_philo *philo);
void		*surveillance(void *args);
void		*routine(void *args);
void		*init_philo(t_data *args);
void		*init_mutex(t_data *args);
void		*init_threads(t_data *args);
void		end_threads(t_data *args);
void		philo_generator(t_data *args, t_philo *philos, int i);
int			init_args(t_data *args, int argc, char **argv);
int			check_args(int argc, char **argv);
void		free_all(t_data *args);
void		destroy_mutex(t_data *args);
void		error_exit(char *msg);

#endif

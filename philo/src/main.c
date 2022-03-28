/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:34:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/03 16:39:50 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Vérification de la validité des arguments
int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		error_exit("ERROR: Please enter between 4 and 5 arguments\n");
		return (1);
	}
	while (argv[i])
	{
		if (!ft_is_digit(argv[i]) || !ft_atol(argv[i]))
		{
			error_exit("ERROR : Invalid arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	args;

	if (check_args(argc, argv))
		return (1);
	if (init_args(&args, argc, argv) == 1)
		return (1);
	init_mutex(&args);
	init_philo(&args);
	init_threads(&args);
	end_threads(&args);
	destroy_mutex(&args);
	free_all(&args);
	return (0);
}

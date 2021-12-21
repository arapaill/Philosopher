/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:57:51 by user42            #+#    #+#             */
/*   Updated: 2021/12/21 11:01:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

int		ft_error(char *msg)
{
	ft_putstr_fd(msg, 1);
	return (-1);
}

int	init_info(t_philo *philo, int argc, char **argv)
{
	if (argc != 6)
		return (ft_error("Error: not enought or too much arguments\n"));
	philo->info.nb_total = ft_atoi(argv[1]);
	if (!philo->info.nb_total)
		return (ft_error("Error: bad argument: nb_total\n"));
	philo->info.time_to_die = ft_atoi(argv[2]);
	if (!philo->info.time_to_die)
		return (ft_error("Error: bad argument: time_to_die\n"));
	philo->info.time_to_eat = ft_atoi(argv[3]);
	if (!philo->info.time_to_eat)
		return (ft_error("Error: bad argument: time_to_eat\n"));
	philo->info.time_to_sleep = ft_atoi(argv[4]);
	if (!philo->info.time_to_sleep)
		return (ft_error("Error: bad argument: time_to_sleep\n"));
	philo->info.must_eat = ft_atoi(argv[5]);
	if (!philo->info.must_eat)
		return (ft_error("Error: bad argument: must_eat\n"));
	return(0);
}

int	main(int argc, char **argv)
{
	t_philo  philo;

	if (init_info(&philo, argc, argv) == -1)
		return (-1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:58:39 by user42            #+#    #+#             */
/*   Updated: 2021/12/21 10:55:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# include "../srcs/libft/libft.h"

typedef struct s_info
{
	int         nb_total;
	int         time_to_die;
	int         time_to_eat;
	int         time_to_sleep;
	int         must_eat;
}				t_info;

typedef struct	s_philo
{
	t_info		info;
	int			nb_philo;
}				t_philo;

int				ft_error(char *msg);

# endif
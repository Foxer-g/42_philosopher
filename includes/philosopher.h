/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toespino <toespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 02:34:49 by toespino          #+#    #+#             */
/*   Updated: 2026/08/20 08:40:11 by toespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define P_EAT "is eating"
# define P_SLEEP "is sleeping"
# define P_FORK "has taken a fork"
# define P_THINK "is thinking"
# define P_DEATH "died"

typedef struct s_philo
{
	int32_t			id;

	bool			*l_fork;
	bool			*av_l_fork;

	bool			*r_fork;
	bool			*av_r_fork;

	bool			*death_con;

	uintmax_t		start_time;
	int32_t			sleep_time;
	int32_t			eat_time;

	int32_t			*start_eat;
	int32_t			*last_eat;

	pthread_mutex_t	*l_fork_lock;
	pthread_mutex_t	*av_l_fork_lock;

	pthread_mutex_t	*r_fork_lock;
	pthread_mutex_t	*av_r_fork_lock;

	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*stdout_lock;

	pthread_mutex_t	*start_eat_lock;
	pthread_mutex_t	*last_eat_lock;
}	t_philo;

void		philo(t_philo *info);

void		p_l_lock_fork(t_philo *philo, bool status);
void		p_r_lock_fork(t_philo *philo, bool status);
void		*get_info(pthread_mutex_t *lock, void *info);

void		p_printf(uintmax_t time, char *act, t_philo *philo);
uintmax_t	getmsofday(void);
#endif

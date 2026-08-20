/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toespino <toespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 03:10:59 by toespino          #+#    #+#             */
/*   Updated: 2026/08/20 08:42:13 by toespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	p_printf(uintmax_t time, char *act, t_philo *philo)
{
	pthread_mutex_lock(philo->stdout_lock);
	printf("[%ju]  %i : %s\n", time, philo->id, act);
	pthread_mutex_unlock(philo->stdout_lock);
}

uintmax_t	getmsofday(void)
{
	struct timeval	ts;

	gettimeofday(&ts, NULL);
	return (ts.tv_sec * 1000 + ts.tv_usec / 1000);
}

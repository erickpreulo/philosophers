/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomes <egomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:11:20 by egomes            #+#    #+#             */
/*   Updated: 2021/11/09 15:59:34 by egomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_obj		obj;

	if (!init_philo(&obj, ac, av))
		return (0);
	obj.philo = malloc(sizeof(t_philo) * obj.arg.philos);
	if (!obj.philo)
		return (error("Malloc"));
	init_mutex(&obj);
	init_philos(&obj);
	init_function(&obj);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 07:18:17 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/01 07:18:19 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(int argc, const char **argv)
{
	const char	*argument;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: philo number_of_philosophers "
				"time_to_die time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	while (argc > 1)
	{
		argument = argv[argc - 1];
		while (*argument > '0' && *argument < '9')
			argument++;
		if (*argument)
		{
			printf("Bad input: %s is not a number.\n", argument);
			return (1);
		}
		argc--;
	}
	return (0);
}

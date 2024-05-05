/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 07:44:36 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/01 07:44:38 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(unsigned int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	while ((*s1 || *s2) && n > 0)
	{
		if ((unsigned const char)*s1 != (unsigned const char)*s2)
			return ((unsigned const char)*s1 - (unsigned const char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	is_negative;
	int	result;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (ft_strncmp((char *)nptr, "2147483648", 10) == 0)
		return (INT_MIN);
	is_negative = 0;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			is_negative = 1;
		nptr++;
	}
	result = 0;
	while (ft_isdigit(*nptr))
	{
		result *= 10;
		result += (*(nptr++) - '0');
	}
	return (result * (1 + (is_negative * -2)));
}

int	free_memory(t_locks *mutexes, pthread_t *threads, t_data *data)
{
	if (threads)
		free(threads);
	if (data)
		free(data);
	if (mutexes)
	{
		free(mutexes->thread_mutexes);
		free(mutexes->mealtime_mutexes);
		free(mutexes);
	}
	return (EXIT_FAILURE);
}
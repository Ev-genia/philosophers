/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:56:39 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/28 17:37:54 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_isspace(char c)
int	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'\
		|| c == ' ');
}

// int	ft_atoi(const char *str)
// {
// 	int			minus;
// 	long int	nbr;
// 	int			i;

// 	while (*str && ft_isspace(*str))
// 		str++;
// 	minus = 1;
// 	// if (*str == '-')
// 	// 	minus = -1;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			minus *= -1;
// 		str++;
// 	}
// 	nbr = 0;
// 	i = 0;
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		nbr = nbr * 10 + (*str - '0');
// 		i++;
// 		if (i > 18 && nbr < 0 && minus == 1)
// 			return (-1);
// 		if (nbr > 19 && nbr > 0 && minus == -1)
// 			return (0);
// 		str++;
// 	}
// 	return (nbr * minus);
// }

long long int  ft_atoi(const char *str)
{
  int          sign;
  unsigned long int  number;

  sign = 1;
  number = 0;
  while (is_space(*str))
    str++;
  if (*str == '-')
    sign = -1;
  if (*str == '-' || *str == '+')
    str++;
  while (*str >= '0' && *str <= '9')
  {
    number = number * 10 + (*str - '0');
    if (number > 9223372036854775807 && sign == 1)
      return (-1);
    if (number > 9223372036854775807 && sign == -1)
      return (0);
    str++;
  }
  return (number * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:07:02 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/04 11:12:26 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
*	Takes in a char *str and an index int i.
*	While str[i] == Space, i is increased.
*	Returns position of next non-space character in string.
*	If str == NULL, returns -1.
*/
int	ft_skip_space(char *str, int i)
{
	if (str)
	{
		while (ft_is_space(str[i]) == 1)
			i++;
		return (i);
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:11:32 by ametapod          #+#    #+#             */
/*   Updated: 2020/09/29 16:47:38 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int				check_args(int argc, char **argv)
{
	char	*point;

	if (argc < 2 || argc > 3)
		return (0);
	if (!(point = ft_strrchr(argv[1], '.')))
		return (0);
	if (ft_strncmp(point, ".cub", 5))
		return (0);
	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 7))
			return (0);
	return (1);
}

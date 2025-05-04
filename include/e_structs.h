/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_structs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:53:26 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 07:48:12 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_STRUCTS_H

# define E_STRUCTS_H

# include "structs.h"

typedef struct s_tempfile
{
	char	*pathname;
	int		fd;
}			t_tempfile;

#endif

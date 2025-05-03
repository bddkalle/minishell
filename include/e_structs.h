/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_structs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:53:26 by cdahne            #+#    #+#             */
/*   Updated: 2025/04/30 18:03:51 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_STRUCTS_H

# define E_STRUCTS_H

# include "structs.h"

typedef struct s_tempfile
{
	char	*name;
	int		fd;
}			t_tempfile;

#endif

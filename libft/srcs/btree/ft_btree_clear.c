/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:02:40 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/26 13:17:08 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_btree_clear(t_btree *root, void (*item_free)(void *))
{
	if (!root)
		return ;
	if (root->left)
		ft_btree_clear(root->left, item_free);
	if (root->right)
		ft_btree_clear(root->right, item_free);
	if (item_free != NULL)
		(*item_free)(root->item);
	free(root);
}

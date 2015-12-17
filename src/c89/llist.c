/*
 *      This file is part of the SmokeOS project.
 *  Copyright (C) 2015  <Fabien Bavent>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   - - - - - - - - - - - - - - -
 */
#include <skc/llist.h>


/** Push an element at the front of a linked-list */
void ll_push_front(llhead_t *list, llnode_t *node)
{
  assert (node->prev_ == NULL);
  assert (node->next_ == NULL);
  node->next_ = list->first_;

  if (list->first_ != NULL)
    list->first_->prev_ = node;
  else
    list->last_ = node;

  node->prev_ = NULL;
  list->first_ = node;
  ++list->count_;
}

/** Push an element at the end of a linked-list */
void ll_push_back(llhead_t *list, llnode_t *node)
{
  assert (node->prev_ == NULL);
  assert (node->next_ == NULL);
  node->prev_ = list->last_;

  if (list->last_ != NULL)
    list->last_->next_ = node;
  else
    list->first_ = node;

  node->next_ = NULL;
  list->last_ = node;
  ++list->count_;
}

/** Pop an element from the front of the linked-list */
llnode_t* ll_pop_front(llhead_t *list)
{
  struct llnode *first = list->first_;

  if (first == 0)
    return NULL;

  assert (first->prev_ == NULL);

  if (first->next_) {
    first->next_->prev_ = NULL;
  } else {
    assert (list->last_ == first);
    list->last_ = NULL;
  }

  list->first_ = first->next_;
  first->prev_ = NULL;
  first->next_ = NULL;
  --list->count_;
  return first;
}

/** Pop an element from the end of the linked-list */
llnode_t* ll_pop_back(llhead_t *list)
{
  struct llnode *last = list->last_;

  if (last == 0)
    return NULL;

  assert (last->next_ == NULL);

  if (last->prev_) {
    last->prev_->next_ = NULL;
  } else {
    assert (list->first_ == last);
    list->first_ = NULL;
  }

  list->last_ = last->prev_;
  last->prev_ = NULL;
  last->next_ = NULL;
  --list->count_;

  return last;
}

/** Remove an item on the linked-list. */
void ll_remove(llhead_t *list, llnode_t *node)
{
  assert (ll_onthelist(list, node));
  if (node->prev_) {
    node->prev_->next_ = node->next_;
  } else {
    assert (list->first_ == node);
    list->first_ = node->next_;
  }

  if (node->next_) {
    node->next_->prev_ = node->prev_;
  } else {
    assert (list->last_ == node);
    list->last_ = node->prev_;
  }

  node->prev_ = NULL;
  node->next_ = NULL;
  --list->count_;
}

/** Check if the node is include on the list. */
int ll_onthelist(llhead_t *list, llnode_t *node)
{
  struct llnode *w = node;
  while (w->prev_) {
    assert (w->prev_->next_ == w);
    w = w->prev_;
  }

  return w == list->first_;
}


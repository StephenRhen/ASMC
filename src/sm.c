/*
   sm.c - code to manipulate the internal state machine data structures.

   Copyright (C) 2019 Stephen Rhen
 
   This file is part of asmc, A State Machine Compiler.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "asmc.h"

/* State machine data */
state_machine_t sm;

void add_hdr_code(const char *code)
{
    sm.hdr_code = code;
}

void add_class_decl_code(const char *code)
{
    sm.class_decl_code = code;
}

/* Sets the start state */
void set_start_state(const char *name)
{
  state_t *state;

  if (state = state_lookup(name))
    sm.start_state = state;
  else
    yyerror("Only one %start option allowed\n");
  
}

/* Find an event by name returning NULL if the event isn't found */
event_t *event_find(const char *name)
{
  event_t *event;
  for (event = sm.event_table; event; event = event->next) {
    if (strcmp(event->name, name) == 0)
      break;
  }
  return event;
}

/* Like event_find(), but prints an error message if the event
 * isn't found */
event_t *event_lookup(const char *name)
{
  event_t *event = event_find(name);
  if (!event) {
    yyerror("Undefind event %s\n", name);
  }
  return event;
}

/* Add an event to the event table */
void event_add(const char *name)
{
  event_t *event, **prev;
  
  /* Check for duplicates */
  if (event_find(name) != NULL) {
    yyerror("Duplicate event %s\n", name);
  }
  else {
    trace("Adding event %s", name);
    event = malloc(sizeof(event_t));
    event->name = strdup(name);
    for (prev = &sm.event_table; *prev; prev = &(*prev)->next);
    (*prev) = event;
  }
}

/* Find an state by name returning NULL if the event isn't found */
state_t *state_find(const char *name)
{
  state_t *state;
  for (state = sm.state_table; state; state = state->next) {
    if (strcmp(state->name, name) == 0)
      break;
  }
  return state;
}

/* Like state_find(), but prints an erro message if the state isn't
 * found */
state_t *state_lookup(const char *name)
{
  state_t *state = state_find(name);
  if (!state) {
    yyerror("Undefind state %s\n", name);
  }
  return state;
}

/* Add an state to the state table */
void state_add(const char *name)
{
  state_t *state, **prev;
  
  /* Check for duplicates */
  if (state_find(name) != NULL) {
    yyerror("Duplicate state %s", name);
  }
  else {
    trace("Adding state %s", name);
    state = malloc(sizeof(state_t));
    state->name = strdup(name);
    for (prev = &sm.state_table; *prev; prev = &(*prev)->next);
    *prev = state;
  }
}

/* Add a transition */
void trans_add(transition_t *list, transition_t *trans)
{
  if (!list) {
    list = trans;
  }
  else {
    while(list->next)
      list = list->next;

    if ((list->event == trans->event) && !list->guard) {
      yyerror("Transition for event %s not reached\n");
      free(trans);
    }
    else {
      list->next = trans;
    }
  }
} 

/* Create a transition */
transition_t *trans_create(event_t *event,
			  const char *guard,
			  state_t *state,
			  const char *code)
{
  transition_t *trans, **prev;
  char *state_name = NULL;

  trans = malloc(sizeof(transition_t));
  trans->event = event;
  trans->guard = guard;
  trans->next_state = state;
  trans->code = code;

  if (state)
    state_name = state->name;
  
  trace("Adding transition for event %s, guard %s\n next state %s code:%s",
	event->name, guard, state_name, code);

  return trans;
}


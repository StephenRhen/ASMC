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

/* Sets the start state */
void set_start_state(char *name)
{
  state_t *state;

  if (state = state_lookup(name)) {
    sm.start_state = state;
  }
}

/* Find an event by name returning NULL if the event isn't found */
event_t *event_find(char *name)
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
event_t *event_lookup(char *name)
{
  event_t *event = event_find(name);
  if (!event) {
    yyerror("Undefind event %s\n", name);
  }
  return event;
}

/* Add an event to the event table */
void event_add(char *name)
{
  event_t *event;
  
  /* Check for duplicates */
  if (event_find(name) != NULL) {
    yyerror("Duplicate event %s\n", name);
  }
  else {
    trace("Adding event %s", name);
    event = malloc(sizeof(event_t));
    event->name = strdup(name);
    event->next = sm.event_table;
    sm.event_table = event;
  }
}

/* Find an state by name returning NULL if the event isn't found */
state_t *state_find(char *name)
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
state_t *state_lookup(char *name)
{
  state_t *state = state_find(name);
  if (!state) {
    yyerror("Undefind state %s\n", name);
  }
  return state;
}

/* Add an state to the state table */
void state_add(char *name)
{
  state_t *state;
  
  /* Check for duplicates */
  if (state_find(name) != NULL) {
    yyerror("Duplicate state %s", name);
  }
  else {
    trace("Adding state %s", name);
    state = malloc(sizeof(state_t));
    state->name = strdup(name);
    state->next = sm.state_table;
    sm.state_table = state;
  }
}

/* Link a transition onto the list */
transition_t *trans_add(transition_t *list, transition_t *trans)
{
  trans->next = list;
  return trans;
}

/* Create a transition */
transition_t *trans_create(event_t *event, state_t *state, char *code)
{
  transition_t *trans = malloc(sizeof(transition_t));
  char *state_name = NULL;
  trans->event = event;
  trans->next_state = state;
  if (code) {
    trans->code = strdup(code);
  }
  if (state) {
    state_name = state->name;
  }
  trace("Creating transition event %s, next state %s \n    code:%s",
	event->name, state_name, code);
  return trans;
}

void add_first_code(const char *code)
{
  sm.first_code = strdup(code);
}



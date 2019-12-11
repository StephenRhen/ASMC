/*
   asmc.h

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

#ifndef _ASMC_H_
#define _ASMC_H_

void yyerror(const char *s,...);

void trace(const char*format,...);

typedef struct event {
  char *name;
  struct event *next;
} event_t;

typedef struct state {
  char *name;
  char *entry;
  char *exit;
  struct transition  *trans_list;
  struct state *next;
} state_t;

typedef struct transition {
  event_t *event;
  const char *guard;
  state_t *next_state;
  const char *code;
  struct transition *next;
} transition_t;

typedef struct state_machine
{
  char *infile_name;       /* Name of file contating the state machine
                            * description as given on the command line. */
  char *infile_basename;   /* Input file name with path removed. */
  char *class_name;        /* Name of the generated state machine class.
                            * defaults to the input file base name with
                            * any '.'s replaced by underscors.
                            */
  FILE *tracefile;         /* File for outputing parser trace messages, 
                            * set with the "-tf" command line switch. */
  event_t *event_table;    /* List of events. */
  state_t *state_table;    /* List of states */
  state_t *start_state;    /* Initial state for the state machine. */

  const char *hdr_code;    /* Literal code to be included in the class header file
                            * prior to the generated code. Used to specify any 
			    * include files required by the class */
  const char *class_decl_code;   /* Code that is inserted as private members of the
                            * state machine class. Used to add state variables
			    * and member functions to the class. */
} state_machine_t;

/* Add header code */
void add_hdr_code(const char *code);

/* Add private members to the class */
void add_class_decl_code(const char *code);

/* Sets the start state */
void set_start_state(const char *name);
  
/* Find an event by name returning NULL if the event isn't found */
event_t *event_find(const char *name);

/* Like event_find(), but prints an error message if the event
 * isn't found */
event_t *event_lookup(const char *name);

/* Add an event to the event table */
void event_add(const char *name);

/* Find an state by name returning NULL if the state isn't found */
state_t *state_find(const char *name);

/* Like state_find(), but prints an erro message if the state isn't
 * found */
state_t *state_lookup(const char *name);

/* Add an state to the state table */
void state_add(const char *name);

/* Add a transition */
void trans_add(transition_t *list, transition_t *trans);

/* Create a transition */
transition_t *trans_create(event_t *event,
			 const char *guard,
			 state_t *state,
			 const char *code);

/* Generate c++ code */
void gen_cpp(state_machine_t *sm);

#endif /* _ASMC_H_ */

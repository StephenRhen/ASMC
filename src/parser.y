/*
   asmc.y - parses the state machine description file

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

%{
  
#include <stdio.h>
#include <string.h>
  
#include "asmc.h"
  
int yylex();
 
%}

%union {
  char *string;
  struct state *state;
  struct event *event;
  struct transition *trans;
}

%token EVENT STATE START NIL PUSH POP
%token <string> ID ENTRY EXIT CODE_BLOCK GUARD
%token DCOLON DPERCENT

%type <state> state_ref state_ref_or_nil
%type <event> event_ref
%type <trans> trans trans_list trans_list_or_nil
%type <string> entry exit raw_code guard

%%

fms:  header DPERCENT rules ;

header: %empty
| hdr_code option_list class_decl_code
;

hdr_code: raw_code { add_hdr_code($1); } ;

class_decl_code: raw_code { add_class_decl_code($1); } ;

option_list: option | option_list option ;

option:   EVENT event_list
        | STATE state_list
        | START ID { set_start_state($2); }
;

event_list:  event_decl | event_list event_decl ;

state_list: state_decl | state_list state_decl ;

rules: state_def_list ;

state_def_list: state_def | state_def_list state_def ;

state_def: state_ref entry exit '{' trans_list_or_nil '}'
  {
    $1->entry = $2;
    $1->exit = $3;
    $1->trans_list = $5;
  }
;

entry: %empty { $$ = NULL; }
  | ENTRY CODE_BLOCK { $$ = strdup($2); }
;

exit: %empty { $$ = NULL; }
  | EXIT CODE_BLOCK { $$ = strdup($2); }
;

trans_list_or_nil: %empty { $$ = NULL; }
| trans_list { $$ = $1; }
;

trans_list: trans { $$ = $1; }
| trans_list trans { trans_add($1, $2); $$ = $1; }
;

trans: event_ref guard state_ref_or_nil raw_code ';'
{
  $$ = trans_create($1, $2, $3, $4);
}
;

guard:   %empty  { $$ = NULL; }
| GUARD { $$ = strdup($1); }
;

raw_code: %empty { $$ = NULL; }
| CODE_BLOCK { $$ = strdup($1); } ;

state_decl: ID { state_add($1); } ;

state_ref: ID { $$ = state_lookup($1); } ;

state_ref_or_nil: %empty { $$ = NULL; } | state_ref { $$ = $1; } ;

event_decl: ID { event_add($1); } ;

event_ref: ID { $$ = event_lookup($1); } ;

%%


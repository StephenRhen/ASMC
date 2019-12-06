/*
   asmc.c

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

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "asmc.h"

extern state_machine_t sm;

/* Interface to the parser. */
extern int yylineno;
extern FILE *yyin;
extern int yyparse();


static int error_cnt;

int main(int argc, char **argv)
{
  int opt;
  char *cp;

  while ((opt = getopt(argc, argv, "t::")) != -1) {
    switch (opt) {

      /* Output parser trace to a file. */
    case 't':
      if (optarg) {
	if (!(sm.tracefile = fopen(optarg, "w"))) {
	  fprintf(stderr, "Couldn't create trace file \"%s\"\n", optarg);
	  exit(EXIT_FAILURE);
	}
      }
      else {
	sm.tracefile = stdout;
      }
      break;
    }
  } /* while() */

  if (optind >= argc) {
    fprintf(stderr, "No input file given\n");
    exit(EXIT_FAILURE);
  }

  if (!(yyin = fopen(argv[optind], "r"))) {
    fprintf(stderr, "Couldnt open input file %s\n", argv[optind]);
    exit(EXIT_FAILURE);
  }

  sm.infile_name = strdup(argv[optind]);

  cp = strdup(sm.infile_name);
  sm.infile_basename = strdup(basename(cp));
  free(cp);

  sm.class_name = strdup(sm.infile_basename);
  if (cp = strchr(sm.class_name, '.')) {
    *cp = '\0';
  }

  if (yyparse() || error_cnt) {
    fprintf(stderr, "Error parsing input file %s\n", sm.infile_name);
  }

  gen_cpp(&sm);

  exit(EXIT_SUCCESS);
  
}

/* Prints an error message. */
void yyerror(const char *format,...)
{
  va_list args;
  va_start(args, format);  
  error_cnt++;
  fprintf(stderr, "Error %s at line %d: ", sm.infile_basename, yylineno);
  vfprintf(stderr, format, args);
  fputc('\n', stderr);
  va_end(args);
}

void trace(const char *format,...)
{
  va_list args;
  va_start(args, format);

  if (sm.tracefile) {
    fprintf(sm.tracefile, "Trace %s at line %d: ", sm.infile_basename, yylineno);
    vfprintf(sm.tracefile, format, args);
    fputc('\n', sm.tracefile);
  }

  va_end(args);

}


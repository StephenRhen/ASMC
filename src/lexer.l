/*
   asmc.l - lexical analyzer for state machine description files. 

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

#include "parser.tab.h"

%}

%option yylineno

%x code
%x guard

%%

    /* FIX ME: need to check for buffer overruns */
    char code_buf[1024];
    char *code_ptr;


    /* remove white space */
[ \t\n]

    /* Strip comments */
\/\*([^*]|\*+[^/])*\*+\/
\/\/.*$

    /* Return raw code sections verbatim */
"%{"             {
                   code_ptr = code_buf;
                   BEGIN(code);
                 }
<code>\n         { *code_ptr++ = '\n'; }
<code>.          { *code_ptr++ = yytext[0]; }

<code>"%}"       {
                   *code_ptr = '\0'; 
                   BEGIN(INITIAL);
                   yylval.string = code_buf;
                   return CODE_BLOCK;
                 }

    /* Return Conditional expressions verbatim */
\[               { 
                   code_ptr = code_buf;
                   BEGIN(guard);
                 }
<guard>\]        { 
                   *code_ptr = '\0';
                   BEGIN(INITIAL);
                   yylval.string = code_buf;
                   return GUARD;
                 }
<guard>\n        { *code_ptr++ = '\n'; }
<guard>.         { *code_ptr++ = yytext[0]; }


    /* Keywords */
%class            return CLASS;
%entry            return ENTRY;
%event            return EVENT;
%exit             return EXIT;
%start            return START;
%state            return STATE;


Default          printf("<default>");
nil              return NIL;
push             return PUSH;
pop              return POP;

     /* Identifiers */
[a-zA-Z][a-zA-Z0-9_]*  { yylval.string = yytext; return ID; } 

     /* Multi character punctuation */
::               return DCOLON;
\%\%             return DPERCENT;

.                return yytext[0];

%%

int yywrap()
{

}

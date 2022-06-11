%option noyywrap
%{
/*
 * We now build a lexical analyzer to be used by a higher-level parser.
 */

#include "lex.h"    /* token codes from the parser */


%}

%%



" "				{ continue;}
'\0'			{ return EOI; }
with			{ return KW_WITH; }
[a-zA-Z]+		{ return IDENT;}
[0-9]+			{ return NUMBER;}
"+"				{ return PLUS; }
"-"				{ return MINUS; }
"*"				{ return STAR; }
"/"				{ return SLASH; }
"("				{ return L_PAREN; }
")"				{ return R_PAREN; }
":"				{ return COLON; }
","				{ return COMMA; }
.				{ return UNKONWN; }


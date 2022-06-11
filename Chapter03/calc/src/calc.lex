%option noyywrap
%{
/*
 * We now build a lexical analyzer to be used by a higher-level parser.
 */

#include "lex.h"    /* token codes from the parser */

void adjust(void)
{
yylval.sval=yytext;
}

%}

%%



" "				{ continue;}
'\0'			{ return EOI; }
with			{ adjust(); return KW_WITH; }
[a-zA-Z]+		{ adjust(); return IDENT;}
[0-9]+			{ adjust(); return NUMBER;}
"+"				{ adjust(); return PLUS; }
"-"				{ adjust(); return MINUS; }
"*"				{ adjust(); return STAR; }
"/"				{ adjust(); return SLASH; }
"("				{ adjust(); return L_PAREN; }
")"				{ adjust(); return R_PAREN; }
":"				{ adjust(); return COLON; }
","				{ adjust(); return COMMA; }
.				{ adjust(); return UNKONWN; }


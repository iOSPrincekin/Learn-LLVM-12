//
//  main.m
//  lex
//
//  Created by LEE on 6/11/22.
//
#include <stdio.h>
#include "lex.h"
int yylex(void);
typedef struct yy_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE yy_scan_string (const char * yystr );
void yy_switch_to_buffer  (YY_BUFFER_STATE  new_buffer );
void yy_delete_buffer (YY_BUFFER_STATE  b );
int main()
{
    int tok;
    YY_BUFFER_STATE bp = yy_scan_string("with a, b: a * (4 + b)");  // Creates a buffer from the string
    yy_switch_to_buffer(bp);                   // Use the buffer
    for(;;) {
        tok=yylex();
        printf("tok--::%d\n",tok);
        if (tok==0) break;
        switch(tok) {
            case KW_WITH:
                printf("KW_WITH\n");
                break;
            case IDENT:
                printf("IDENT\n");
                break;
            case NUMBER:
                printf("NUMBER\n");
                break;
            case PLUS:
                printf("PLUS\n");
                break;
            case MINUS:
                printf("MINUS\n");
                break;
            case STAR:
                printf("STAR\n");
                break;
            case SLASH:
                printf("SLASH\n");
                break;
            case L_PAREN:
                printf("L_PAREN\n");
                break;
            case R_PAREN:
                printf("R_PAREN\n");
                break;
            case COLON:
                printf("COLON\n");
                break;
            case COMMA:
                printf("COMMA\n");
                break;
            case UNKONWN:
                printf("UNKONWN\n");
                break;
            default:
                break;
        }
    }
    yy_delete_buffer(bp);  
    return 0;
}

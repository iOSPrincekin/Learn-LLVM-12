#include "Lexer.h"
#include "lex.h"
#define USE_YYLEX

#ifndef USE_YYLEX

namespace charinfo {
LLVM_READNONE inline bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v' ||
    c == '\r' || c == '\n';
}

LLVM_READNONE inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

LLVM_READNONE inline bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
}

void Lexer::next(Token &token) {
    while (*BufferPtr && charinfo::isWhitespace(*BufferPtr)) {
        ++BufferPtr;
    }
    if (!*BufferPtr) {
        token.Kind = Token::eoi;
        return;
    }
    if (charinfo::isLetter(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while (charinfo::isLetter(*end))
            ++end;
        llvm::StringRef Name(BufferPtr, end - BufferPtr);
        Token::TokenKind kind =
        Name == "with" ? Token::KW_with : Token::ident;
        formToken(token, end, kind);
        return;
    } else if (charinfo::isDigit(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while (charinfo::isDigit(*end))
            ++end;
        formToken(token, end, Token::number);
        return;
    } else {
        switch (*BufferPtr) {
                
#define CASE(ch, tok) \
case ch: formToken(token, BufferPtr + 1, tok); break
                CASE('+', Token::plus);
                CASE('-', Token::minus);
                CASE('*', Token::star);
                CASE('/', Token::slash);
                CASE('(', Token::Token::l_paren);
                CASE(')', Token::Token::r_paren);
                CASE(':', Token::Token::colon);
                CASE(',', Token::Token::comma);
#undef CASE
            default:
                formToken(token, BufferPtr + 1, Token::unknown);
        }
        return;
    }
}

#else

extern "C" {
int yylex(void);
}

void Lexer::next(Token &token) {
    int tok;
    tok=yylex();
    printf("tok--::%d\n",tok);
    Token::TokenKind kind;
    switch(tok) {
        case 0:
        case EIO:
            token.Kind = Token::eoi;
            break;
        case KW_WITH:
            printf("KW_WITH::%s\n",yylval.sval);
            kind = Token::KW_with;
            formTokenStr(token, yylval.sval, kind);
            break;
        case IDENT:
            printf("IDENT::%s\n",yylval.sval);
            kind = Token::ident;
            formTokenStr(token, yylval.sval, kind);
            break;
        case NUMBER:
            printf("NUMBER::%d,%s\n",yylval.ival,yylval.sval);
            kind = Token::number;
            formTokenStr(token, yylval.sval, kind);
            break;
        case PLUS:
            printf("PLUS\n");
            kind = Token::plus;
        case MINUS:
            printf("MINUS\n");
            kind = Token::minus;
        case STAR:
            printf("STAR\n");
            kind = Token::star;
        case SLASH:
            printf("SLASH\n");
            kind = Token::slash;
        case L_PAREN:
            printf("L_PAREN\n");
            kind = Token::l_paren;
        case R_PAREN:
            printf("R_PAREN\n");
            kind = Token::r_paren;
        case COLON:
            printf("COLON\n");
            kind = Token::colon;
        case COMMA:
            printf("COMMA\n");
            kind = Token::comma;
        case UNKONWN:
            printf("UNKONWN\n");
            kind = Token::unknown;
            formTokenStr(token, yylval.sval, kind);
        default:
            break;
    }
}

void Lexer::formTokenStr(Token &Tok, const char *TokStr,
                      Token::TokenKind Kind) {
    Tok.Kind = Kind;
    Tok.Text = llvm::StringRef(TokStr);
}

#endif

void Lexer::formToken(Token &Tok, const char *TokEnd,
                      Token::TokenKind Kind) {
    Tok.Kind = Kind;
    Tok.Text = llvm::StringRef(BufferPtr, TokEnd - BufferPtr);
    BufferPtr = TokEnd;
}

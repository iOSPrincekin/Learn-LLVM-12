#ifndef LEXER_H
#define LEXER_H

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"

extern "C" {
typedef struct yy_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE yy_scan_string (const char * yystr );
void yy_switch_to_buffer  (YY_BUFFER_STATE  new_buffer );
void yy_delete_buffer (YY_BUFFER_STATE  b );
}

class Lexer;

class Token {
    friend class Lexer;
    
public:
    enum TokenKind : unsigned short {
        eoi,
        unknown,
        ident,
        number,
        comma,
        colon,
        plus,
        minus,
        star,
        slash,
        l_paren,
        r_paren,
        KW_with
    };
    
private:
    TokenKind Kind;
    llvm::StringRef Text;
    
public:
    TokenKind getKind() const { return Kind; }
    llvm::StringRef getText() const {
        return Text;
    }
    
    bool is(TokenKind K) const { return Kind == K; }
    bool isOneOf(TokenKind K1, TokenKind K2) const {
        return is(K1) || is(K2);
    }
    template <typename... Ts>
    bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const {
        return is(K1) || isOneOf(K2, Ks...);
    }
};

class Lexer {
    const char *BufferStart;
    const char *BufferPtr;
    YY_BUFFER_STATE bp;
public:
    Lexer(const llvm::StringRef &Buffer) {
        
        BufferStart = Buffer.begin();
        BufferPtr = BufferStart;
        
#define USE_YYLEX                        
#ifdef USE_YYLEX
        bp = yy_scan_string(BufferPtr);  // Creates a buffer from the string
        yy_switch_to_buffer(bp);                   // Use the buffer
        
#endif
    }
    
    void next(Token &token);
    ~Lexer()
    {
#ifdef USE_YYLEX
        yy_delete_buffer(bp);  
#endif
    }
    
private:
    void formToken(Token &Result, const char *TokEnd,
                   Token::TokenKind Kind);
    void formTokenStr(Token &Tok, const char *TokStr,
                             Token::TokenKind Kind);
};
#endif

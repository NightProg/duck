#ifndef DUCK_LANG_TOKEN_H
#define DUCK_LANG_TOKEN_H

#include <string>

namespace duck::lang {

    typedef enum {
        // Single-character tokens
        TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN, TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
        TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS, TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,

        // One or two character tokens
        TOKEN_BANG, TOKEN_BANG_EQUAL,
        TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
        TOKEN_GREATER, TOKEN_GREATER_EQUAL,
        TOKEN_LESS, TOKEN_LESS_EQUAL,

        // Literals
        TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,

        // Keywords
        TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE, TOKEN_FUN, TOKEN_FOR, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
        TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS, TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE,

        // End of file
        TOKEN_END_OF_FILE
    } TokenKind;

    class Token {
    public:
        Token(std::string lexeme, TokenKind type, int line, int column);
        Token(TokenKind kind) : Token("", kind, 0, 0) {}
        ~Token() = default;

        [[nodiscard]] std::string getLexeme() const;
        TokenKind getType() const;
        int getLine() const;
        int getColumn() const;

        bool operator== (const Token &rhs) const {
            return m_type == rhs.m_type;
        }

        [[nodiscard]] bool isExactSameType(const Token &rhs) const {
            return m_type == rhs.m_type && m_lexeme == rhs.m_lexeme && m_line == rhs.m_line && m_column == rhs.m_column;
        }

    private:
        std::string m_lexeme;
        TokenKind m_type;
        int m_line;
        int m_column;
    };
}


#endif
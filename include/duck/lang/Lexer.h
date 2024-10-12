//
// Created by antoine barbier on 08/10/2024.
//

#ifndef DUCK_LEXER_H
#define DUCK_LEXER_H

#include <string>
#include <vector>
#include <duck/lang/Token.h>
#include <duck/lang/Error.h>

namespace duck::lang {
    class Lexer {
    public:
        Lexer(std::string source);
        ~Lexer() = default;

        void scanTokens();
        bool isAtEnd() const;
        void scanToken();
        char advance();
        void addToken(TokenKind type);
        bool match(char expected);
        char peek();
        char peekNext();
        void number();
        void identifier();
        void error(std::string message);

        [[nodiscard]] std::vector<Token> getTokens() const;


        

    private:
        std::string m_source;
        std::string::iterator m_current;
        std::string::iterator m_start;
        std::vector<Token> m_tokens;
        std::vector<Error> m_errors;
        int m_line;
        int m_column;
    };

} // lang
// duck

#endif //DUCK_LEXER_H

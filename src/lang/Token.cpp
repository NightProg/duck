#include <duck/lang/Token.h>

namespace duck {
    namespace lang {
        Token::Token(std::string lexeme, TokenKind type, int line, int column) {
            m_lexeme = lexeme;
            m_type = type;
            m_line = line;
            m_column = column;
        }

        std::string Token::getLexeme() const {
            return m_lexeme;
        }

        TokenKind Token::getType() const {
            return m_type;
        }
    } // lang
} // duck
//
// Created by antoine barbier on 08/10/2024.
//

#include <duck/lang/Lexer.h>
#include <cctype>


namespace duck::lang {

    Lexer::Lexer(std::string source) : m_source(std::move(source)), m_current(m_source.begin()), m_start(m_source.begin()), m_line(1), m_column(0) {}

    void Lexer::scanTokens() {
        while (!isAtEnd()) {
            // We are at the beginning of the next lexeme.
            m_start = m_current;
            scanToken();
        }
    }

    bool Lexer::isAtEnd() const {
        return m_current == m_source.end();
    }

    void Lexer::scanToken() {
        char c = advance();
        switch (c) {
            case '(': addToken(TOKEN_LEFT_PAREN); break;
            case ')': addToken(TOKEN_RIGHT_PAREN); break;
            case '{': addToken(TOKEN_LEFT_BRACE); break;
            case '}': addToken(TOKEN_RIGHT_BRACE); break;
            case ',': addToken(TOKEN_COMMA); break;
            case '.': addToken(TOKEN_DOT); break;
            case '-': addToken(TOKEN_MINUS); break;
            case '+': addToken(TOKEN_PLUS); break;
            case ';': addToken(TOKEN_SEMICOLON); break;
            case '*': addToken(TOKEN_STAR); break;
            case '!': addToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG); break;
            case '=': addToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL); break;
            case '<': addToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS); break;
            case '>': addToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER); break;
            case '/':
                if (match('/')) {
                    // A comment goes until the end of the line.
                    while (peek() != '\n' && !isAtEnd()) advance();
                } else {
                    addToken(TOKEN_SLASH);
                }
                break;
            case ' ':
            case '\r':
            case '\t':
                // Ignore whitespace.
                break;
            case '\n':
                m_line++;
                m_column = 0;
                break;
            default:
                if (isdigit(c)) {
                    number();
                } else if (isalpha(c)) {
                    identifier();
                } else {
                    error("Unexpected character.");
                }
                break;
        }
    }

    char Lexer::advance() {
        m_column++;
        return *m_current++;
    }

    void Lexer::addToken(TokenKind type) {
        std::string text = std::string(m_start, m_current);
        m_tokens.emplace_back(text, type, m_line, m_column);
    }

    bool Lexer::match(char expected) {
        if (isAtEnd()) return false;
        if (*m_current != expected) return false;

        m_current++;
        return true;
    }

    char Lexer::peek() {
        if (isAtEnd()) return '\0';
        return *m_current;
    }

    char Lexer::peekNext() {
        if (m_current + 1 >= m_source.end()) return '\0';
        return m_current[1];
    }

    void Lexer::number() {
        while (isdigit(peek())) advance();

        // Look for a fractional part.
        if (peek() == '.' && isdigit(peekNext())) {
            // Consume the "."
            advance();

            while (isdigit(peek())) advance();
        }

        addToken(TOKEN_NUMBER);
    }

    void Lexer::identifier() {
        while (isalnum(peek())) advance();

        // See if the identifier is a reserved word.
        std::string text = std::string(m_start, m_current);
        TokenKind type = TOKEN_IDENTIFIER;
        if (text == "and") type = TOKEN_AND;
        else if (text == "class") type = TOKEN_CLASS;
        else if (text == "else") type = TOKEN_ELSE;
        else if (text == "false") type = TOKEN_FALSE;
        else if (text == "for") type = TOKEN_FOR;
        else if (text == "fun") type = TOKEN_FUN;
        else if (text == "if") type = TOKEN_IF;
        else if (text == "nil") type = TOKEN_NIL;
        else if (text == "or") type = TOKEN_OR;
        else if (text == "print") type = TOKEN_PRINT;
        else if (text == "return") type = TOKEN_RETURN;
        else if (text == "super") type = TOKEN_SUPER;
        else if (text == "this") type = TOKEN_THIS;
        else if (text == "true") type = TOKEN_TRUE;
        else if (text == "var") type = TOKEN_VAR;
        else if (text == "while") type = TOKEN_WHILE;

        addToken(type);
    }

    void Lexer::error(std::string message) {
        m_errors.emplace_back(std::move(message), m_line, m_column);
    }


} // lang

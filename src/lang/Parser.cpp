#include <duck/lang/Parser.h>

#include <utility>


    namespace duck::lang {
        Parser::Parser(Cursor<Token> cursor) : m_cursor(std::move(cursor)) {}
        Parser::Parser(std::vector<Token> tokens) : m_cursor(std::move(tokens)) {}

        AST *Parser::parseAST() {
            if (m_cursor.match(TOKEN_IF)) {
                return parseIf();
            } else if (m_cursor.match(TOKEN_WHILE)) {
                return parseWhile();
            } else if (m_cursor.match(TOKEN_FOR)) {
                return parseFor();
            } else if (m_cursor.match(TOKEN_LEFT_BRACE)) {
                return parseBlock();
            } else {
                return parseExpr();
            }

        }

        AST *Parser::parseIf() {
            ExprAST *condition = parseExpr();
            AST *thenBlock = parseAST();
            AST *elseBlock = nullptr;
            if (m_cursor.match(TOKEN_ELSE)) {
                elseBlock = parseAST();
            }
            return new IfAST(condition, thenBlock, elseBlock);
        }

        AST *Parser::parseWhile() {
            ExprAST *condition = parseExpr();
            AST *block = parseAST();
            return new WhileAST(condition, block);
        }

    }

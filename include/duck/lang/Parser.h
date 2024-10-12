#ifndef DUCK_PARSER_H
#define DUCK_PARSER_H

#include <duck/lang/AST.h>
#include <duck/lang/Token.h>
#include <duck/lang/Cursor.h>

namespace duck::lang {
    class Parser {
    public:
        Parser(Cursor<Token> cursor);
        Parser(std::vector<Token> tokens);
        ~Parser() = default;

        std::vector<AST> parse();

    private:
        ExprAST *parseExpr();
        ExprAST *parseBinOp();
        ExprAST *parseUnOp();
        ExprAST *parseLiteral();
        ExprAST *parseIdentifier();
        ExprAST *parseAssign();
        AST *parseAST();
        AST *parseIf();
        AST *parseWhile();
        AST *parseBlock();
        AST *parseFor();
        AST *parseFunction();

        Cursor<Token> m_cursor;
    };
}

#endif //DUCK_PARSER_H

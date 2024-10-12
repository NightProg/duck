#ifndef DUCK_AST_H
#define DUCK_AST_H

#include <iostream>
#include <vector>
#include <duck/lang/Token.h>
#include <duck/lang/Cursor.h>
#include <memory>

namespace duck {
    namespace lang {
        typedef enum {
            BinOp,
            UnOp,
            LiteralInt,
            LiteralFloat,
            Identifier,
            Assign,
            If,
            While,
            Block,
            For,
            Function,
        } ASTKind;

        class AST {
        public:
            AST() = default;
            ~AST() = default;

            virtual void print(std::ostream &os);
            virtual ASTKind getKind() const;
        };

        class ExprAST : public AST {
        public:
            ExprAST() = default;
            ~ExprAST() = default;
        };

        class BinOpAST : public ExprAST {
        public:
            BinOpAST(AST *left, AST *right, Token op);
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return BinOp;
            }
        private:
            AST *m_left;
            AST *m_right;
            Token m_op;
        };

        class UnOpAST : public ExprAST {
        public:
            UnOpAST(AST *expr, Token op);
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return UnOp;
            }
        private:
            AST *m_expr;
            Token m_op;
        };

        class LiteralIntAST : public ExprAST {
        public:
            LiteralIntAST(Token value);
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return LiteralInt;
            }

            int getValue() const {
                return std::stoi(m_value.getLexeme());
            }
        private:
            Token m_value;
        };

        class LiteralFloatAST : public ExprAST {
        public:
            LiteralFloatAST(Token value);
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return LiteralFloat;
            }

            float getValue() const {
                return std::stof(m_value.getLexeme());
            }
        private:
            Token m_value;
        };

        class IdentifierAST : public ExprAST {
        public:
            IdentifierAST(Token value);
            void print(std::ostream &os) override;
            [[nodiscard]] ASTKind getKind() const override {
                return Identifier;
            }

            [[nodiscard]] std::string getValue() const {
                return m_value.getLexeme();
            }
        private:
            Token m_value;
        };

        class AssignAST : public ExprAST {
        public:
            AssignAST(ExprAST *var, ExprAST *m_value);
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return Assign;
            }
        private:
            ExprAST *m_var;
            ExprAST *m_value;
        };

        class IfAST : public AST {
        public:
            IfAST(ExprAST *condition, AST *thenBranch, AST *elseBranch);
            IfAST(ExprAST *condition, AST *thenBranch) : IfAST(condition, thenBranch, nullptr) {}
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return If;
            }
        private:
            ExprAST *m_condition;
            AST *m_thenBranch;
            AST *m_elseBranch;
        };

        class WhileAST : public AST {
        public:
            WhileAST(ExprAST *condition, AST *body);
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return While;
            }
        private:
            ExprAST *m_condition;
            AST *m_body;
        };

        class BlockAST : public AST {
        public:
            BlockAST(std::vector<AST *> statements);
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return Block;
            }
        private:
            std::vector<AST *> m_statements;
        };

        class ForAST : public AST {
        public:
            ForAST(ExprAST *init, ExprAST *condition, ExprAST *increment, AST *body);
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return For;
            }
        private:
            ExprAST *m_init;
            ExprAST *m_condition;
            ExprAST *m_increment;
            AST *m_body;
        };

        class FunctionAST : public AST {
        public:
            FunctionAST(IdentifierAST *name, std::vector<IdentifierAST *> params, AST *body);
            void print(std::ostream &os) override;
            ASTKind getKind() const override {
                return Function;
            }

        private:
            IdentifierAST *m_name;
            std::vector<IdentifierAST *> m_params;
            AST *m_body;

        };

    } // lang
} // duck

#endif //DUCK_AST_H

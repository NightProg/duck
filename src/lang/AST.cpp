//
// Created by antoine barbier on 11/10/2024.
//

#include <duck/lang/AST.h>

namespace duck {
    namespace lang {
        BinOpAST::BinOpAST(AST *left, AST *right, Token op) : m_left(left), m_right(right), m_op(op) {}

        void BinOpAST::print(std::ostream &os) {
            os << "(";
            m_left->print(os);
            os << " " << m_op.getLexeme() << " ";
            m_right->print(os);
            os << ")";
        }

        UnOpAST::UnOpAST(AST *expr, Token op) : m_expr(expr), m_op(op) {}

        void UnOpAST::print(std::ostream &os) {
            os << "(" << m_op.getLexeme();
            m_expr->print(os);
            os << ")";
        }

        LiteralIntAST::LiteralIntAST(Token token) : m_value(token) {}

        void LiteralIntAST::print(std::ostream &os) {
            os << m_value.getLexeme();
        }

        LiteralFloatAST::LiteralFloatAST(Token token) : m_value(token) {}

        void LiteralFloatAST::print(std::ostream &os) {
            os << m_value.getLexeme();
        }

        IdentifierAST::IdentifierAST(Token token) : m_value(token) {}

        void IdentifierAST::print(std::ostream &os) {
            os << m_value.getLexeme();
        }

        AssignAST::AssignAST(ExprAST *identifier, ExprAST *expr) : m_var(identifier), m_value(expr) {}

        void AssignAST::print(std::ostream &os) {
            m_var->print(os);
            os << " = ";
            m_value->print(os);
        }

        IfAST::IfAST(ExprAST *condition, AST *then, AST *else_) : m_condition(condition), m_thenBranch(then), m_elseBranch(else_) {}

        void IfAST::print(std::ostream &os) {
            os << "if (";
            m_condition->print(os);
            os << ") ";
            m_thenBranch->print(os);
            if (m_elseBranch) {
                os << " else ";
                m_elseBranch->print(os);
            }
        }

        WhileAST::WhileAST(ExprAST *condition, AST *body) : m_condition(condition), m_body(body) {}

        void WhileAST::print(std::ostream &os) {
            os << "while (";
            m_condition->print(os);
            os << ") ";
            m_body->print(os);
        }

        BlockAST::BlockAST(std::vector<AST *> statements) : m_statements(std::move(statements)) {}

        void BlockAST::print(std::ostream &os) {
            os << "{\n";
            for (auto &stmt : m_statements) {
                stmt->print(os);
                os << ";\n";
            }
            os << "}";
        }

        ForAST::ForAST(ExprAST *init, ExprAST *condition, ExprAST *increment, AST *body) : m_init(init), m_condition(condition), m_increment(increment), m_body(body) {}

        void ForAST::print(std::ostream &os) {
            os << "for (";
            m_init->print(os);
            os << "; ";
            m_condition->print(os);
            os << "; ";
            m_increment->print(os);
            os << ") ";
            m_body->print(os);
        }




    } // lang
} // duck
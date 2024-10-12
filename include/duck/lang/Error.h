//
// Created by antoine barbier on 11/10/2024.
//

#ifndef DUCK_ERROR_H
#define DUCK_ERROR_H

#include <string>
#include <iostream>

namespace duck {
    namespace lang {

        class Error {
        public:
            Error(std::string message, int line, int column) : m_message(std::move(message)), m_line(line), m_column(column) {}

            [[nodiscard]] std::string getMessage() const {
                return m_message;
            }

            [[nodiscard]] int getLine() const {
                return m_line;
            }

            [[nodiscard]] int getColumn() const {
                return m_column;
            }

            void print(std::ostream &os) {
                os << "Error at line " << m_line << " and column " << m_column << ": " << m_message << std::endl;
            }

        private:
            std::string m_message;
            int m_line;
            int m_column;

        };

    } // lang
} // duck

#endif //DUCK_ERROR_H

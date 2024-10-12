//
// Created by antoine barbier on 11/10/2024.
//

#include <duck/lang/Cursor.h>

namespace duck::lang {
    template<typename T>
    Cursor<T>::Cursor(std::vector<T> data) : m_data(std::move(data)), m_current(m_data.begin()) {

    }

    template<typename T>
    T Cursor<T>::peek() {
        if (isAtEnd()) {
            return nullptr;
        }
        return *m_current;
    }

    template<typename T>
    T Cursor<T>::advance() {
        if (isAtEnd()) {
            return nullptr;
        }
        return *m_current++;
    }

    template<typename T>
    bool Cursor<T>::isAtEnd() {
        return m_current == m_data.end();
    }

    template<typename T>
    void Cursor<T>::reset() {
        m_current = m_data.begin();
    }

    template<typename T>
    void Cursor<T>::back() {
        if (m_current != m_data.begin()) {
            m_current--;
        }
    }

    template<typename T>
    void Cursor<T>::skip(int n) {
        for (int i = 0; i < n; i++) {
            advance();
        }
    }

    template<typename T>
    bool Cursor<T>::match(T expected) {
        if (isAtEnd()) {
            return false;
        }
        if (peek() == expected) {
            advance();
            return true;
        }
        return false;
    }

    template<typename T>
    bool Cursor<T>::check(T expected) {
        if (isAtEnd()) {
            return false;
        }
        return peek() == expected;
    }

    template<typename T>
    bool Cursor<T>::checkNext(T expected) {
        if (isAtEnd() || m_current + 1 == m_data.end()) {
            return false;
        }
        return *(m_current + 1) == expected;
    }

    template<typename T>
    bool Cursor<T>::matchNext(T expected) {
        if (isAtEnd() || m_current + 1 == m_data.end()) {
            return false;
        }
        if (*(m_current + 1) == expected) {
            m_current++;
            return true;
        }
        return false;
    }

}

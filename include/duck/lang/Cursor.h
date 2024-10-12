//
// Created by antoine barbier on 11/10/2024.
//

#ifndef DUCK_CURSOR_H
#define DUCK_CURSOR_H

#include <vector>
#include <iterator>
namespace duck::lang {
    template<typename T>
    class Cursor {
    public:
        Cursor(std::vector<T> data);

        T peek();
        T advance();
        bool isAtEnd();
        void reset();
        void back();
        void skip(int n);

        bool match(T expected);
        bool check(T expected);
        bool checkNext(T expected);
        bool matchNext(T expected);

    private:
        std::vector<T> m_data;
        std::vector<T>::iterator m_current;

    };
}


#endif //DUCK_CURSOR_H

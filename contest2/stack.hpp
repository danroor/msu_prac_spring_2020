#ifndef stack_hpp
#define stack_hpp

#include "complex.hpp"

namespace numbers
{
    class complex_stack
    {
        complex *arr;
        int element_counter;
        int stack_size;
        
        void push (complex addend);
        
        void pop ();
        
    public:
        complex_stack ();
        
        complex_stack (const complex_stack &cpy);
        
        ~complex_stack ();
        
        size_t size () const;
        
        complex &operator[] (int x) const;
        
        complex_stack operator<< (const complex &cmplx) const;
        
        complex &operator+ () const;
        
        complex_stack operator~ () const;
        
        complex_stack &operator= (const complex_stack &cmplx);
    };
}

#endif /* stack_hpp */

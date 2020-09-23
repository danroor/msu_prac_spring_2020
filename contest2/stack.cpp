#include "stack.hpp"

namespace numbers
{
    
    void complex_stack::push (complex addend)
    {
        if (stack_size < element_counter + 1) {
            stack_size *= 2;
            complex *tmp = new complex [stack_size];
            int i;
            for (i = 0; i < element_counter; i++)
            {
                tmp[i] = arr[i];
            }
            delete [] arr;
            arr = tmp;
        }
        element_counter += 1;
        arr[element_counter - 1] = addend;
    }
    
    void complex_stack::pop ()
    {
        --element_counter;
        
    }
    
    complex_stack::complex_stack ()
    {
        element_counter = 0;
        stack_size = 1;
        arr = new complex[stack_size];
    }
    
    complex_stack::complex_stack (const complex_stack &cpy)
    {
        if (cpy.element_counter > 0) {
            this->arr = new complex [cpy.element_counter];
            for (int i = 0; i < cpy.element_counter; ++i) {
                this->arr[i] = cpy.arr[i];
            }
            this->element_counter = cpy.element_counter;
            this->stack_size = cpy.element_counter;
        } else {
            this->element_counter = cpy.element_counter;
            this->stack_size = 1;
            arr = new complex[stack_size];
        }
    }
    
    complex_stack::~complex_stack ()
    {
        if (stack_size > 0) {
            delete [] arr;
        }
    }
    
    size_t complex_stack::size () const
    {
        return element_counter;
    }
    
    complex &complex_stack::operator[] (int x) const
    {
        return arr[x];
    }
    
    complex_stack complex_stack::operator<< (const complex &cmplx) const
    {
        complex_stack newstack = *this;
        newstack.push(cmplx);
        return newstack;
    }
    
    complex &complex_stack::operator+ () const
    {
        return this->arr[element_counter - 1];
    }
    
    complex_stack complex_stack::operator~ () const
    {
        complex_stack newstack = *this;
        newstack.pop();
        return newstack;
    }
    
    complex_stack &complex_stack::operator= (const complex_stack &cpy)
    {
        this->stack_size = cpy.stack_size;
        this->element_counter = cpy.element_counter;
        delete [] arr;
        this->arr = new complex [cpy.element_counter];
        for (int i = 0; i < cpy.element_counter; ++i) {
            this->arr[i] = cpy.arr[i];
        }
        return *this;
    }
}

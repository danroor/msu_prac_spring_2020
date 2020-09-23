namespace numbers {
    class complex_stack
    {
        complex *stack;
        size_t sz, ncur;
    public:
        complex_stack() {
            sz = ncur = 0;
        }

        complex_stack(const complex_stack &oldstack) : sz(oldstack.sz), ncur(oldstack.ncur) {
            stack = new complex[sz];
            for (unsigned int i = 0; i < ncur; ++i) {
                stack[i] = oldstack.stack[i];
            }
        }

        ~complex_stack() {
            if (sz > 0)
                delete [] stack;
        }

        size_t size() const {
            return ncur;
        }

        complex_stack operator<<(const complex &z) const {
            complex_stack newstack;
            if (ncur == sz) {
                newstack.sz =  (sz << 1) + 1;
                newstack.stack = new complex[newstack.sz];
            } else {
                newstack.sz = sz;
                newstack.stack = new complex[sz];
            }
            newstack.ncur = ncur + 1;
            
            for (unsigned int i = 0; i < ncur; ++i) {
                newstack.stack[i] = stack[i];
            }
            newstack.stack[ncur] = z;
            return newstack;
        }

        const complex operator+() const {
            return stack[ncur - 1];
        }

        const complex_stack operator~() const {
            complex_stack newstack(*this);
            newstack.ncur--;
            return newstack;
        }

        const complex operator[](const int &i) const {
            return stack[i];
        }

        complex_stack & operator=(const complex_stack &stck) {
            if (sz > 0) {
                delete [] stack;
            }
            sz = stck.sz;
            ncur = stck.ncur;
            stack = new complex[sz];
            
            for (unsigned int i = 0; i < ncur; ++i) {
                stack[i] = stck.stack[i];
            }
            return *this;
        }
    };
};

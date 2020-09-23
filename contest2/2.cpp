/*

# 2

В пространстве имен numbers реализуйте класс complex_stack,
который будет реализовывать функциональность иммутабельного стека комплексных чисел из предыдущей задачи.

Реализация не должна использовать стандартные контейнерные классы (vector, stack и т. п.).

Класс должен реализовывать:

конструктор по умолчанию.
конструкторы, деструкторы и операции, необходимые для корректного управления памятью.
метод size для получения числа элементов в стеке (возвращает size_t).
доступ к произвольному элементу стека только на чтение с помощью операции [].
бинарный оператор <<, у которого первый аргумент - complex_stack, а второй аргумент - complex,
бинарный оператор возвращает новый стек, в который добавлен указанный элемент. Исходный стек не изменяется.
унарный оператор +, который возвращает элемент типа complex с вершины стека.
унарный оператор ~, который удаляет один элемент из стека и возвращает модифицированный стек,
исходный стек при этом не изменяется.
На проверку сдавайте только класс complex_stack.

Возможные ошибки (извлечение из пустого стека, доступ за пределами стека) игнорируйте.

Дополнительно реализуйте:

Семантику переноса в конструкторе, присваивании и операциях << и ~
placement new для минимизации вызовов конструкторов при перевыделении памяти

*/


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

#include <stdexcept>

class StringImpl
{
    char *data;
    size_t *cntref, length;

public:
    explicit StringImpl() : data(nullptr), cntref(new size_t), length(0) {
        *cntref = 1;
    }
    explicit StringImpl(const char *s) : data(nullptr), cntref(new size_t), length(0) {
        *cntref = 1;
        if (s == nullptr) {
            return;
        }
        size_t len = 0;
        for (; s[len] != '\0'; ++len);
        length = len;

        data = new char[len + 1];
        for (size_t i = 0; i <= len; ++i) {
            data[i] = s[i];
        }
    }
    explicit StringImpl(const StringImpl &s) : data(s.data), cntref(s.cntref), 
                                               length(s.length)
    {
        (*cntref)++;
    }
    ~StringImpl() {
        if (*cntref == 1) {
            if (data != nullptr) {
                delete [] data;
            }
            delete cntref;
        } else {
            (*cntref)--;
        }
    }

    const char& getElem(size_t i) {
        if (i >= length) {
            throw std::out_of_range("");
        }
        return data[i];
    }

    char& changeElem(size_t i) {
        if (i >= length) {
            throw std::out_of_range("");
        }
        
        if (*cntref > 1) {
            (*cntref)--;
            cntref = new size_t;
            *cntref = 1;

            if (data != nullptr) {
                char *ptr = new char[length + 1];
                for (size_t i = 0; i <= length; ++i) {
                    ptr[i] = data[i];
                }
                data = ptr;
            }
        }
        return data[i];
    }

    void append(const StringImpl &s) {
        char *ptr = new char[length + s.length + 1];
        for (size_t i = 0; i < length; ++i) {
            ptr[i] = data[i];
        }
        for (size_t i = length; i <= length + s.length; ++i) {
            ptr[i] = s.data[i - length];
        }

        length += s.length;
    
        if (*cntref > 1) {
            (*cntref)--;
            cntref = new size_t;
            *cntref = 1;
        } else if (data != nullptr) {
            delete [] data;
        }
        data = ptr;
    }

    char* get_data() const {
        return data;
    }
};

class String
{
    StringImpl *ptr;
public:
    String() : ptr(new StringImpl) {}
    String(const char *s) : ptr(new StringImpl(s)) {}
    String(const String &s) : ptr( new StringImpl(*(s.ptr)) ) {}

    String& operator=(const String &s) {
        delete ptr;
        ptr = new StringImpl(*(s.ptr));
        return *this;
    }
    ~String() {
        delete ptr;
    }

    const char& operator[](size_t i) const {
        return ptr->getElem(i);
    }

    char& operator[](size_t i) {
        return ptr->changeElem(i);
    }

    String& operator+=(const String &s) {
        ptr->append(*(s.ptr));
        return *this;
    }

    operator std::string() const {
        return std::string(ptr->get_data());
    }
};

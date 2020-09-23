#ifndef LONGLONGLONG_H
#define LONGLONGLONG_H

class LongLongLong
{
    int a_;
public:
    LongLongLong(int a = 0): a_(a) {
    }
    LongLongLong(std::string str) {
        std::cout << "LongLongLong c-tor: str = \'";
        std::cout << str << "'\n";
        std::istringstream(str) >> a_;
    }
    int get() const {
        return a_;
    }
    friend std::ostream& operator << (std::ostream& out, LongLongLong var) {
        out << var.a_;
        return out;
    }
    LongLongLong& operator-() {
        a_ = -a_;
        return *this;
    }
};

bool operator> (LongLongLong left, LongLongLong right) {
    return left.get() > right.get();
}

bool operator< (LongLongLong left, LongLongLong right) {
    return left.get() < right.get();
}

LongLongLong operator+(LongLongLong left, LongLongLong right) {
    return LongLongLong(left.get() + right.get());
}

LongLongLong operator-(LongLongLong left, LongLongLong right) {
    return LongLongLong(left.get() - right.get());
}

LongLongLong operator*(LongLongLong left, LongLongLong right) {
    return LongLongLong(left.get() * right.get());
}

#endif

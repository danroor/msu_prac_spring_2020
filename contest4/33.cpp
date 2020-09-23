#include <iostream>
#include <list>
#include <iterator>
#include <functional>

using namespace std;

template <typename iter, typename func>
void myapply(iter begin, iter end, func f)
{
    for (auto it = begin; it != end; ++it) {
        f(*it);
    }
}

template <typename iter, typename func>
auto myfilter2(iter begin, iter end, func predic)
-> std::vector<std::reference_wrapper <typename iter::value_type> >
{
    std::vector<std::reference_wrapper <typename iter::value_type> > newcont;

    for (auto it = begin; it != end; ++it) {
        if (predic(*it)) {
            newcont.push_back(std::ref(*it));
        }
    }

    return newcont;
}

template <typename arr, typename func>
void myapply(arr *begin, arr *end, func f)
{
    for (auto it = begin; it != end; ++it) {
        f(*it);
    }
}

template <typename arr, typename func>
auto myfilter2(arr *begin, arr *end, func predic)
-> std::vector<std::reference_wrapper <arr> >
{
    std::vector<std::reference_wrapper <arr> > newcont;

    for (auto it = begin; it != end; ++it) {
        if (predic(*it)) {
            newcont.push_back(std::ref(*it));
        }
    }

    return newcont;
}

//template <typename T>
void f(int &x) { x++; } 

int main()
{
   /* std::list<int> v{1,2,3,4,5,6};

    auto res = myfilter2(v.begin(), v.end(), [](int x) { return x % 2 == 1;  } );
   
    myapply(res.begin(), res.end(), f);

    for (auto vv : v)
        cout << vv << endl; */

    int a[] = {1,2,3,4,5,6,7,8,9,0};
 
    auto res = myfilter2(a, a + 9, [](int x) { return x % 2 == 1;  } );

    for (auto vv : a)
        cout << vv << " ";

    cout << endl;

    for (auto vv : res)
        cout << vv << " ";


    cout << endl;

    myapply(res.begin(), res.end(), f);

    for (auto vv : a)
        cout << vv << " ";

    cout << endl;
}

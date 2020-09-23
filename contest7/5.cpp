#include <iostream>
#include <boost/date_time.hpp>

unsigned long long date_dist(std::string &date1, std::string &date2) {

    using namespace boost::gregorian;

    int year, month, day;
    auto calc_month = [](int x) -> int {
        switch(x) {
        case 1:
            return Jan;
        case 2:
            return Feb;
        case 3:
            return Mar;
        case 4:
            return Apr;
        case 5:
            return May;
        case 6:
            return Jun;
        case 7:
            return Jul;
        case 8:
            return Aug;
        case 9:
            return Sep;
        case 10:
            return Oct;
        case 11:
            return Nov;
        default: //12
            return Dec;
        }
    };

    year = (date1[0] - '0') * 1000 + (date1[1] - '0') * 100 + 
            (date1[2] - '0') * 10 + (date1[3] - '0');

    day = (date1[8] - '0') * 10 + (date1[9] - '0');
    month = calc_month((date1[5] - '0') * 10 + (date1[6] - '0'));

    date d1(year, month, day);

    year = (date2[0] - '0') * 1000 + (date2[1] - '0') * 100 + 
            (date2[2] - '0') * 10 + (date2[3] - '0');

    day = (date2[8] - '0') * 10 + (date2[9] - '0');
    month = calc_month((date2[5] - '0') * 10 + (date2[6] - '0'));

    date d2(year, month, day);
    if (d2 > d1) {
        return (d2 - d1).days();
    } else {
        return (d1 - d2).days();
    }
}

int main() {
    unsigned long long dist = 0;

    std::string prev, date;
    std::cin >> prev;
    while (std::cin >> date) {
        dist += date_dist(prev, date);
        prev = date;
    }

    std::cout << dist << std::endl;
    return 0;
}

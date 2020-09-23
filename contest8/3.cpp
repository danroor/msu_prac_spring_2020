#include <iostream>
#include <string>

static constexpr int CONTEXT_FREE = 2, NOT_SHORTEN = 3, 
        NOT_CONTEXT_FREE = 10, NOT_GRAMMAR = -1;

int main()
{ 
    bool not_shorten = true, context_free = true, no_start = true, left_is_S = false, 
        S_left_only = true, invalid = false, term_only = true, not_term = true, underline = false;

    size_t lsz = 0, rsz = 0;

    std::string str;
    while (std::cin >> str) {

        if (lsz == 0) {
            //left
            lsz = str.size();
            term_only = true;
            not_term = false;
            for (char i : str) {
                if ( (i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') ) {
                    context_free = false;
                } else if (i >= 'A' && i <= 'Z') {
                    term_only = false;
                    context_free &= !not_term;
                    not_term = true;
                } else {
                    invalid = true;
                    break;
                }
            }

            invalid |= term_only;

            left_is_S = lsz == 1 && str[0] == 'S'; 
            no_start &= !left_is_S;

            rsz = 0;
            continue;
        }

        //right
        rsz = str.size();

        if (lsz > rsz) {
            not_shorten = false;
        }

        for (char i : str) {
            if (i >= 'A' && i <= 'Z') {
                S_left_only &= i != 'S';
            } else if ( (i < 'a' || i > 'z') && (i < '0' || i > '9')) {
                if (i == '_') {
                    underline = true;
                    not_shorten &= left_is_S;
                    if (rsz > 1) {
                        invalid = true;
                        break;
                    }
                } else {
                    invalid = true;
                    break;
                }
            }
            
        }

        lsz = 0;
    }

    not_shorten &= (!underline || S_left_only);
    invalid |= rsz == 0 || no_start;

    if (invalid) {
        std::cout << NOT_GRAMMAR;
    } else if (context_free) {
        std::cout << CONTEXT_FREE;
        if (not_shorten) {
            std::cout << NOT_SHORTEN;
        }
    } else {
        std::cout << NOT_CONTEXT_FREE;
    }

    std::cout << std::endl;

    return 0;
}

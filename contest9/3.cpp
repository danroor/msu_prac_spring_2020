/*

На вход подается описание грамматики в следующем виде: каждое правило состоит из двух символьных строк,
разделяемых произвольным количеством пробельных символов.
Грамматика представляет собой последовательность правил.
Таким образом, на вход подается четное число строк,
разделяемых произвольным количеством пробельных символов.

В строках допускаются:

Заглавные латинские буквы, обозначающие нетерминалы.
Строчные латинские буквы и цифры, обозначающие терминалы.
Символ подчеркивания, обозначающий пустую правую часть (эпсилон).
Символ подчеркивания может находится только в правой части правила,
в этом случае он является единственным символом в правой части.

Начальный нетерминал грамматики всегда 'S'.

Гарантируется, что входная грамматика — контекстно-свободная (в том числе укорачивающая),
то есть удовлетворяет правилам, описанным в задаче 'is-context-free'.

На стандартный поток вывода напечатайте:

2 если грамматика является контекстно-свободной,
но не неукорачивающей контекстно-свободной и не регулярной.
21 если грамматика является неукорачивающей контестно-свободной,
но не является регулярной.
31 если грамматика является леволинейной регулярной грамматикой, но не является левоавтоматной
311 если грамматика является левоавтоматной грамматикой
32 если грамматика является праволинейной регулярной грамматикой, но не является правоавтоматной
321 если грамматика являеся правоавтоматной грамматикой

В случае неоднозначности выводите меньший номер.

В леволинейной или праволинейной грамматике в правой части правил допускается
произвольное (в том числе нулевое) количество терминальных символов.
В лево- или право-автоматной грамматике в правой части правил
всегда должен присутствовать ровно один терминал.
Но в автоматной грамматике в качестве исключения допускаются
два правила для вывода пустой цепочки из S вида:

S _
S A
В этом случае грамматика со стартовым нетерминалом A должна быть автоматной в строгом смысле,
а нетерминал S не должен использоваться в правых частях правил.

*/

#include <iostream>
#include <string>

constexpr int SHORTEN = 2, NON_SHORTEN = 21, LEFTLIN = 31, RIGHTLIN = 32,
        LEFTAUTO = 311, RIGHTAUTO = 321, AUTO = 0, REGUL = 1;

inline bool terminal(char i) {
    return (i >= '0' && i <= '9') || (i >= 'a' && i <= 'z');
}

int main()
{
    std::string left, right;
    int state = AUTO;
    size_t sz;
    bool s_left_only = true, underline = false;

    char on_right = '-', l, r;

    while (std::cin >> left >> right) {
        
        l = left[0];
        r = right[0];

        sz = right.size();

        if (sz == 1) {
            if (r == '_') {
                underline = true;
                if (l != 'S') {
                    if (state == AUTO) {
                        state = REGUL;
                    } else if (state == LEFTAUTO) {
                        state = LEFTLIN;
                    } else if (state == RIGHTAUTO) {
                        state = RIGHTLIN;
                    } else if (state != REGUL && state != LEFTLIN && state != RIGHTLIN) {
                        state = SHORTEN;
                    }
                }
            } else if (r >= 'A' && r <= 'Z') {

                s_left_only &= r != 'S';

                if (l != 'S') {
                    if (state == AUTO) {
                        state = REGUL;
                    } else if (state == LEFTAUTO) {
                        state = LEFTLIN;
                    } else if (state == RIGHTAUTO) {
                        state = RIGHTLIN;
                    }
                } else {
                    
                    if (on_right == '-' || on_right == r) {
                        on_right = r;
                    } else {
                        if (state == AUTO) {
                            state = REGUL;
                        } else if (state == LEFTAUTO) {
                            state = LEFTLIN;
                        } else if (state == RIGHTAUTO) {
                            state = RIGHTLIN;
                        }
                    }
                }

            }

        } else if (r >= 'A' && r <= 'Z') {
            //left
            s_left_only &= r != 'S';

            for (size_t i = 1; i < sz; ++i) {
                if (!terminal(right[i])) {
                    if (state != SHORTEN) {
                        state = NON_SHORTEN;
                    }
                    break;
                }
            }

            switch (state) {
            case SHORTEN:
            case NON_SHORTEN:
            case LEFTLIN:
                break;
            case REGUL:
                state = LEFTLIN;
                break;
            case AUTO:
            case LEFTAUTO:
                state = LEFTAUTO;
                if (sz > 2) {
                    state = LEFTLIN;
                }
                break;
            default: //RIGHTLIN, RIGHTAUTO
                state = NON_SHORTEN;
            }

        } else if (right[sz - 1] >= 'A' && right[sz - 1] <= 'Z') {
            //right

            s_left_only &= right[sz - 1] != 'S';

            for (size_t i = 0; i < sz - 1; ++i) {
                if (!terminal(right[i])) {
                    if (state != SHORTEN) {
                        state = NON_SHORTEN;
                    }
                    break;
                }
            }

            switch (state) {
            case SHORTEN:
            case NON_SHORTEN:
            case RIGHTLIN:
                break;
            case REGUL:
                state = RIGHTLIN;
                break;
            case AUTO:
            case RIGHTAUTO:
                state = RIGHTAUTO;
                if (sz > 2) {
                    state = RIGHTLIN;
                }
                break;
            default: //LEFTLIN, LEFTAUTO
                state = NON_SHORTEN;
            }

        } else {

            bool flag = true;

            for (size_t i = 0; i < sz; ++i) {
                flag &= terminal(right[i]);

                if (right[i] == 'S') {
                    s_left_only = false;
                    break;
                }
            }            
 
            if (flag) {
                if (state == AUTO) {
                    state = REGUL;
                } else if (state == LEFTAUTO) {
                    state = LEFTLIN;
                } else if (state == RIGHTAUTO) {
                    state = RIGHTLIN;
                }
            } else if (state != SHORTEN) {
                state = NON_SHORTEN;
            }
        }
    }

    bool rf = on_right != '-';

    if (underline && rf) {
        if (!s_left_only) {
            if (state == AUTO) {
                state = REGUL;
            } else if (state == LEFTAUTO) {
                state = LEFTLIN;
            } else if (state == RIGHTAUTO) {
                state = RIGHTLIN;
            } else if (state != REGUL && state != LEFTLIN && state != RIGHTLIN) {
                state = SHORTEN;
            }
        }
    } else if (underline) {
        if (!s_left_only) {
            if (state == AUTO) {
                state = REGUL;
            } else if (state == LEFTAUTO) {
                state = LEFTLIN;
            } else if (state == RIGHTAUTO) {
                state = RIGHTLIN;
            } else if (state != REGUL && state != LEFTLIN && state != RIGHTLIN) {
                state = SHORTEN;
            }
        }
    } else if (rf) {
        if (state == AUTO) {
            state = REGUL;
        } else if (state == LEFTAUTO) {
            state = LEFTLIN;
        } else if (state == RIGHTAUTO) {
            state = RIGHTLIN;
        }
    }


    if (state == AUTO) {
        state = LEFTAUTO;
    } else if (state == REGUL) {
        state = LEFTLIN;
    }

    std::cout << state << std::endl;

    return 0;
}

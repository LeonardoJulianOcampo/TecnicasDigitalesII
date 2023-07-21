#include <stdio.h>


int counter(int select,int reset, int count_max) {
    static int count = 0;

    if (reset == 1)
	count = 0;
    else if (select == 1 && count < count_max - 1)
        count++;
    else if (select == 1 && count == count_max - 1)
        count = 0;
    else if (select == 0 && count > 0)
        count--;
    else if (select == 0 && count == 0)
        count = count_max - 1;
    else
        count = count;

    return count;
}

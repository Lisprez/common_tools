#include <stdbool.h>
/**
 * true small end
 * false big end
 */

bool check_system_end()
{
    union check {
        int i;
        char ch;
    } c;

    c.i = 1;

    return (c.ch == 1);
}

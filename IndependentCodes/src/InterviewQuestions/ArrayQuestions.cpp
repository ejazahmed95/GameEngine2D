#include "ArrayQuestions.h"

void ReorderZeros(int* p_Ints, int size) {
    for (int lastNonZeroAt = 0, cur = 0; cur < size; cur++) {
        if (p_Ints[cur] != 0) {
            if (lastNonZeroAt != cur) {
                p_Ints[lastNonZeroAt] ^= p_Ints[cur];
                p_Ints[cur] ^= p_Ints[lastNonZeroAt];
                p_Ints[lastNonZeroAt] ^= p_Ints[cur];
            }
            lastNonZeroAt++;
        }
    }
}
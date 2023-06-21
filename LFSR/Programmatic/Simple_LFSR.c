#include <stdio.h>

int main(){
    int state = 0b1001;
    for (int i = 0; i < 20; i++) {
        printf("This is the current state: ");
        for (int i = 1 << 3; i > 0; i = i >> 1) {
            if (state & i) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
        // Compute new state for Simple_LFSR from folder Logisim
        int newBit = (state ^ (state >> 1)) & 1;
        state = (state >> 1) |  (newBit << 3);        
    }
    return 0;
}
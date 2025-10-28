#include <stdio.h>

int main() {
    int buffer[10];
    int bufsize = 10;
    int in = 0, out = 0;
    int produce, consume;
    int choice = 0;

    while (choice != 3) {
        printf("\n1. Produce\t2. Consume\t3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if ((in + 1) % bufsize == out) {
                    printf("\nBuffer is Full\n");
                } else {
                    printf("\nEnter the value to produce: ");
                    scanf("%d", &produce);
                    buffer[in] = produce;
                    in = (in + 1) % bufsize;
                    printf("Produced value: %d\n", produce);
                }
                break;

            case 2:
                if (in == out) {
                    printf("\nBuffer is Empty\n");
                } else {
                    consume = buffer[out];
                    out = (out + 1) % bufsize;
                    printf("Consumed value: %d\n", consume);
                }
                break;

            case 3:
                printf("\nExiting...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }

        printf("\nCurrent Buffer: [ ");
        for (int i = 0; i < bufsize; i++) {
            int filled = 0;
            int j = out;
            while (j != in) {
                if (i == j) {
                    printf("%d ", buffer[i]);
                    filled = 1;
                    break;
                }
                j = (j + 1) % bufsize;
            }
            if (!filled)
                printf("_ ");
        }
        printf("]\n");
    }

    return 0;
}

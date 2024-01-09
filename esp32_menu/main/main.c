#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include <string.h>
#include <stdlib.h>

#define UART_NUM UART_NUM_0

void read_input(char *input, int max_length) {
    // Clear UART input buffer to remove any lingering characters
    uart_flush_input(UART_NUM);

    memset(input, 0, max_length);
    int length = 0;
    char ch;
    while (1) {
        if (uart_read_bytes(UART_NUM, (unsigned char*)&ch, 1, portMAX_DELAY) > 0) {
            if (ch == '\n' || ch == '\r') {
                printf("\n");
                fflush(stdout);
                break;
            } else if (ch == '\b' || ch == 127) {
                if (length > 0) {
                    length--;
                    input[length] = '\0';
                    printf("\b \b");
                    fflush(stdout);
                }
            } else if (length < max_length - 1) {
                input[length++] = ch;
                printf("%c", ch);
                fflush(stdout);
            }
        }
    }
}


void option1_sub_menu() {
    printf("Option 1 Submenu\n");
    printf("Enter numerical arguments (separated by space) > ");
     fflush(stdout);

    char input[100];
    read_input(input, sizeof(input));

    // Process the input - example: split by spaces
    printf("You entered: %s\n", input);

    // Further processing can be done here to handle the arguments
    // For example, tokenize the input string and convert each token to an integer
}

void app_main(void) {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_driver_install(UART_NUM, 256, 0, 0, NULL, 0);

    int running = 1;
    char input[10]; // Buffer for input

    printf("\n\n");
    while (running) {
        printf("\n--- Main Menu ---\n");
       printf("1. Option 1\n");
        printf("2. Option 2\n");
        printf("3. Option 3\n");
        printf("23. Option 23\n");
        printf("0. Quit\n");
        printf("Enter choice: ");

        fflush(stdout);

        read_input(input, sizeof(input));

        int choice = atoi(input);

        printf("\nyou selected: %d\n\n", choice);
        fflush(stdout);
        switch (choice) {
            case 1:
                option1_sub_menu();
                break;
            case 2:
                printf("Option 2 selected\n");
                // Add your code for Option 2 here
                break;
            case 3:
                printf("Option 3 selected\n");
                // Add your code for Option 3 here
                break;
            case 23:
                printf("Option 23 selected\n");
                // Add your code for Option 23 here
                break;
            case 0:
                printf("Quitting...\n");
                running = 0; // Exit the loop to end the program
                break;
            default:
                printf("Invalid choice (%d). Please try again.\n", choice);
                break;
        }
    }
}

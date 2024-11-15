#include <stdio.h>
#include <string.h>

#define STACK_SIZE 100

// Stack and input symbols
char stack[STACK_SIZE];
char input[STACK_SIZE];
int top = -1;

// Push onto stack
void push(char symbol) {
    if (top < STACK_SIZE - 1) {
        stack[++top] = symbol;
    }
}

// Pop from stack
void pop() {
    if (top >= 0) {
        top--;
    }
}

// Check if stack contains a specific string
int checkStack(const char *str) {
    int len = strlen(str);
    if (top + 1 < len) return 0;
    for (int i = 0; i < len; i++) {
        if (stack[top - len + 1 + i] != str[i]) {
            return 0;
        }
    }
    return 1;
}

// Display current stack and input
void display() {
    printf("Stack: ");
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
    printf("\tInput: %s\n", input);
}

// Main shift-reduce parsing logic
void parse() {
    int pos = 0;
    while (input[pos] != '\0') {
        // Shift step
        push(input[pos++]);
        display();

        // Reduce step
        while (1) {
            if (checkStack("E+E")) {
                top -= 2;  // Reduce "E+E" to "E"
                stack[top] = 'E';
                printf("Reduced by E -> E+E\n");
            } else if (checkStack("E*E")) {
                top -= 2;  // Reduce "E*E" to "E"
                stack[top] = 'E';
                printf("Reduced by E -> E*E\n");
            } else if (checkStack("(E)")) {
                top -= 2;  // Reduce "(E)" to "E"
                stack[top] = 'E';
                printf("Reduced by E -> (E)\n");
            } else if (checkStack("i")) {
                stack[top] = 'E';  // Reduce "i" to "E"
                printf("Reduced by E -> i\n");
            } else {
                break;
            }
            display();
        }
    }

    // Final check if we have a valid expression
    if (top == 0 && stack[top] == 'E') {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }
}

int main() {
    printf("Enter an expression (use 'i' for identifiers): ");
    scanf("%s", input);

    printf("\nParsing process:\n");
    parse();

    return 0;
}


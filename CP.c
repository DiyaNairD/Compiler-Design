#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct expr {
    char op[2], op1[5], op2[5], res[5];
    int flag;
} arr[10];

int n;

void input() {
    printf("\nEnter the number of expressions: ");
    scanf("%d", &n);
    printf("\nEnter the expressions (op op1 op2 res):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %s %s %s", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
        arr[i].flag = 0;
    }
}

void optimize() {
    for (int i = 0; i < n; i++) {
        if ((isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0])) || strcmp(arr[i].op, "=") == 0) {
            int op1 = atoi(arr[i].op1), op2 = atoi(arr[i].op2), res = 0;
            char result[5];

            switch (arr[i].op[0]) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
                case '=': res = op1; break;
            }

            sprintf(result, "%d", res);
            arr[i].flag = 1;

            // Replace occurrences in subsequent expressions
            for (int j = i + 1; j < n; j++) {
                if (strcmp(arr[i].res, arr[j].op1) == 0) strcpy(arr[j].op1, result);
                if (strcmp(arr[i].res, arr[j].op2) == 0) strcpy(arr[j].op2, result);
            }
        }
    }
}

void output() {
    printf("\nOptimized Code:\n");
    for (int i = 0; i < n; i++) {
        if (!arr[i].flag)
            printf("%s %s %s %s\n", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
    }
}

int main() {
    input();
    optimize();
    output();
    return 0;
}


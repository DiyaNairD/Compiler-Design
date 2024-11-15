#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100

void generateThreeAddressCode(char *expression) 
{
    int tempCount = 1, opTop = -1, operTop = -1;
    char opStack[MAX_EXPR_LENGTH], operStack[MAX_EXPR_LENGTH][5], temp[5];

    for (int i = 0; expression[i]; i++) 
    {
        if (isspace(expression[i])) 
          continue;

        if (isalnum(expression[i])) 
        {  // Operand
            operStack[++operTop][0] = expression[i];
            operStack[operTop][1] = '\0';
        } 
        else 
        {  // Operator
            while (opTop >= 0 && strchr("*/", opStack[opTop])) 
            {
                sprintf(temp, "t%d", tempCount++);
                printf("%s = %s %c %s\n", temp, operStack[operTop - 1], opStack[opTop--], operStack[operTop]);
                strcpy(operStack[--operTop], temp);
            }
            opStack[++opTop] = expression[i];
        }
    }

    while (opTop >= 0) 
    {
        sprintf(temp, "t%d", tempCount++);
        printf("%s = %s %c %s\n", temp, operStack[operTop - 1], opStack[opTop--], operStack[operTop]);
        strcpy(operStack[--operTop], temp);
    }
    printf("result = %s\n", operStack[operTop]);
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) return perror("Error opening file"), 1;

    char expression[MAX_EXPR_LENGTH];
    if (fgets(expression, sizeof(expression), file)) 
    {
        printf("Expression: %sThree-address code:\n", expression);
        generateThreeAddressCode(expression);
    } else {
        printf("Error reading expression.\n");
    }
    fclose(file);
    return 0;
}


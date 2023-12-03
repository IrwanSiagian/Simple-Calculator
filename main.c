#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_EXPR_LENGTH 100

int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
    {
        return 1;
    }
    return 0;
}

int precedence(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

void calculate(char operator, double * operandStack, int *index)
{
    double B = operandStack[--(*index)];
    double A = operandStack[--(*index)];
    double result = 0;

    switch (operator)
    {
    case '+':
        result = A + B;
        break;
    case '-':
        result = A - B;
        break;
    case '*':
        result = A * B;
        break;
    case '/':
        result = A / B;
        break;
    }

    operandStack[(*index)++] = result;
}

double evaluate(char *expression)
{
    double operandStack[MAX_EXPR_LENGTH];
    char operatorStack[MAX_EXPR_LENGTH];
    int operandIndex = 0, operatorIndex = 0;
    int i = 0;

    while (expression[i] != '\0')
    {
        if (isdigit(expression[i]))
        {
            operandStack[operandIndex++] = expression[i] - '0';
        }
        else if (isOperator(expression[i]))
        {
            while (operatorIndex > 0 && precedence(operatorStack[operatorIndex - 1]) >= precedence(expression[i]))
            {
                calculate(operatorStack[--operatorIndex], operandStack, &operandIndex);
            }
            operatorStack[operatorIndex++] = expression[i];
        }
        i++;
    }

    while (operatorIndex > 0)
    {
        calculate(operatorStack[--operatorIndex], operandStack, &operandIndex);
    }

    return operandStack[0];
}

char *rmSpace(char *string)
{
    char *token;
    token = strtok(string, " ");
    char *result;
    result = (char *)calloc(100, sizeof(char *));
    int i = 0;

    while (token != NULL)
    {
        strcat(result, token);
        token = strtok(NULL, " ");
    }
    return result;
}

int main()
{
    char *expression;
    expression = (char *)calloc(100, sizeof(char *));
    scanf("%[^\n]", expression);
    expression = rmSpace(expression);
    double result = evaluate(expression);
    printf("Result: %.3f\n", result);
    return 0;
}

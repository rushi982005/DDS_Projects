#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char x) {
    stack[++top] = x;
}
char pop() {
    return stack[top--];
}
int precedence(char x) {
    if(x == '+' || x == '-') return 1;
    if(x == '*' || x == '/') return 2;
    if(x == '^') return 3;
    return -1;
}
void infixToPostfix(char* exp, char* result) {
    int i, k = 0;
    for(i = 0; exp[i]; i++) {
        if(isdigit(exp[i])) result[k++] = exp[i];
        else if(exp[i] == '(') push(exp[i]);
        else if(exp[i] == ')') {
            while(top != -1 && stack[top] != '(')
                result[k++] = pop();
            pop(); // remove '('
        } else {
            while(top != -1 && precedence(stack[top]) >= precedence(exp[i]))
                result[k++] = pop();
            push(exp[i]);
        }
    }
    while(top != -1) result[k++] = pop();
    result[k] = '\0';
}
int evalPostfix(char* exp) {
    int s[MAX], st = -1, i;
    for(i=0; exp[i]; i++) {
        if(isdigit(exp[i])) s[++st] = exp[i]-'0';
        else {
            int b = s[st--];
            int a = s[st--];
            switch(exp[i]) {
                case '+': s[++st] = a+b; break;
                case '-': s[++st] = a-b; break;
                case '*': s[++st] = a*b; break;
                case '/': s[++st] = a/b; break;
                case '^': s[++st] = pow(a,b); break;
            }
        }
    }
    return s[st];
}
int main() {
    char exp[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", exp);
    infixToPostfix(exp, postfix);
    printf("Postfix: %s\n", postfix);
    printf("Result: %d\n", evalPostfix(postfix));
    return 0;
}

#include <iostream>
#include <cstring>
using namespace std;

class Stack {
private:
    struct Node {
        char data;
        Node* next;
    };

    Node* top;

public:
    Stack() {
        top = NULL;
    }

    ~Stack() {
        while (top != NULL) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(char x) {
        Node* newNode = new Node;
        newNode->data = x;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (top == NULL)
            return '\0';

        Node* temp = top;
        char x = top->data;
        top = top->next;
        delete temp;
        return x;
    }

    bool isEmpty() {
        return top == NULL;
    }

    int precedence(char op) {
        if (op == '*' || op == '/')
            return 2;
        if (op == '+' || op == '-')
            return 1;
        return 0;
    }

    void postfix() {
        char exp[100];
        char post[100];
        int j = 0;

        cout << "Enter infix expression: ";
        cin >> exp;

        for (int i = 0; exp[i] != '\0'; i++) {
            char ch = exp[i];

            if (ch == '(') {
                push(ch);
            }
            else if (isalnum(ch)) {
                post[j++] = ch;
            }
            else if (ch == ')') {
                while (!isEmpty() && top->data != '(')
                    post[j++] = pop();

                if (!isEmpty())
                    pop();
            }
            else {
                while (!isEmpty() &&
                       top->data != '(' &&
                       precedence(top->data) >= precedence(ch)) {
                    post[j++] = pop();
                }
                push(ch);
            }
        }

        while (!isEmpty())
            post[j++] = pop();

        post[j] = '\0';

        cout << "Postfix expression: " << post << endl;
    }
};

int main() {
    Stack st;
    int ch;

    do {
        cout << "\n1. Infix to Postfix";
        cout << "\n2. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                st.postfix();
                break;

            case 2:
                cout << "Exit\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (ch != 2);

    return 0;
}

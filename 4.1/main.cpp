#include "brackets.cpp"

int main() {
    string expr = "{()}[]";

    if (areBracketsBalanced(expr))
        cout << "Balanced";
    else
        cout << "Not Balanced";

    return 0;
}
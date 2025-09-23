#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Function f(x) = e^x - 3x
double f(double x) {
    return exp(x) - 3*x;
}

/* ================= Main Program ================= */
int main() {
    double x1, x2, tol;
    int maxIter = 50;

    cout << "Enter guess-1, guess-2 and error tolerance: ";
    cin >> x1 >> x2 >> tol;

    int iterFalsePos, iterSecant;

    double root1 = modifiedFalsePosition(x1, x2, tol, maxIter, iterFalsePos);
    double root2 = secant(x1, x2, tol, maxIter, iterSecant);

    cout << "\n==================== Comparison ====================\n";
    cout << "Modified False Position converged in " << iterFalsePos << " iterations.\n";
    cout << "Secant Method converged in " << iterSecant << " iterations.\n";

    if (iterFalsePos < iterSecant)
        cout << ">> Modified False Position converged faster.\n";
    else if (iterSecant < iterFalsePos)
        cout << ">> Secant Method converged faster.\n";
    else
        cout << ">> Both methods converged in the same number of iterations.\n";

    return 0;
}

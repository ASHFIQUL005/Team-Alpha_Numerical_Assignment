#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Function f(x) = e^x - 3x
double f(double x) {
    return exp(x) - 3*x;
}

/* ================= Modified False Position Method ================= */
double modifiedFalsePosition(double x1, double x2, double tol, int maxIter, int &iterCount) {
        if (f(x1) * f(x2) > 0) {
        cout << "Wrong guesses! f(x1) and f(x2) must have opposite signs." << endl;
        return NAN;
    }

    double x0 = x1;
    double f0;
    double f1 = f(x1), f2 = f(x2);

    cout << "\n--- Modified False Position Method ---\n";
    cout << left << setw(6) << "Iter"
         << setw(12) << "x1"
         << setw(12) << "x2"
         << setw(12) << "x0"
         << setw(12) << "f(x0)"
         << setw(12) << "f(x1)"
         << setw(12) << "f(x2)"
         << setw(16) << "Relative Error" << endl;

    for (iterCount = 1; iterCount <= maxIter; iterCount++) {
        double x_new = (x1*f2 - x2*f1) / (f2 - f1);
        f0 = f(x_new);
        double rel_error = fabs(x_new - x0) / fabs(x_new);

        cout << left << setw(6) << iterCount
             << setw(12) << x1
             << setw(12) << x2
             << setw(12) << x_new
             << setw(12) << f0
             << setw(12) << f1
             << setw(12) << f2
             << setw(16) << rel_error << endl;

        if (fabs(f0) < tol || rel_error < tol) {
            cout << "\nRoot (Modified False Position) = " << x_new
                 << " after " << iterCount << " iterations.\n";
            return x_new;
        }

        if (f1 * f0 < 0) {
            x2 = x_new;
            f2 = f0 / 2;   // update trick
        } else {
            x1 = x_new;
            f1 = f0 / 2;
        }

        x0 = x_new;
    }

    cout << "Max iterations reached in Modified False Position.\n";

    return x0;
}
/* ================= Secant Method ================= */
double secant(double x1, double x2, double tol, int maxIter, int &iterCount) {
        double f1 = f(x1), f2 = f(x2);
    double x0;

    cout << "\n--- Secant Method ---\n";
    cout << left << setw(6) << "Iter"
         << setw(12) << "x1"
         << setw(12) << "x2"
         << setw(12) << "f1"
         << setw(12) << "f2"
         << setw(12) << "x0"
         << setw(12) << "f(x0)"
         << setw(20) << "Relative error" << endl;

    for (iterCount = 1; iterCount <= maxIter; iterCount++) {
        if (fabs(f2 - f1) < 1e-12) {
            cout << "Division by zero risk!" << endl;
            return NAN;
        }

        x0 = x2 - f2 * (x2 - x1) / (f2 - f1);
        double f0 = f(x0);
        double error = fabs(x0 - x2) / fabs(x0);

        cout << left << setw(6) << iterCount
             << setw(12) << x1
             << setw(12) << x2
             << setw(12) << f1
             << setw(12) << f2
             << setw(12) << x0
             << setw(12) << f0
             << setw(20) << error << endl;

        if (fabs(f0) < tol || error < tol) {
            cout << "\nRoot (Secant Method) = " << x0
                 << " after " << iterCount << " iterations.\n";
            return x0;
        }

        // update
        x1 = x2; f1 = f2;
        x2 = x0; f2 = f0;
    }

    cout << "Max iterations reached in Secant Method.\n";

    return x0;
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



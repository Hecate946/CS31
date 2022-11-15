#include <string>
#include <iostream>
using namespace std;

int main() {

    // Define constant tax rates.
    const double HIGH_TAX_RATE = 0.093;
    const double MEDIUM_TAX_RATE = 0.07;
    const double NURSE_TEACHER_TAX_RATE = 0.05;
    const double LOW_TAX_RATE = 0.04;

    // Define variables that will be used to store user input.
    string name;
    double taxable_income;
    string occupation;
    int children;

    // Ask for name
    cout << "Name: ";
    getline(cin, name);
    if (name == "") { // Invalid input received
        cout << "---" << endl;
        cout << "You must enter a name" << endl; // Send error
        return 1; // Quit program
    }


    cout << "Taxable income: ";
    cin >> taxable_income;
    if (taxable_income < 0) { // Invalid input received
        cout << "---" << endl;
        cout << "The taxable income must not be negative" << endl; // Send error
        return 1; // Quit program
    }

    cin.ignore(); // flush cin so getline won't ignore the occupation
    cout << "Occupation: ";
    getline(cin, occupation);
    if (occupation == "") { // Invalid input received
        cout << "---" << endl;
        cout << "You must enter an occupation" << endl; // Send error
        return 1; // Quit program
    }

    cout << "Number of children: ";
    cin >> children;
    if (children < 0) { // Invalid input received
        cout << "---" << endl;
        cout << "The number of children must not be negative" << endl; // Send error
        return 1; // Quit program
    }   


    double tax = 0; // This will be the tax value that'll be changed as we go through different cases.
    bool child_discount = true; // Set child discount to true
    if (taxable_income > 125000) {
        child_discount = false; // they make more than 125000, no child discount.

        double remainder = taxable_income - 125000;
        tax += remainder * HIGH_TAX_RATE; // All money more than 125000 gets taxed
        taxable_income = 125000; // This is now the remaining income that hasn't been taxed.
    }
    if (taxable_income > 55000) {
        // Set medium_tax_rate based on occupation.
        double medium_tax_rate;
        if (occupation == "nurse" || occupation == "teacher")
            medium_tax_rate = NURSE_TEACHER_TAX_RATE;
        else
            medium_tax_rate = MEDIUM_TAX_RATE;

        double remainder = taxable_income - 55000;
        tax += remainder * medium_tax_rate; // All money more than 55000 gets taxed
        taxable_income = 55000; // This is now the remaining income that hasn't been taxed.
    }

    tax += taxable_income * LOW_TAX_RATE;

    if (child_discount == true) {
        tax -= children * 200; // subtract 200 dollars per child from tax bill.
        tax = (tax >= 0) ? tax : 0; // Use single line if/else to set tax to zero if tax is negative.
    }

    // Set cout precision to 2 places past the decimal point.
    cout.setf(ios::fixed);
    cout.precision(2);

    cout << "---" << endl << name << " would pay $" << tax << endl;
}


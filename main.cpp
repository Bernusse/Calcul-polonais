/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <stack>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

string saisie() {
    ifstream f("calcul.txt");
    if (!f) throw runtime_error("Erreur : fichier introuvable");
    string expr, ligne;
    while (getline(f, ligne)) expr += ligne + " ";
    if (expr.empty()) throw runtime_error("Erreur : fichier vide");
    return expr;
}


double operation(double a, double b, const string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw runtime_error("Erreur: division par zéro");
        return a / b;
    }
    throw runtime_error("Erreur: opérateur inconnu " + op);
}


double calcul(const string& expr) {
    stack<double> s; stringstream ss(expr); string t;
    while (ss >> t) {
        if (isdigit(t[0]) || (t.size()>1 && isdigit(t[1]))) { s.push(stod(t)); continue; }
        if (s.size() < 2) throw runtime_error("Erreur: opérande manquante");
        double b=s.top(); s.pop(); double a=s.top(); s.pop();
        s.push(operation(a,b,t));
    }
    if (s.size()!=1) throw runtime_error("Erreur: expression invalide");
    return s.top();
}

void erreur(const string& msg) {
    cerr << "[ERREUR] " << msg << endl;
    cerr << "Vérifiez votre fichier 'calcul.txt' ou votre expression." << endl;
}

int main() {
    try {
        string expr = saisie();
        cout << "Expression: " << expr << endl;
        cout << "Résultat = " << calcul(expr) << endl;
    } catch (exception& e) {
        erreur(e.what());
    }
}

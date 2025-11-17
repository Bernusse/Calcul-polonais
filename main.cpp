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


double operation(double operandeGauche, double operandeDroite, const string& operateur) {
    if (operateur == "+") return operandeGauche + operandeDroite;
    if (operateur == "-") return operandeGauche - operandeDroite;
    if (operateur == "*") return operandeGauche * operandeDroite;
    if (operateur == "/") {
        if (abs(operandeDroite) < 0.00000000001
        ) throw runtime_error("Division par zéro");
        return operandeGauche / operandeDroite;
    }
    throw runtime_error("Opérateur inconnu : " + operateur);
}

double calcul(const string& expr) {
    stack<double> pile; stringstream flux(expr); string jeton;
    while (flux >> jeton) {
        if (isdigit(jeton[0]) || (jeton.size()>1 && isdigit(jeton[1]))) { pile.push(stod(jeton)); continue; }
        if (pile.size() < 2) throw runtime_error("Erreur: opérande manquante");
        double operandeDroite=pile.top(); pile.pop(); double operandeGauche=pile.top(); pile.pop();
        pile.push(operation(operandeGauche,operandeDroite,jeton));
    }
    if (pile.size()!=1) throw runtime_error("Erreur: expression invalide");
    return pile.top();
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



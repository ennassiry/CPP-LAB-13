
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <exception>

using namespace std;

// ==========================================
// 1. EXCEPTION StackOverflow
// ==========================================

class StackOverflow : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Erreur : la pile est pleine !";
    }
};

// ==========================================
// 2. EXCEPTION StackUnderflow
// ==========================================

class StackUnderflow : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Erreur : la pile est vide !";
    }
};

// ==========================================
// 3. CLASSE GENERIQUE Stack<T>
// ==========================================

template <typename T>
class Stack
{
private:

    // Tableau dynamique intelligent
    unique_ptr<T[]> data;

    // Capacite maximale
    size_t capacity;

    // Nombre d'elements dans la pile
    size_t top;

public:

    // ======================================
    // 4. CONSTRUCTEUR PAR DEFAUT
    // ======================================

    Stack(size_t c = 100)
        : data(c > 0 ? make_unique<T[]>(c) : nullptr),
          capacity(c),
          top(0)
    {
    }

    // ======================================
    // 5. CONSTRUCTEUR AVEC ITERATEURS
    // ======================================

    template <typename Iterator>
    Stack(Iterator debut, Iterator fin)
        : capacity(0), top(0)
    {
        // Calculer le nombre d'elements
        auto n = distance(debut, fin);

        if (n < 0)
        {
            throw invalid_argument("Intervalle invalide !");
        }

        capacity = static_cast<size_t>(n);

        // Allocation de la memoire
        if (capacity > 0)
        {
            data = make_unique<T[]>(capacity);
        }

        // Copier les elements dans la pile
        for (Iterator it = debut; it != fin; ++it)
        {
            push(*it);
        }
    }

    // ======================================
    // 6. PUSH : AJOUTER UN ELEMENT
    // ======================================

    void push(const T& valeur)
    {
        if (top >= capacity)
        {
            throw StackOverflow();
        }

        data[top] = valeur;

        top++;
    }

    // ======================================
    // 7. POP : SUPPRIMER LE SOMMET
    // ======================================

    void pop()
    {
        if (top == 0)
        {
            throw StackUnderflow();
        }

        top--;
    }

    // ======================================
    // 8. PEEK : CONSULTER LE SOMMET
    // ======================================

    const T& peek() const
    {
        if (top == 0)
        {
            throw StackUnderflow();
        }

        return data[top - 1];
    }

    // ======================================
    // 9. EMPTY : VERIFIER SI LA PILE EST VIDE
    // ======================================

    bool empty() const
    {
        return top == 0;
    }

    // ======================================
    // 10. GETTERS
    // ======================================

    size_t size() const
    {
        return top;
    }

    size_t getCapacity() const
    {
        return capacity;
    }
};


// ==========================================
// 11. CLASSE MAISON : ETUDIANT
// ==========================================

class Etudiant
{
private:

    string nom;
    int age;

public:

    Etudiant(string n = "", int a = 0)
        : nom(n), age(a)
    {
    }

    void afficher() const
    {
        cout << "Nom : " << nom
             << " | Age : " << age << endl;
    }
};


// ==========================================
// 12. PROGRAMME PRINCIPAL
// ==========================================

int main()
{
    // --------------------------------------
    // TEST 1 : STACK<int>
    // --------------------------------------

    cout << "===== TEST STACK<int> =====" << endl;

    Stack<int> pile(5);

    pile.push(10);
    pile.push(20);
    pile.push(30);

    cout << "Sommet : " << pile.peek() << endl;
    cout << "Taille : " << pile.size() << endl;

    pile.pop();

    cout << "Apres pop : " << pile.peek() << endl;


    // --------------------------------------
    // TEST 2 : STACK<string>
    // --------------------------------------

    cout << "\n===== TEST STACK<string> =====" << endl;

    Stack<string> noms(3);

    noms.push("Ahmed");
    noms.push("Youssef");
    noms.push("Mohamed");

    cout << "Sommet : " << noms.peek() << endl;

    noms.pop();

    cout << "Apres pop : " << noms.peek() << endl;


    // --------------------------------------
    // TEST 3 : STACK<Etudiant>
    // --------------------------------------

    cout << "\n===== TEST STACK<Etudiant> =====" << endl;

    Stack<Etudiant> etudiants(3);

    etudiants.push(Etudiant("Ali", 20));
    etudiants.push(Etudiant("Sara", 21));
    etudiants.push(Etudiant("Omar", 22));

    cout << "Etudiant au sommet :" << endl;

    etudiants.peek().afficher();


    // --------------------------------------
    // TEST 4 : CONSTRUCTEUR AVEC ITERATEURS
    // --------------------------------------

    cout << "\n===== TEST CONSTRUCTEUR ITERATEURS =====" << endl;

    vector<int> valeurs = {10, 20, 30, 40, 50};

    // Initialiser la pile depuis un vector
    Stack<int> pile2(valeurs.begin(), valeurs.end());

    cout << "Taille : " << pile2.size() << endl;

    cout << "Elements dans l'ordre LIFO :" << endl;

    while (!pile2.empty())
    {
        cout << pile2.peek() << " ";
        pile2.pop();
    }

    cout << endl;


    // --------------------------------------
    // TEST 5 : STACKOVERFLOW
    // --------------------------------------

    cout << "\n===== TEST STACKOVERFLOW =====" << endl;

    try
    {
        Stack<int> petitePile(2);

        petitePile.push(100);
        petitePile.push(200);

        // La pile est pleine
        petitePile.push(300);
    }
    catch (const StackOverflow& e)
    {
        cout << e.what() << endl;
    }


    // --------------------------------------
    // TEST 6 : STACKUNDERFLOW
    // --------------------------------------

    cout << "\n===== TEST STACKUNDERFLOW =====" << endl;

    try
    {
        Stack<int> pileVide(3);

        // Impossible de retirer un element
        pileVide.pop();
    }
    catch (const StackUnderflow& e)
    {
        cout << e.what() << endl;
    }


    // --------------------------------------
    // TEST 7 : PEEK SUR UNE PILE VIDE
    // --------------------------------------

    cout << "\n===== TEST PEEK VIDE =====" << endl;

    try
    {
        Stack<int> p;

        cout << p.peek() << endl;
    }
    catch (const StackUnderflow& e)
    {
        cout << e.what() << endl;
    }


    // --------------------------------------
    // TEST 8 : GROS NOMBRE D'ELEMENTS
    // --------------------------------------

    cout << "\n===== TEST 100000 ELEMENTS =====" << endl;

    {
        Stack<int> grandePile(100000);

        for (int i = 1; i <= 100000; i++)
        {
            grandePile.push(i);
        }

        cout << "Nombre d'elements : "
             << grandePile.size() << endl;

        cout << "Sommet : "
             << grandePile.peek() << endl;

        // Suppression de tous les elements
        while (!grandePile.empty())
        {
            grandePile.pop();
        }

        cout << "Pile vide : "
             << (grandePile.empty() ? "Oui" : "Non")
             << endl;
    }

    cout << "\nFin du programme !" << endl;

    return 0;
}

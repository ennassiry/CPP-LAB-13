
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// ==========================================
// 1. CLASSE GENERIQUE ArrayDyn<T>
// ==========================================

template <typename T>
class ArrayDyn
{
private:
    T* elements;          // Tableau dynamique
    size_t capacite;      // Capacite maximale
    size_t taille;        // Nombre d'elements stockes

    // Agrandir le tableau lorsque necessaire
    void agrandir()
    {
        size_t nouvelleCapacite;

        if (capacite == 0)
            nouvelleCapacite = 1;
        else
            nouvelleCapacite = capacite * 2;

        T* nouveau = new T[nouvelleCapacite];

        for (size_t i = 0; i < taille; i++)
        {
            nouveau[i] = elements[i];
        }

        delete[] elements;

        elements = nouveau;
        capacite = nouvelleCapacite;
    }

public:

    // ======================================
    // 2. CONSTRUCTEUR PAR DEFAUT
    // ======================================

    ArrayDyn()
    {
        elements = nullptr;
        capacite = 0;
        taille = 0;
    }

    // ======================================
    // 3. CONSTRUCTEUR AVEC CAPACITE
    // ======================================

    ArrayDyn(size_t c)
    {
        capacite = c;
        taille = 0;

        if (capacite > 0)
            elements = new T[capacite];
        else
            elements = nullptr;
    }

    // ======================================
    // 4. CONSTRUCTEUR DE COPIE
    // ======================================

    ArrayDyn(const ArrayDyn<T>& autre)
    {
        capacite = autre.capacite;
        taille = autre.taille;

        if (capacite > 0)
        {
            elements = new T[capacite];

            for (size_t i = 0; i < taille; i++)
            {
                elements[i] = autre.elements[i];
            }
        }
        else
        {
            elements = nullptr;
        }
    }

    // ======================================
    // 5. OPERATEUR D'AFFECTATION
    // ======================================

    ArrayDyn<T>& operator=(const ArrayDyn<T>& autre)
    {
        // Eviter l'auto-affectation
        if (this != &autre)
        {
            T* nouveau = nullptr;

            if (autre.capacite > 0)
            {
                nouveau = new T[autre.capacite];

                for (size_t i = 0; i < autre.taille; i++)
                {
                    nouveau[i] = autre.elements[i];
                }
            }

            delete[] elements;

            elements = nouveau;
            capacite = autre.capacite;
            taille = autre.taille;
        }

        return *this;
    }

    // ======================================
    // 6. DESTRUCTEUR
    // ======================================

    ~ArrayDyn()
    {
        delete[] elements;
    }

    // ======================================
    // 7. PUSH_BACK
    // ======================================

    void push_back(const T& valeur)
    {
        // Si le tableau est plein
        if (taille == capacite)
        {
            agrandir();
        }

        elements[taille] = valeur;
        taille++;
    }

    // ======================================
    // 8. POP_BACK
    // ======================================

    void pop_back()
    {
        if (taille == 0)
        {
            throw out_of_range("Le tableau est vide !");
        }

        taille--;
    }

    // ======================================
    // 9. OPERATEUR []
    // ======================================

    T& operator[](size_t indice)
    {
        if (indice >= taille)
        {
            throw out_of_range("Indice hors limites !");
        }

        return elements[indice];
    }

    // Version constante de operator[]
    const T& operator[](size_t indice) const
    {
        if (indice >= taille)
        {
            throw out_of_range("Indice hors limites !");
        }

        return elements[indice];
    }

    // ======================================
    // 10. GETTERS
    // ======================================

    size_t getTaille() const
    {
        return taille;
    }

    size_t getCapacite() const
    {
        return capacite;
    }

    bool empty() const
    {
        return taille == 0;
    }

    // ======================================
    // 11. CLASSE ITERATOR
    // ======================================

    class Iterator
    {
    private:
        T* ptr;

    public:

        // Constructeur
        Iterator(T* p = nullptr)
        {
            ptr = p;
        }

        // Acceder a l'element
        T& operator*() const
        {
            return *ptr;
        }

        // Incrementer : element suivant
        Iterator& operator++()
        {
            ptr++;
            return *this;
        }

        // Decrementer : element precedent
        Iterator& operator--()
        {
            ptr--;
            return *this;
        }

        // Comparer deux iterateurs
        bool operator!=(const Iterator& autre) const
        {
            return ptr != autre.ptr;
        }
    };

    // ======================================
    // 12. BEGIN ET END
    // ======================================

    Iterator begin()
    {
        return Iterator(elements);
    }

    Iterator end()
    {
        return Iterator(elements + taille);
    }
};


// ==========================================
// 13. CLASSE MAISON : ETUDIANT
// ==========================================

class Etudiant
{
private:
    string nom;
    int age;

public:

    Etudiant(string n = "", int a = 0)
    {
        nom = n;
        age = a;
    }

    void afficher() const
    {
        cout << "Nom : " << nom
             << " | Age : " << age << endl;
    }
};


// ==========================================
// 14. PROGRAMME PRINCIPAL
// ==========================================

int main()
{
    // --------------------------------------
    // TEST 1 : ArrayDyn<int>
    // --------------------------------------

    cout << "===== TEST DES ENTIERS =====" << endl;

    ArrayDyn<int> nombres;

    nombres.push_back(10);
    nombres.push_back(20);
    nombres.push_back(30);
    nombres.push_back(40);

    // Parcours avec range-based for
    for (auto& e : nombres)
    {
        cout << e << " ";
    }

    cout << endl;

    cout << "Taille : " << nombres.getTaille() << endl;
    cout << "Capacite : " << nombres.getCapacite() << endl;

    // Modification avec operator[]
    nombres[0] = 100;

    cout << "Premier element : " << nombres[0] << endl;


    // --------------------------------------
    // TEST 2 : ArrayDyn<string>
    // --------------------------------------

    cout << "\n===== TEST DES STRINGS =====" << endl;

    ArrayDyn<string> noms(2);

    noms.push_back("Ahmed");
    noms.push_back("Youssef");
    noms.push_back("Mohamed");

    for (auto& e : noms)
    {
        cout << e << endl;
    }


    // --------------------------------------
    // TEST 3 : ArrayDyn<Etudiant>
    // --------------------------------------

    cout << "\n===== TEST DES ETUDIANTS =====" << endl;

    ArrayDyn<Etudiant> etudiants;

    etudiants.push_back(Etudiant("Ali", 20));
    etudiants.push_back(Etudiant("Sara", 21));
    etudiants.push_back(Etudiant("Omar", 22));

    for (auto& e : etudiants)
    {
        e.afficher();
    }


    // --------------------------------------
    // TEST 4 : CONSTRUCTEUR DE COPIE
    // --------------------------------------

    cout << "\n===== TEST CONSTRUCTEUR DE COPIE =====" << endl;

    ArrayDyn<int> copie(nombres);

    for (auto& e : copie)
    {
        cout << e << " ";
    }

    cout << endl;


    // --------------------------------------
    // TEST 5 : OPERATEUR D'AFFECTATION
    // --------------------------------------

    cout << "\n===== TEST AFFECTATION =====" << endl;

    ArrayDyn<int> tableau2;

    tableau2 = nombres;

    for (auto& e : tableau2)
    {
        cout << e << " ";
    }

    cout << endl;


    // --------------------------------------
    // TEST 6 : POP_BACK
    // --------------------------------------

    cout << "\n===== TEST POP_BACK =====" << endl;

    nombres.pop_back();

    for (auto& e : nombres)
    {
        cout << e << " ";
    }

    cout << endl;


    // --------------------------------------
    // TEST 7 : CONTROLE DES BORNES
    // --------------------------------------

    cout << "\n===== TEST DES EXCEPTIONS =====" << endl;

    try
    {
        cout << nombres[100] << endl;
    }
    catch (const out_of_range& e)
    {
        cout << "Erreur : " << e.what() << endl;
    }

    return 0;
}

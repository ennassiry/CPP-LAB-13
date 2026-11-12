
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <concepts>
#include <cassert>
#include <utility>

using namespace std;

// ==========================================
// 1. CONCEPT SORTABLE
// ==========================================

template <typename T>
concept Sortable = requires(T a, T b)
{
    { a < b } -> convertible_to<bool>;
};


// ==========================================
// 2. FONCTEUR ASC : TRI CROISSANT
// ==========================================

struct Asc
{
    template <typename T>
    bool operator()(const T& a, const T& b) const
    {
        return a < b;
    }
};


// ==========================================
// 3. FONCTEUR DESC : TRI DECROISSANT
// ==========================================

struct Desc
{
    template <typename T>
    bool operator()(const T& a, const T& b) const
    {
        return b < a;
    }
};


// ==========================================
// 4. FONCTION DE PARTITIONNEMENT
// ==========================================

template <Sortable T, typename Comp>
ptrdiff_t partitionner(
    vector<T>& tab,
    ptrdiff_t debut,
    ptrdiff_t fin,
    Comp comp)
{
    // Choisir le dernier element comme pivot
    T pivot = tab[fin];

    // Position des elements plus petits
    ptrdiff_t i = debut;

    for (ptrdiff_t j = debut; j < fin; j++)
    {
        if (comp(tab[j], pivot))
        {
            swap(tab[i], tab[j]);
            i++;
        }
    }

    // Placer le pivot a sa position correcte
    swap(tab[i], tab[fin]);

    return i;
}


// ==========================================
// 5. FONCTION QUICK SORT RECURSIVE
// ==========================================

template <Sortable T, typename Comp>
void quickSortRec(
    vector<T>& tab,
    ptrdiff_t debut,
    ptrdiff_t fin,
    Comp comp)
{
    if (debut < fin)
    {
        // Partitionner le tableau
        ptrdiff_t pivot = partitionner(
            tab, debut, fin, comp
        );

        // Trier la partie gauche
        quickSortRec(
            tab, debut, pivot - 1, comp
        );

        // Trier la partie droite
        quickSortRec(
            tab, pivot + 1, fin, comp
        );
    }
}


// ==========================================
// 6. FONCTION QUICK SORT PRINCIPALE
// ==========================================

template <
    Sortable T,
    typename Comp = less<T>
>
void quickSort(
    vector<T>& tab,
    Comp comp = Comp{})
{
    // Verifier si le vecteur est vide
    if (tab.empty())
        return;

    quickSortRec(
        tab,
        0,
        static_cast<ptrdiff_t>(tab.size()) - 1,
        comp
    );
}


// ==========================================
// 7. STRUCTURE UTILISATEUR : ETUDIANT
// ==========================================

struct Etudiant
{
    string nom;
    int age;

    Etudiant(string n, int a)
        : nom(n), age(a)
    {
    }

    // Surcharge de l'operateur <
    // Comparaison selon l'age
    bool operator<(const Etudiant& autre) const
    {
        return age < autre.age;
    }
};


// ==========================================
// 8. FONCTIONS D'AFFICHAGE
// ==========================================

template <typename T>
void afficher(const vector<T>& tab)
{
    for (const T& element : tab)
    {
        cout << element << " ";
    }

    cout << endl;
}


// Affichage special pour Etudiant
void afficherEtudiants(const vector<Etudiant>& tab)
{
    for (const Etudiant& e : tab)
    {
        cout << e.nom << " (" << e.age << " ans) ";
    }

    cout << endl;
}


// ==========================================
// 9. PROGRAMME PRINCIPAL
// ==========================================

int main()
{
    // --------------------------------------
    // TEST 1 : VECTOR<int>
    // --------------------------------------

    cout << "===== TEST DES ENTIERS =====" << endl;

    vector<int> nombres = {8, 3, 6, 1, 5, 9, 2};

    cout << "Avant le tri : ";
    afficher(nombres);

    // Tri croissant
    quickSort(nombres, Asc{});

    cout << "Tri croissant : ";
    afficher(nombres);

    // Test unitaire
    assert(is_sorted(nombres.begin(), nombres.end()));

    cout << "Test croissant : OK" << endl;

    // Tri decroissant
    quickSort(nombres, Desc{});

    cout << "Tri decroissant : ";
    afficher(nombres);

    // Test unitaire
    assert(is_sorted(
        nombres.begin(),
        nombres.end(),
        Desc{}
    ));

    cout << "Test decroissant : OK" << endl;


    // --------------------------------------
    // TEST 2 : VECTOR<string>
    // --------------------------------------

    cout << "\n===== TEST DES STRINGS =====" << endl;

    vector<string> mots = {
        "Orange",
        "Banane",
        "Pomme",
        "Abricot",
        "Cerise"
    };

    cout << "Avant le tri : ";
    afficher(mots);

    // Tri alphabetique
    quickSort(mots, Asc{});

    cout << "Tri alphabetique : ";
    afficher(mots);

    assert(is_sorted(mots.begin(), mots.end()));

    cout << "Test alphabetique : OK" << endl;

    // Tri alphabetique inverse
    quickSort(mots, Desc{});

    cout << "Tri inverse : ";
    afficher(mots);

    assert(is_sorted(
        mots.begin(),
        mots.end(),
        Desc{}
    ));

    cout << "Test inverse : OK" << endl;


    // --------------------------------------
    // TEST 3 : VECTOR<Etudiant>
    // --------------------------------------

    cout << "\n===== TEST DES ETUDIANTS =====" << endl;

    vector<Etudiant> etudiants = {
        Etudiant("Ali", 22),
        Etudiant("Sara", 19),
        Etudiant("Omar", 25),
        Etudiant("Youssef", 20)
    };

    cout << "Avant le tri :" << endl;
    afficherEtudiants(etudiants);

    // Tri par age croissant
    quickSort(etudiants, Asc{});

    cout << "\nTri par age croissant :" << endl;
    afficherEtudiants(etudiants);

    // Verification
    assert(is_sorted(
        etudiants.begin(),
        etudiants.end()
    ));

    cout << "Test Etudiant : OK" << endl;


    // --------------------------------------
    // TEST 4 : COMPARATEUR PAR DEFAUT
    // --------------------------------------

    cout << "\n===== TEST COMPARATEUR PAR DEFAUT =====" << endl;

    vector<int> valeurs = {9, 4, 7, 2, 1, 8};

    // Utilisation de std::less<int> automatiquement
    quickSort(valeurs);

    afficher(valeurs);

    assert(is_sorted(valeurs.begin(), valeurs.end()));

    cout << "Test comparateur par defaut : OK" << endl;


    // --------------------------------------
    // TEST 5 : VECTEUR VIDE
    // --------------------------------------

    cout << "\n===== TEST VECTEUR VIDE =====" << endl;

    vector<int> vide;

    quickSort(vide, Asc{});

    assert(vide.empty());

    cout << "Test vecteur vide : OK" << endl;


    // --------------------------------------
    // RESULTAT FINAL
    // --------------------------------------

    cout << "\nTous les tests sont reussis !" << endl;

    return 0;
}

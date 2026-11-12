
#include <iostream>
using namespace std;

// ==========================================
// 1. CLASSE GENERIQUE Matrice<T, N, M>
// ==========================================

template <typename T, int N, int M>
class Matrice
{
private:

    // Tableau statique de N lignes et M colonnes
    T data[N][M];

public:

    // ======================================
    // 2. CONSTRUCTEUR PAR DEFAUT
    // ======================================

    Matrice()
    {
        // Initialiser tous les elements a 0
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                data[i][j] = 0;
            }
        }
    }

    // ======================================
    // 3. CONSTRUCTEUR AVEC LISTE D'INITIALISATION
    // ======================================

    Matrice(const T valeurs[N][M])
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                data[i][j] = valeurs[i][j];
            }
        }
    }

    // ======================================
    // 4. ACCES AUX ELEMENTS
    // ======================================

    T& operator()(int i, int j)
    {
        return data[i][j];
    }

    const T& operator()(int i, int j) const
    {
        return data[i][j];
    }

    // ======================================
    // 5. OPERATEUR +
    // Addition de deux matrices
    // ======================================

    Matrice<T, N, M> operator+(const Matrice<T, N, M>& autre) const
    {
        Matrice<T, N, M> resultat;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                resultat.data[i][j] =
                    data[i][j] + autre.data[i][j];
            }
        }

        return resultat;
    }

    // ======================================
    // 6. OPERATEUR -
    // Soustraction de deux matrices
    // ======================================

    Matrice<T, N, M> operator-(const Matrice<T, N, M>& autre) const
    {
        Matrice<T, N, M> resultat;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                resultat.data[i][j] =
                    data[i][j] - autre.data[i][j];
            }
        }

        return resultat;
    }

    // ======================================
    // 7. OPERATEUR *
    // Produit matriciel
    // ======================================

    template <int P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const
    {
        Matrice<T, N, P> resultat;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < P; j++)
            {
                for (int k = 0; k < M; k++)
                {
                    resultat(i, j) +=
                        data[i][k] * autre(k, j);
                }
            }
        }

        return resultat;
    }

    // ======================================
    // 8. OPERATEUR << (AFFICHAGE)
    // ======================================

    friend ostream& operator<<(ostream& os, const Matrice<T, N, M>& mat)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                os << mat.data[i][j] << "\t";
            }

            os << endl;
        }

        return os;
    }
};


// ==========================================
// 9. PROGRAMME PRINCIPAL
// ==========================================

int main()
{
    // --------------------------------------
    // TEST 1 : MATRICES D'ENTIERS
    // --------------------------------------

    cout << "===== MATRICES D'ENTIERS =====" << endl;

    Matrice<int, 2, 2> A;
    Matrice<int, 2, 2> B;

    // Initialisation des elements
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;

    B(0, 0) = 5;
    B(0, 1) = 6;
    B(1, 0) = 7;
    B(1, 1) = 8;

    cout << "\nMatrice A :" << endl;
    cout << A;

    cout << "\nMatrice B :" << endl;
    cout << B;

    // Addition
    Matrice<int, 2, 2> C = A + B;

    cout << "\nA + B :" << endl;
    cout << C;

    // Soustraction
    Matrice<int, 2, 2> D = A - B;

    cout << "\nA - B :" << endl;
    cout << D;

    // Multiplication
    Matrice<int, 2, 2> E = A * B;

    cout << "\nA * B :" << endl;
    cout << E;


    // --------------------------------------
    // TEST 2 : MATRICES DE DOUBLE
    // --------------------------------------

    cout << "\n===== MATRICES DE DOUBLE =====" << endl;

    Matrice<double, 2, 2> X;
    Matrice<double, 2, 2> Y;

    X(0, 0) = 1.5;
    X(0, 1) = 2.5;
    X(1, 0) = 3.5;
    X(1, 1) = 4.5;

    Y(0, 0) = 2.0;
    Y(0, 1) = 1.0;
    Y(1, 0) = 0.5;
    Y(1, 1) = 3.0;

    cout << "\nMatrice X :" << endl;
    cout << X;

    cout << "\nMatrice Y :" << endl;
    cout << Y;

    Matrice<double, 2, 2> Z = X + Y;

    cout << "\nX + Y :" << endl;
    cout << Z;

    Matrice<double, 2, 2> W = X * Y;

    cout << "\nX * Y :" << endl;
    cout << W;


    // --------------------------------------
    // TEST 3 : MATRICES DE DIMENSIONS DIFFERENTES
    // --------------------------------------

    cout << "\n===== PRODUIT DE MATRICES 2x3 ET 3x2 =====" << endl;

    Matrice<int, 2, 3> F;
    Matrice<int, 3, 2> G;

    // F : 2 lignes et 3 colonnes
    F(0, 0) = 1;
    F(0, 1) = 2;
    F(0, 2) = 3;

    F(1, 0) = 4;
    F(1, 1) = 5;
    F(1, 2) = 6;

    // G : 3 lignes et 2 colonnes
    G(0, 0) = 7;
    G(0, 1) = 8;

    G(1, 0) = 9;
    G(1, 1) = 10;

    G(2, 0) = 11;
    G(2, 1) = 12;

    cout << "\nMatrice F :" << endl;
    cout << F;

    cout << "\nMatrice G :" << endl;
    cout << G;

    // Resultat : 2 lignes et 2 colonnes
    Matrice<int, 2, 2> H = F * G;

    cout << "\nF * G :" << endl;
    cout << H;

    return 0;
}

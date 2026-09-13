#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Algorithm 5:
    Match a new sequence z against reference haplotypes X.

    The PBWT index maintains:
        e = beginning of current match
        [f,g) = interval of matching reference haplotypes
*/

struct PBWT {

    int M;
    int N;

    vector<string> X;

    vector<vector<int>> a;
    vector<vector<int>> d;

    vector<int> c;

    vector<vector<int>> u;
    vector<vector<int>> v;
};


// ------------------------------------------------------------
// Build PBWT index
// ------------------------------------------------------------

void buildPBWT(PBWT &P) {

    int M = P.M;
    int N = P.N;

    P.a.resize(N + 1);
    P.d.resize(N + 1);

    P.c.resize(N);

    P.u.resize(N);
    P.v.resize(N);

    P.a[0].resize(M);
    P.d[0].assign(M, 0);

    for (int i = 0; i < M; i++)
        P.a[0][i] = i;

    for (int k = 0; k < N; k++) {

        vector<int> zero;
        vector<int> one;

        vector<int> dZero;
        vector<int> dOne;

        P.u[k].assign(M, 0);
        P.v[k].assign(M, 0);

        int p = k + 1;
        int q = k + 1;

        int zeroCount = 0;
        int oneCount = 0;

        for (int i = 0; i < M; i++) {

            int id = P.a[k][i];

            if (P.X[id][k] == '0') {

                P.u[k][i] = zeroCount;

                if (P.d[k][i] > p)
                    p = P.d[k][i];

                zero.push_back(id);
                dZero.push_back(p);

                zeroCount++;

                p = 0;
            }

            else {

                P.v[k][i] = oneCount;

                if (P.d[k][i] > q)
                    q = P.d[k][i];

                one.push_back(id);
                dOne.push_back(q);

                oneCount++;

                q = 0;
            }
        }

        P.c[k] = zeroCount;

        // a[k+1]
        P.a[k + 1].clear();

        for (int id : zero)
            P.a[k + 1].push_back(id);

        for (int id : one)
            P.a[k + 1].push_back(id);

        // d[k+1]
        P.d[k + 1].clear();

        for (int value : dZero)
            P.d[k + 1].push_back(value);

        for (int value : dOne)
            P.d[k + 1].push_back(value);
    }
}


// ------------------------------------------------------------
// Extension function w
// ------------------------------------------------------------

int w(
    const PBWT &P,
    int k,
    int i,
    int allele
) {

    if (i >= P.M)
        return P.M;

    if (allele == 0)
        return P.u[k][i];

    return P.c[k] + P.v[k][i];
}


// ------------------------------------------------------------
// Algorithm 5 query
// ------------------------------------------------------------

void matchQuery(
    const PBWT &P,
    const string &z
) {

    int M = P.M;
    int N = P.N;

    int e = 0;

    int f = 0;
    int g = M;

    cout << "\n====================================\n";
    cout << "ALGORITHM 5: QUERY MATCHING\n";
    cout << "====================================\n";

    cout << "Query: " << z << "\n";

    for (int k = 0; k < N; k++) {

        int allele = z[k] - '0';

        /*
            Map current interval [f,g)
            through the PBWT extension function.
        */

        int fNew = w(P, k, f, allele);
        int gNew = w(P, k, g, allele);

        if (fNew < gNew) {

            // Current match can be extended
            f = fNew;
            g = gNew;

            continue;
        }

        /*
            Existing interval cannot be extended.

            Report the current matching interval.
        */

        if (f < g) {

            cout << "\nMatch ending at position "
                 << k - 1 << ":\n";

            for (int i = f; i < g; i++) {

                cout << "Query <-> H"
                     << P.a[k][i]
                     << " | start = "
                     << e
                     << " | end = "
                     << k - 1
                     << "\n";
            }
        }

        /*
            Start a new matching interval.
        */

        e = k;

        f = fNew;
        g = gNew;
    }

    /*
        Report final interval.
    */

    if (f < g) {

        cout << "\nFinal match:\n";

        for (int i = f; i < g; i++) {

            cout << "Query <-> H"
                 << P.a[N][i]
                 << " | start = "
                 << e
                 << " | end = "
                 << N - 1
                 << "\n";
        }
    }
}


// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main() {

    PBWT P;

    cout << "Enter number of reference haplotypes (M): ";
    cin >> P.M;

    cout << "Enter number of sites (N): ";
    cin >> P.N;

    P.X.resize(P.M);

    cout << "\nEnter reference haplotypes:\n";

    for (int i = 0; i < P.M; i++) {

        cin >> P.X[i];

        if ((int)P.X[i].size() != P.N) {

            cout << "Error: invalid haplotype length.\n";
            return 1;
        }
    }

    string z;

    cout << "\nEnter query haplotype z:\n";
    cin >> z;

    if ((int)z.size() != P.N) {

        cout << "Error: query length must be "
             << P.N << ".\n";

        return 1;
    }

    // Build PBWT index
    buildPBWT(P);

    // Match query
    matchQuery(P, z);

    return 0;
}

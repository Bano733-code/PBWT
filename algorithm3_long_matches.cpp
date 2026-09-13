#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Algorithm 3: ReportLongMatches

    Reports haplotype pairs having a match
    of at least the specified minimum length L.
*/

int main() {

    int M, N, L;

    cout << "Enter number of haplotypes (M): ";
    cin >> M;

    cout << "Enter number of sites (N): ";
    cin >> N;

    vector<string> X(M);

    cout << "\nEnter haplotypes:\n";

    for (int i = 0; i < M; i++) {
        cin >> X[i];

        if ((int)X[i].size() != N) {
            cout << "Error: invalid haplotype length.\n";
            return 1;
        }
    }

    cout << "\nEnter minimum match length L: ";
    cin >> L;

    vector<int> a(M);
    vector<int> d(M, 0);

    for (int i = 0; i < M; i++)
        a[i] = i;

    cout << "\n====================================\n";
    cout << "ALGORITHM 3: LONG MATCHES\n";
    cout << "====================================\n";

    for (int k = 0; k < N; k++) {

        vector<int> zero;
        vector<int> one;

        vector<int> dZero;
        vector<int> dOne;

        int p = k + 1;
        int q = k + 1;

        // Build next a and d
        for (int i = 0; i < M; i++) {

            if (d[i] > p)
                p = d[i];

            if (d[i] > q)
                q = d[i];

            int id = a[i];

            if (X[id][k] == '0') {

                zero.push_back(id);
                dZero.push_back(p);

                p = 0;
            }
            else {

                one.push_back(id);
                dOne.push_back(q);

                q = 0;
            }
        }

        /*
            In PBWT order, neighboring haplotypes whose
            divergence is sufficiently old share a match
            of at least L sites.
        */

        for (int i = 1; i < M; i++) {

            int start = d[i];

            if (k - start + 1 >= L) {

                for (int j = i - 1; j >= 0; j--) {

                    if (d[i] <= d[j] &&
                        k - d[i] + 1 >= L) {

                        cout << "Match: H"
                             << a[i]
                             << " <-> H"
                             << a[j]
                             << " | start = "
                             << d[i]
                             << " | end = "
                             << k
                             << "\n";
                    }
                    else {
                        break;
                    }
                }
            }
        }

        // Update a
        a.clear();

        for (int id : zero)
            a.push_back(id);

        for (int id : one)
            a.push_back(id);

        // Update d
        d.clear();

        for (int value : dZero)
            d.push_back(value);

        for (int value : dOne)
            d.push_back(value);
    }

    return 0;
}

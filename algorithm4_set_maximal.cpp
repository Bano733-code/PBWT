#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Algorithm 4: ReportSetMaximalMatches

    Reports set-maximal matches using the PBWT
    prefix and divergence arrays.
*/

int main() {

    int M, N;

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

    vector<int> a(M);
    vector<int> d(M, 0);

    for (int i = 0; i < M; i++)
        a[i] = i;

    cout << "\n====================================\n";
    cout << "ALGORITHM 4: SET-MAXIMAL MATCHES\n";
    cout << "====================================\n";

    for (int k = 0; k < N; k++) {

        /*
            Examine neighboring PBWT intervals.

            A divergence value d[i] gives the beginning
            of the common match for neighboring sequences.
        */

        for (int i = 1; i < M; i++) {

            int start = d[i];

            if (start <= k) {

                bool extendableLeft = false;
                bool extendableRight = false;

                // Check left neighbor
                if (i > 0) {

                    int leftID = a[i - 1];
                    int currentID = a[i];

                    if (X[leftID][k] == X[currentID][k])
                        extendableLeft = true;
                }

                // Check right neighbor
                if (i + 1 < M) {

                    int rightID = a[i + 1];
                    int currentID = a[i];

                    if (X[rightID][k] == X[currentID][k])
                        extendableRight = true;
                }

                /*
                    If the match cannot be extended through
                    the current position, report it.
                */

                if (!extendableLeft && !extendableRight) {

                    cout << "Set-maximal match: H"
                         << a[i - 1]
                         << " <-> H"
                         << a[i]
                         << " | start = "
                         << start
                         << " | end = "
                         << k
                         << "\n";
                }
            }
        }

        // Build next PBWT ordering
        vector<int> zero;
        vector<int> one;

        vector<int> dZero;
        vector<int> dOne;

        int p = k + 1;
        int q = k + 1;

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

        a.clear();
        d.clear();

        for (int id : zero)
            a.push_back(id);

        for (int id : one)
            a.push_back(id);

        for (int value : dZero)
            d.push_back(value);

        for (int value : dOne)
            d.push_back(value);
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Algorithm 2: BuildPrefixAndDivergenceArrays

    Builds:
        a[k] = positional prefix ordering
        d[k] = divergence array
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
    cout << "ALGORITHM 2: PREFIX + DIVERGENCE\n";
    cout << "====================================\n";

    cout << "\na[0]: ";

    for (int id : a)
        cout << id << " ";

    cout << "\nd[0]: ";

    for (int value : d)
        cout << value << " ";

    cout << "\n";

    for (int k = 0; k < N; k++) {

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

        // New prefix ordering
        a.clear();

        for (int id : zero)
            a.push_back(id);

        for (int id : one)
            a.push_back(id);

        // New divergence array
        d.clear();

        for (int value : dZero)
            d.push_back(value);

        for (int value : dOne)
            d.push_back(value);

        cout << "\nPosition " << k << ":\n";

        cout << "a[" << k + 1 << "]: ";

        for (int id : a)
            cout << id << " ";

        cout << "\nd[" << k + 1 << "]: ";

        for (int value : d)
            cout << value << " ";

        cout << "\n";
    }

    return 0;
}

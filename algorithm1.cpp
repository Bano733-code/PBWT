#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    int M, N;

    cout << "Enter number of haplotypes (M): ";
    cin >> M;

    cout << "Enter number of positions (N): ";
    cin >> N;

    vector<string> x(M);

    cout << "\nEnter haplotypes:\n";

    for (int i = 0; i < M; i++) {
        cin >> x[i];

        if ((int)x[i].size() != N) {
            cout << "Invalid haplotype length.\n";
            return 1;
        }
    }

    // --------------------------------------------------
    // a = current prefix ordering
    // d = current divergence array
    // --------------------------------------------------

    vector<int> a(M);
    vector<int> d(M);

    // Initial ordering
    for (int i = 0; i < M; i++) {
        a[i] = i;
        d[i] = 0;
    }

    cout << "\n============================\n";
    cout << "PBWT PREFIX + DIVERGENCE\n";
    cout << "============================\n";

    cout << "\na[0]: ";
    for (int id : a)
        cout << id << " ";

    cout << "\nd[0]: ";
    for (int value : d)
        cout << value << " ";

    cout << "\n";

    // --------------------------------------------------
    // Sweep through positions
    // --------------------------------------------------

    for (int k = 0; k < N; k++) {

        vector<int> zero;
        vector<int> one;

        vector<int> dZero;
        vector<int> dOne;

        int p = k + 1;
        int q = k + 1;

        // --------------------------------------------------
        // Algorithm 2
        // --------------------------------------------------

        for (int i = 0; i < M; i++) {

            // Update p and q using previous divergence
            if (d[i] > p)
                p = d[i];

            if (d[i] > q)
                q = d[i];

            int haplotypeIndex = a[i];

            // --------------------------------------------------
            // Current allele = 0
            // --------------------------------------------------

            if (x[haplotypeIndex][k] == '0') {

                zero.push_back(haplotypeIndex);

                dZero.push_back(p);

                p = 0;
            }

            // --------------------------------------------------
            // Current allele = 1
            // --------------------------------------------------

            else {

                one.push_back(haplotypeIndex);

                dOne.push_back(q);

                q = 0;
            }
        }

        // --------------------------------------------------
        // New a[k+1]
        // --------------------------------------------------

        a.clear();

        for (int id : zero)
            a.push_back(id);

        for (int id : one)
            a.push_back(id);

        // --------------------------------------------------
        // New d[k+1]
        // --------------------------------------------------

        d.clear();

        for (int value : dZero)
            d.push_back(value);

        for (int value : dOne)
            d.push_back(value);

        // --------------------------------------------------
        // Display
        // --------------------------------------------------

        cout << "\nPosition k = " << k << "\n";

        cout << "a[" << k + 1 << "]: ";

        for (int id : a)
            cout << id << " ";

        cout << "\n";

        cout << "d[" << k + 1 << "]: ";

        for (int value : d)
            cout << value << " ";

        cout << "\n";
    }

    return 0;
}

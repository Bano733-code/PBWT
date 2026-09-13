#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Algorithm 1: BuildPrefixArray

    Input:
        M haplotypes of length N

    Output:
        Positional prefix ordering a[k]

    At every position k:
        1. Take current ordering a[k]
        2. Stable-partition haplotypes according to allele 0/1
        3. Concatenate 0-group and 1-group
*/

int main() {

    int M, N;

    cout << "Enter number of haplotypes (M): ";
    cin >> M;

    cout << "Enter number of sites (N): ";
    cin >> N;

    vector<string> X(M);

    cout << "\nEnter " << M << " haplotypes:\n";

    for (int i = 0; i < M; i++) {
        cin >> X[i];

        if ((int)X[i].size() != N) {
            cout << "Error: haplotype length must be "
                 << N << ".\n";
            return 1;
        }
    }

    // Initial ordering a[0]
    vector<int> a(M);

    for (int i = 0; i < M; i++)
        a[i] = i;

    cout << "\n====================================\n";
    cout << "ALGORITHM 1: BUILD PREFIX ARRAY\n";
    cout << "====================================\n";

    cout << "\na[0]: ";

    for (int id : a)
        cout << id << " ";

    cout << "\n";

    // Build a[k+1]
    for (int k = 0; k < N; k++) {

        vector<int> zero;
        vector<int> one;

        // Stable partition
        for (int i = 0; i < M; i++) {

            int id = a[i];

            if (X[id][k] == '0')
                zero.push_back(id);
            else
                one.push_back(id);
        }

        // Concatenate zero + one
        a.clear();

        for (int id : zero)
            a.push_back(id);

        for (int id : one)
            a.push_back(id);

        cout << "a[" << k + 1 << "]: ";

        for (int id : a)
            cout << id << " ";

        cout << "\n";
    }

    return 0;
}

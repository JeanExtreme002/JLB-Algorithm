#include <algorithm>
#include <bits/stdc++.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


// You can change the comparision method as you wish,
// but the comparision must have complexity O(1).
bool comparison_method(long long x, long long y) {
    return x <= y;
}

long long to_int(string sequence, unordered_map<char, int> alphabet_map) {
    long long value = 0;

    int base = alphabet_map.size();
    int m = sequence.size();

    for (int index = 0; index < m; index++) {
        int integer = alphabet_map[sequence[index]];
        int exponent = (m - 1) - index;
        value += integer * pow(base, exponent);
    }
    return value;
}

vector<int> search(string sequence, string pattern, string alphabet) {
    vector<int> occurrences;
    
    int n = sequence.size();
    int m = pattern.size();
    int base = alphabet.size();

    unordered_map<char, int> alphabet_map;

    for (int i = 0; i < base; i++) {
        alphabet_map[alphabet[i]] = i;
    }

    // Preprocessing phase ...
    long long pattern_value = to_int(pattern, alphabet_map);

    long long frame = to_int(sequence.substr(0, m), alphabet_map);
    long long most_significant_digit_position = pow(base, m - 1);

    // Searching phase ...
    if (comparison_method(frame, pattern_value)) {
        occurrences.push_back(0);
    }

    for (int i = m; i < n; ++i) {
        int element = alphabet_map[sequence[i]];

        int digit = (int)(frame / most_significant_digit_position);

        frame = (frame - (digit * most_significant_digit_position)) * base;
        frame = round(frame + element);

        if (comparison_method(frame, pattern_value)) {
            occurrences.push_back(i - m + 1);
        }
    }
    return occurrences;
}

int main() {
    string text = "abcabbbababbdaaabd";
    string pattern = "abb";
    string alphabet = "abcd";  // It must be ordered

    cout << "Searching..." << endl;

    vector<int> occurrences = search(text, pattern, alphabet);

    for (int i = 0; i < occurrences.size(); i++) {
        cout << "Found at position: " << occurrences[i] << endl;
    }
}
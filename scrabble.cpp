#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <unordered_set>
#include <limits>
using namespace std;

bool pred (char c) { return !isalpha(c); }

/**
 * Starting with an empty and reserve pset vector, generates
 * the in-order power set of the line string in pset.
 * ! REQUIRES: line is sorted and pset is empty.
 * @param line : The line for which we generate the power set of.
 * @param pset : The vector where we store the power set of line.
 * * Complexity O(2^n).
 */
void generate_power_set ( const string &line, vector<string> &pset );

int main(int argc, char **argv) {
	// stdio optimization + preliminary checks.
	ios_base::sync_with_stdio(false);
	if (argc != 2) {
		cerr << "Error: please use ./scrabble words_file < strings_file > output_file" << endl;
		exit(1);	
	}

	// Open up the words file.
	ifstream fin (argv[1]);
	if (!fin.is_open()) {
		cerr << "Error: failed to open " << argv[1] << endl;
		exit(1);
	}

	// Initialize the word dictionary and insert strings.
	unordered_map<string, vector<string> > dict;
	string in_word;
	in_word.reserve(128);

	// Read word by word.
	while (fin >> in_word) {
		string in_key = in_word;
		sort(in_key.begin(), in_key.end());
		dict[in_key].push_back(in_word);
	}
	fin.close();

	// Read line by line from standard input.
	string line;
	line.reserve(128);
	while (getline(cin, line)) {
		// Get rid of anything that is not a letter.
		line.erase(remove_if(line.begin(), line.end(), pred), line.end());
		// Store a copy of the original ordering of the line.
		const string original_line = line;
		// Sort line in alphabetical format.
		sort(line.begin(), line.end());

		// Generate the power set of line.
		vector<string> pset;
		generate_power_set(line, pset);

		vector<string> possible, longest, shortest;
		possible.reserve(pset.size());
		size_t longest_length = 0;
		size_t shortest_length = numeric_limits<size_t>::max();

		// Print the original letters.
		cout << "Original letters: " << original_line << endl;
		// For each entry in pset, check if it's in the hash table.
		for (const string &s : pset) {
			// If we find it in dict, print out the words in the vector!
			if (dict.find(s) != dict.end())
				for (const string &word : dict[s]) {
					// Print word and save it on push_back.
					possible.push_back(word);

					// Check if word could be a longest word.
					if (word.size() >= longest_length) {
						if (word.size() > longest_length) {
							longest.clear();
							longest_length = word.size();
						}
						longest.push_back(word);
					}

					if (word.size() <= shortest_length) {
						if (word.size() < shortest_length) {
							shortest.clear();
							shortest_length = word.size();
						}
						shortest.push_back(word);
					}
				}
		}
		
		// Print possible words.
		sort(possible.begin(), possible.end());
		cout << '\t' << possible.size() << " possible words: ";
		for (const string &s : possible) cout << s << ' ';
		cout << endl;

		// Print shortest words.
		sort(shortest.begin(), shortest.end());
		cout << '\t' << shortest.size() << " shortest words of length " << shortest_length << ": ";
		for (const string &s : shortest) cout << s << ' ';
		cout << endl;

		// Print shortest words.
		sort(longest.begin(), longest.end());
		cout << '\t' << longest.size() << " longest words of length " << longest_length << ": ";
		for (const string &s : longest) cout << s << ' ';
		cout << endl;
	}
}

void generate_power_set ( const string &line, vector<string> &pset ) {
	// To get the power set, we iterate over the binary numbers from 0 to 2^n - 1.
	const size_t n = line.size();
	const size_t two_pow_n = (size_t) pow(2, n);

	unordered_set<string> subwords;
	for (size_t i = 0; i < two_pow_n; ++i) {
		string substring;
		substring.reserve(n);

		// Check up to n bits.
		for (size_t j = 0; j < n; ++j) {
			// If bit j is 1, we include the j th letter
			if (i & (1 << j)) substring.push_back(line[j]);
		}

		// Add this substring to the set (auto remove duplicates).
		subwords.insert(substring);
	}
	pset.assign(subwords.begin(), subwords.end());
}
/*
Copyright 2019. Siwei Wang.

Scrabble solver.
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios_base;

using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using std::is_integral;
using std::runtime_error;
using std::sort;
using std::transform;

/**
 * A power function for integers.
 * Avoids floating point ambiguity.
 */
template <typename T>
T power(T base, T exponent);

/**
 * Returns bits matchings original.
 */
string subset(const string &original, __uint64_t bits);

/**
 * Starting with an empty and pset, generates
 * the in-order power set of the line string.
 * * Complexity O(2^n).
 */
unordered_set<string> generate_power_set(const string &line);

/**
 * Ensures command line arguments are valid. Retrieves input from
 * the list of all words and returns a sorted dictionary.
 */
unordered_map<string, vector<string> > get_input(int argc, char **argv);

/**
 * Removes non alphanumeric characters and sets everything to lower case.
 */
string process_line(string line);

/**
 * Returns as subset of pset containing
 * the possible words in the dictionary.
 */
vector<string> possible_words(
    const unordered_set<string> &pset,
    const unordered_map<string, vector<string> > &dict);

/**
 * Returns the longest possible words.
 */
vector<string> longest(const vector<string> &possible);

int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false);
  auto dict = get_input(argc, argv);

  // Read line by line from standard input.
  for (string line; getline(cin, line);) {
    cout << "\nORIGINAL INPUT: " << line << '\n';
    const auto processed = process_line(line);
    // There are 64 bits in a __uint64_t type.
    if (processed.length() > 64) {
      throw runtime_error("Lines can have at most 64 characters.");
    }
    // Generate the power set of line.
    unordered_set<string> pset = generate_power_set(processed);

    // Keep track of possible words and the longest/shortest lengths.
    const auto possible = possible_words(pset, dict);

    if (possible.empty()) {
      cout << "\nNO WORDS CAN BE FORMED USING THESE LETTERS.\n";
      continue;
    }

    const auto long_words = longest(possible);

    // Print possible words.
    cout << "\nTHERE ARE " << possible.size()
         << " POSSIBLE WORD(S) USING THESE LETTERS.\n";
    for (const string &s : possible) cout << s << ' ';
    cout << '\n';

    cout << "\nTHE LONGEST ONE(S) HAVE LENGTH " << long_words.front().length()
         << ".\n";
    for (const string &s : long_words) cout << s << ' ';
    cout << "\n" << endl;
  }
}

template <typename T>
T power(T base, T exponent) {
  static_assert(is_integral<T>::value);
  if (exponent == 0) return 1;
  if (exponent == 1) return base;

  auto tmp = power(base, exponent / 2);
  auto tmp_sq = tmp * tmp;
  return exponent % 2 == 0 ? tmp_sq : base * tmp_sq;
}

string subset(const string &original, __uint64_t bits) {
  string substring;
  // Check up to n bits.
  for (__uint64_t j = 0; j < original.length(); ++j) {
    // If bit j is 1, we include the j th letter
    if (bits & (1 << j)) substring.push_back(original[j]);
  }
  return substring;
}

unordered_set<string> generate_power_set(const string &line) {
  // To get the power set, we iterate over the binary numbers from 0 to 2^n - 1.
  const __uint64_t n = line.size();
  const __uint64_t two_pow_n = power(static_cast<__uint64_t>(2), n);

  unordered_set<string> pset;
  pset.reserve(two_pow_n);

  for (__uint64_t i = 0; i < two_pow_n; ++i) {
    pset.emplace(subset(line, i));
  }
  return pset;
}

unordered_map<string, vector<string> > get_input(int argc, char **argv) {
  if (argc != 2) {
    throw runtime_error(
        "Error: usage ./scrabble words_file < strings_file > output_file");
  }

  // Open up the words file.
  ifstream fin(argv[1]);

  // Initialize the word dictionary and insert strings.
  unordered_map<string, vector<string> > dict;
  for (string word; fin >> word;) {
    // Use sorted word as key.
    string key = word;
    sort(key.begin(), key.end());
    dict[key].emplace_back(word);
  }
  return dict;
}

string process_line(string line) {
  // Get rid of anything that is not a letter.
  line.erase(
      remove_if(line.begin(), line.end(), [](char c) { return !isalpha(c); }),
      line.end());
  transform(line.begin(), line.end(), line.begin(), ::tolower);
  // Sort line in alphabetical format.
  sort(line.begin(), line.end());
  return line;
}

vector<string> possible_words(
    const unordered_set<string> &pset,
    const unordered_map<string, vector<string> > &dict) {
  vector<string> possible;

  /**
   * Loop over possible subsets and see which
   * are contained in the dictionary.
   */
  for (const auto &str : pset) {
    if (dict.find(str) == dict.end()) continue;
    const auto &words = dict.at(str);
    // Otherwise, the dictionary contains this substring.
    possible.insert(possible.end(), words.begin(), words.end());
  }
  sort(possible.begin(), possible.end());
  return possible;
}

vector<string> longest(const vector<string> &possible) {
  __uint64_t longest_length = 0;
  vector<string> lo;
  for (const auto &str : possible) {
    const auto n = str.length();
    if (n > longest_length) {
      lo.clear();
      lo.emplace_back(str);
      longest_length = n;
    } else if (n == longest_length) {
      lo.emplace_back(str);
    }
  }
  return lo;
}

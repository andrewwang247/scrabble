# Scrabble

The scrabble program stores English words from the text file words.txt and takes in input character strings. It returns the possible English words whose letters are a multi-subset of the letters in the input string. Uses I/O redirection to handle input files containing lines of strings and output.
Usage: ./scrabble words_file < strings_file > output_file

## Algorithm

### Input Words

First, the file reads the words_file into a hash map. In particular, we want to sort each word in the words_file and use the sorted version as a key. The value then is a vector of the particular words that are an anagram of those letters. Thus, we are mapping sorted_strings -> vector of strings. Since words.txt is sorted, we get the added benefit of sorted vectors in the map.

### String Parsing

Next, we read from standard input line by line. Each line should contain a query in the form of a string of characters. Our goal is to find every word in our map that can be formed using those letters. For a query of n letters, there are 2^n subsets of those letters, so the runtime is exponential. However, we expect n to be small, so this should not be an issue. We sort the input string at the very beginning and iterate through its in-order power set, searching the hash map for each subset.

## Output

After finding all possible words that are a multi-subset of the line, we print the possible words as well as the shortest/longest words you can form using those letters.
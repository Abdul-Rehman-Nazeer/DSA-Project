import os
import time
import sys

class Node:
    def __init__(self):
        self.children = [None] * 26
        self.is_end_of_word = False

class WordTree:
    def __init__(self):
        self.root = Node()
        self.total_words = 0

    def insert(self, word):
        node = self.root
        for char in word.lower():
            if not char.isalpha():
                continue
            index = ord(char) - ord('a')
            if not node.children[index]:
                node.children[index] = Node()
            node = node.children[index]
        node.is_end_of_word = True
        self.total_words += 1

    def search_by_letter(self, node, letter, path, level, results):
        if node.is_end_of_word:
            word = ''.join(path[:level])
            if word.startswith(letter.lower()):
                results.append(word)

        for i in range(26):
            if node.children[i]:
                path[level] = chr(i + ord('a'))
                self.search_by_letter(node.children[i], letter, path, level + 1, results)

    def get_words_starting_with(self, letter):
        results = []
        path = [''] * 50
        self.search_by_letter(self.root, letter, path, 0, results)
        return results


class WordPuzzle:
    def __init__(self):
        self.forward_tree = WordTree()
        self.words = []

    def load_words_from_file(self, filename):
        try:
            with open(filename, 'r') as file:
                for line in file:
                    word = line.strip()
                    self.forward_tree.insert(word)
        except FileNotFoundError:
            print(f"\nError: '{filename}' not found.\n")

    def sort_and_save_words(self, filename="unsorted.txt"):
        if not os.path.exists(filename):
            print(f"File '{filename}' not found.")
            return

        with open(filename, 'r') as file:
            words = sorted(word.strip() for word in file if word.strip())

        print("\nSorting file alphabetically", end="")
        for _ in range(5):
            time.sleep(0.5)
            print(".", end="")
        print("\n")

        with open("Sorted.txt", 'w') as sorted_file:
            for word in words:
                sorted_file.write(word + "\n")

        print("File has been sorted and saved as 'Sorted.txt'.")
        
        # Adding explicit flush to ensure the output is printed immediately
        sys.stdout.flush()

        input("\nPress Enter to continue...")

    def run(self):
        # Load words from the file only once
        query_filename = input("Enter the filename to load (or 'default' for 'unsorted.txt'): ").strip()
        if query_filename.lower() == 'default':
            query_filename = "unsorted.txt"
        
        self.load_words_from_file(query_filename)
        print(f"Total words loaded: {self.forward_tree.total_words}")

        while True:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("\n\tWORD PUZZLE SEARCH TOOL\n")
            print("****************************************")
            print("* 0. Exit    - Exit                    *")
            print("****************************************\n")

            # Ask the user for the starting letter of the word
            letter = input("Enter the starting letter of the words you want to search: ").strip()
            if len(letter) != 1 or not letter.isalpha():
                print("Invalid input. Please enter a single alphabet letter.")
                continue

            # Get the list of words starting with the selected letter
            words = self.forward_tree.get_words_starting_with(letter)
            if words:
                print(f"\nWords starting with '{letter}':")
                for idx, word in enumerate(words, 1):
                    print(f"{idx}. {word}")

                # Ask the user to enter a word from the list
                search_word = input("\nEnter the word you want to search: ").strip()

                # Check if the entered word exists in the filtered list
                if search_word in words:
                    word_index = words.index(search_word) + 1  # Adding 1 to make it 1-based index
                    print(f"\nWord found: {word_index}. {search_word}")
                else:
                    print(f"Word '{search_word}' not found in the list of words starting with '{letter}'.")

            else:
                print(f"No words found starting with '{letter}'.")

            # Ask if the user wants to continue or exit
            exit_choice = input("\nDo you want to search again? (y/n): ").strip().lower()
            if exit_choice != 'y':
                break


if __name__ == "__main__":
    print("\t\tWORD GUESSER PROJECT\n")
    puzzle = WordPuzzle()

    # Sort and save the words (you can skip this if you don't need to sort)
    puzzle.sort_and_save_words("unsorted.txt")
    
    # Run the puzzle game with search functionality
    puzzle.run()

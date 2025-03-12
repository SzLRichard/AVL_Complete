# AVL_Complete

The autocomplete program implemented in this project works by inserting the entered words into an **AVL tree**.

It runs in the background and works in any text editor.
The entered characters are stored in a buffer, and inserted into the tree when a delimiter is typed.
It uses [Windows Hooks](https://learn.microsoft.com/en-us/windows/win32/winmsg/hooks) to fire off keypresses in order to complete the words.
## Functionality
When you press the **Tab** key after typing a partially completed word, the program searches the tree for the closest matching word and replaces the input with that word.

After that, you can use three functions:

1. **Tab Key:**  
   - If you press the Tab key again, the previously found word is replaced with the next word in the sorted sequence of the AVL tree.

2. **Backtick Key (`):**  
   - If you press the backtick key, the opposite happens: the currently selected word is replaced with the previous word in the sorted sequence of the AVL tree.

3. **Backslash Key (\\):**  
   - If you press the backslash key, the last substituted word is deleted from the displayed text **and** removed from the AVL tree, so it will no longer appear as a suggestion.

You terminate the program at any time by pressing the **Esc** key.
## Clarifications and Constraints
- Input and output only include **lowercase letters** of the English alphabet.  
- The following characters are treated as delimiters: `' '`, `','`, `'.'`, and `'\n'`.  

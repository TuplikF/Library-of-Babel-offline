# Library-of-Babel-offline

---
Principle:

Book address = any arbitrary string from the command line  
We convert it into a 64‑bit seed (FNV‑1a hash)  
The seed is used in a simple xorshift PRNG  
We generate characters from a fixed character set into pages/lines  

Parameters (feel free to adjust later):

PAGES = 10  
LINESPERPAGE = 40  
CHARSPERLINE = 80  

Character set:

`
"abcdefghijklmnopqrstuvwxyz ,.!?"
`

---

Compilation and usage

Compile:

`
gcc babeloffline.c -o babeloffline
`

Display the book in the terminal:

`
./babel_offline "hex-1-wall-2-shelf-3-book-4"
`

Save to a file:

`
./babeloffline "my-super-address" mybook.txt
`

Same address → always the same book.

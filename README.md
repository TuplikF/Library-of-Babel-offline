# Library-of-Babel-offline


---

Princip

- Adresa knihy = libovolný string z příkazové řádky  
- Z ní uděláme 64bit seed (FNV‑1a hash)  
- Seed použijeme v jednoduchém xorshift PRNG  
- Generujeme znaky z pevné znakové sady do stránek/řádků

Parametry (klidně si pak přepiš):

- PAGES = 10  
- LINESPERPAGE = 40  
- CHARSPERLINE = 80  

Znaková sada:

`c
"abcdefghijklmnopqrstuvwxyz ,.!?"
`

---

---

Kompilace a použití

`bash
gcc babeloffline.c -o babeloffline
`

Zobrazení knihy do terminálu:

`bash
./babel_offline "hex-1-wall-2-shelf-3-book-4"
`

Uložení do souboru:

`bash
./babeloffline "moje-super-adresa" mojekniha.txt
`

Stejná adresa → vždy stejná kniha.

---
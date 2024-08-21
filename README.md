Tools needed:
  VMProtect -> its load on start for our authswap dll
  cracked program -> target authswap program

So lets say you cracked a program and you want to auth swap it for your benefits

We can make a program that acts kind of ask a mask, holding back the cracked program
If you can get past the mask you have the cracked program.

So how do we make that mask?
IDEA ->
  1. Make a dll that uses any auth, keyauth for example
  2. Secure it with vmprotect
  3. Load on start on the target program with vmp

HOW? ->
  1. Setup keyauth to your keyauth
  2. Make it read a file, such as key.txt for example
  3. Make keyauth validate if that key is valid.

  .4 -> IF VALID, continue program
  .4 -> IF NOT VALID, close program

SECURITY ->
  1. Since latest vmp abuses memory exploits a cracker should not be able to crack this UNLESS they somehow "crack" vmprotect

## showcase
https://streamable.com/9i177t

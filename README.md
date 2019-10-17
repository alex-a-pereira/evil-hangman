# Evil Hangman

Hangman, with a twist >:)

## Getting started

### Build and run the program

Build the program at the root of the repository
```
make
```

Run the program
```
./string_driver
```

### How to play

You are playing from the perspective of the "guesser" in a typical game of hangman. The program plays from the perspective of the person who chooses a word.

Follow the on screen prompts to play the game. If you choose fair parameters (e.g. less than 26 guesses), you'll likely lose. 

*How to win?** It's simple - allow yourself to guess 26 or more times. No computer can outsmart you if you're allowed to guess every letter in the alphabet!

## Programming Logic

### Terminology

**my_string**

This is a typical string object, implemented as a dynamic, null terminated character array.

**Word Family**

A word family is a generic vectory consisting of my_string objects.

Each word can be sorted into a word family that all have a similar pattern. For example there are 21193 words in the dictionary that 
are 7 letters long and do not contain any occurrences of the letter ‘z’. There are 6 words that end in a
single ‘z’, 57 words that have a single ‘z’ as the next to last character and so on. 


### Process

The game works by never "choosing" a word that the user is working to guess. After each letter the user guesses, the program will determine how to leave the user with the least possible chance to win.

Take the below example, where the use choses to play with a 4 character word - excluding null terminator, obviously.
The program determines that, considering all of the possible patterns of 4-letter words containing the letter A, the user will have the worst chance if it narrows its word bank down to the words which **do not** contain the letter A at all.

```
Guess a character by entering a character a-z: a
Key: aa--, num words: 2
Key: a-a-, num words: 19
Key: a--a, num words: 20
Key: a---, num words: 151
Key: -aa-, num words: 6
Key: -a-a, num words: 34
Key: -a--, num words: 691
Key: --a-, num words: 310
Key: ----, num words: 2489
Key: ---a, num words: 140
Key with most words: '----' size 2489
```

Since the word family which has a key of `----` has 2489 words that match this pattern, it should narrow its results down to words that are in that family.

Looking at the next turn, let's assuming that the user guesses the letter Z.

```
Guess a character by entering a character a-z: z
Key: ----, num words: 2439
Key: --z-, num words: 14
Key: --zz, num words: 3
Key: ---z, num words: 11
Key: z---, num words: 22
Key with most words: '----' size 2439
```

Remember that on the previous turn, we had narrowed our word bank down to words containing no A's in them. Out of the 2489 words that were left in the word bank, there were 2439 that also did not contain any Z's in them. 
The program decides to narrow the word bank down once more to the word family with the key `----`, which now consists of words which don't contain any A's or any Z's (e.g. the word STOP)
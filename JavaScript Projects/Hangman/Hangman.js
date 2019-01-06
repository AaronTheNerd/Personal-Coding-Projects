var rl = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});
rl.setPrompt("Guess a letter or word: ");

function play(word) {
  var gameOver = false;
  var guessedLetters = [];
  var wrongGuesses = 0;
  do {
    var partialWord = partial(word, guessedLetters);
    if (partialWord === word) {
      gameOver = true;
      console.log("The word was: " + word);
      console.log("You Win!!");
      continue;
    }
    console.log(partialWord);
    printGuessedLetters(guessedLetters);
    var guess = "a";
    if (guess.length > 1 || guess.length === 0) {
      if (guess === word) {
        gameOver = true;
        console.log("The word was: " + word);
        console.log("You Win!!");
        continue;
      } else {
        wrongGuesses++;
        console.log("That guess was incorrect");
      }
    } else {
      if (guessedLetters.includes(guess)) {
        console.log("That has already been guessed");
        wrongGuesses++;

      }
      if(!word.includes(guess)) {
        wrongGuesses++;
        console.log("That guess was incorrect");
      } else {
        console.log("Good guess");
      }
    }
    if (wrongGuesses > 5) {
      console.log("You've lost!");
      gameOver = true;
      continue;
    }
  } while (!gameOver && wrongGuesses < 5);
  return;
}

function partial(word, guessedLetters) {
  var partialWord = "";
  for (var i = 0; i < word.length; i++) {
    if (guessedLetters[i] == word[i])
      partialWord += word[i];
    else
      partialWord += "_";
  }
  return partialWord;
}

function printGuessedLetters(guessedLetters) {
  var out = "Guessed Letters: ";
  if (guessedLetters.length === 0) {
    out += "None";
    console.log(out);
    return;
  }
  for (var i = 0; i < guessedLetters.length; ++i) {
    out += guessedLetters[i];
    out += " ";
  }
  console.log(out);
}

play("Jazz");
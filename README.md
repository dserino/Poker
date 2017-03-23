# Poker
Poker App

This repo houses the poker app, which is a project to build a Two-Card Texas Hold'em Poker game for Android. This app is primarily a training exercise to dive into the world of app development and to better understand the dynamics of Poker.

Details and Features:
(1) Currently written in C.
(2) Still a skeleton. Most functionality built so far is directly written in main, and all code is in one file.
(3) Two fundamental data types are Card and Player. The Card structure contains two enumerated integer data types--face and suit. Cards make up the deck, and having certain combinations of cards ranks your hand higher. The player structure contains two cards, chips, and some player characteristics.
(4) The deck is an array of cards that is shuffled with the Fisher-Yates algorithm.
(5) The poker "ring" is a circular, doubly-linked list of players
(6) The game is kept moving with a loop over players still at the table and logic based on players' actions.
(7) Side pots are pot-centric. Not yet implmented, the fundamental idea can be foudn at this link: http://stackoverflow.com/questions/17224913/fill-poker-pots
(8) Should use a pre-existing library to rank the poker hands instead of writing our own. Here are a few links that can help with that:
http://stackoverflow.com/questions/7813253/java-library-to-calculate-the-equity-of-texas-poker-hands
http://stackoverflow.com/questions/42781958/how-does-a-recursive-correlated-expression-speed-up-distinct-queries
http://stackoverflow.com/questions/10483993/faster-poker-hand-evaluation
(9) Reading user input is not robust because future implmentations will come from a touch-screen, not a terminal.
(10) Most of the details and features are driven from the World Series of Poker app on Android.

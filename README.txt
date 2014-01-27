//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu
CSE 332 README.txt - Lab 5

This code uses an abstract base class of type game, and when a game is initialized, uses the Singleton design pattern to playe either Five Card Draw or Seven Card Stud. The program also can load and save files pertaining to specific players, and their win/loss records.

I did not run into many errors while developing this lab. I implemented a sidepot that gives remaining sidepots to second place players if they had a sidepot after the winning player finished betting, and continues to give back chips to lower ranking players if they had more significant sidepots, until the last player does not have an applicable sidepot. Then they win the pot.



# Countdown Solver using Reverse Polish Notation (RPN)
# Overview
This is a C++ implementation of a solver for the Countdown game, a popular TV show in which contestants must find the longest word possible using a set of randomly selected letters, or reach a target number using a set of randomly selected numbers and basic mathematical operations. This solver focuses on the numbers version of the game and uses Reverse Polish Notation (RPN) to create and evaluate different expressions, recursively exploring all possible combinations to find the solution.

# Requirements
C++ compiler (tested on g++ version 9.3.0)

# How it works
The program generates all possible RPN expressions using the given set of numbers and operators (+, -, *, /), and evaluates each expression to see if it equals the target number. To do this, it uses a recursive approach, where each recursive call adds an operator and two operands to the expression until there are no more numbers left to use. Once a valid solution is found, the program stops searching and returns the solution. If there are no valid solutions, the program terminates and returns the closest possible number.

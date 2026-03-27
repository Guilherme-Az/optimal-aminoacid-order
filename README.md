# Optimal Amino Acid Removal Order

## Problem Description

This project solves an optimization problem involving a protein chain composed of **n amino acids**.
Each amino acid has a stability potential and belongs to one of four biochemical classes:

* **P** – Polar
* **N** – Non-Polar
* **A** – Acidic
* **B** – Basic

During the game, amino acids are removed one by one from the chain. When an amino acid is removed, a certain amount of **energy is released**.

The released energy depends on:

* The potential of the removed amino acid
* The potentials of its two closest neighbors
* The biochemical affinity between the classes of adjacent amino acids

An important aspect of the problem is that **removing an amino acid changes the neighbors of the remaining elements**, which influences the energy released by future removals.

The objective is to determine the **optimal order of removals that maximizes the total energy released**.

## Input Format

The program reads from standard input:

1. An integer `n` representing the number of amino acids
2. A sequence of `n` integers representing the potential of each amino acid
3. A sequence of `n` characters representing the biochemical class (`P`, `N`, `A`, `B`)

Example input:

```
3
10 5 12
ABA
```

## Output Format

The program outputs:

1. The **maximum total energy released**
2. The **sequence of amino acids removed** that achieves this value

If multiple optimal solutions exist, the program outputs the **lexicographically smallest sequence**.

Example output:

```
359
1 2 3
```

## Compilation

Compile the program using:

```
g++ -std=c++11 -O3 -Wall main.cpp -o program
```

Run it with:

```
./program < input.txt
```

## Context

This project was developed for the **Algorithms Analysis and Synthesis** course at **Instituto Superior Técnico**.

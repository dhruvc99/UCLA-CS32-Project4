# UCLA CS 32 Project 4: "Gee-nomics"

Project 4 for Prof. Smallberg's CS 32 taught Winter 2019 at UCLA.

The goal of this project is to efficiently process genetic data. It has the following use cases:
* Maintain a library of genomes from multiple organisms; the user can add new genomes to this library.
* Allow the user to search the library for a specified DNA sequence and identify all genomes in the library that contain that DNA sequence or any SNiP of it.
* Allow the user to present the genome/DNA of a new organism and quickly identify all genomes in the library that have a high percentage of matching DNA with the presented genome.

Our project was to implement three clasees: Genome, GenomeMatcher and Trie. 'main.cpp' and 'provided.h' were given to us. Outside of general data structures and algorithms, the core skill tested on this project was writing efficient and fast code, which is crucial considering the amount of data held in a single genome.

The data folder contains some genetic data which may be used to test the program.

# HaploPBWT

## C++ Implementation of the Positional Burrows-Wheeler Transform

This project implements the main algorithms from Richard Durbin's 2014 paper:

**"Efficient haplotype matching and storage using the positional Burrows-Wheeler transform (PBWT)"**

The implementation is written in C++ and focuses on understanding and reproducing the five main algorithms presented in the paper.

## Algorithms Implemented

### Algorithm 1 — BuildPrefixArray

Constructs the positional prefix array `a[k]`.

At each genomic position, the current haplotype ordering is stably partitioned according to allele `0` and allele `1`.

### Algorithm 2 — BuildPrefixAndDivergenceArrays

Extends Algorithm 1 by constructing the divergence array `d[k]`.

The divergence array records where neighboring haplotypes in PBWT order begin to differ.

### Algorithm 3 — ReportLongMatches

Uses the PBWT prefix and divergence information to identify haplotype matches satisfying a minimum match-length threshold.

### Algorithm 4 — ReportSetMaximalMatches

Identifies set-maximal haplotype matches within the reference haplotype panel.

### Algorithm 5 — Query Matching

Uses a PBWT index to match a new haplotype sequence against a reference panel.

The algorithm maintains a matching interval `[f,g)` and the beginning of the current match `e`.

## Project Structure

```text
HaploPBWT/
│
├── main.cpp
├── algorithm1_prefix_array.cpp
├── algorithm2_prefix_divergence.cpp
├── algorithm3_long_matches.cpp
├── algorithm4_set_maximal.cpp
├── algorithm5_query_matching.cpp
└── README.md
```

## Input

The programs use aligned binary haplotypes.

Example:

```text
6 8
00110110
00100110
10110110
10100100
00110100
10110110
```

Here:

* `6` = number of haplotypes
* `8` = number of variant positions
* each row represents one haplotype
* `0` and `1` represent the two alleles

## How to Compile

Using g++:

```bash
g++ algorithm1_prefix_array.cpp -o algorithm1
g++ algorithm2_prefix_divergence.cpp -o algorithm2
g++ algorithm3_long_matches.cpp -o algorithm3
g++ algorithm4_set_maximal.cpp -o algorithm4
g++ algorithm5_query_matching.cpp -o algorithm5
```

## How to Run

```bash
./algorithm1
```

or on Windows:

```bash
algorithm1.exe
```

The same procedure can be used for Algorithms 2–5.

## Project Objective

The objective of this project is to understand how PBWT reorganizes aligned haplotypes so that long haplotype matches can be identified efficiently.

The project separates the five algorithms so that each component can be tested and understood independently before being combined into a complete PBWT toolkit.

## Reference

Durbin, R. (2014). Efficient haplotype matching and storage using the positional Burrows-Wheeler transform (PBWT). *Bioinformatics*, 30(9), 1266–1272.

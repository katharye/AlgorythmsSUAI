# All Labs - Algorithms & Data Structures

This project is a comprehensive collection of laboratory assignments focused on algorithms and data structures in C. It features an interactive console interface to navigate through different tasks, ranging from basic text parsing to complex graph algorithms like Dijkstra and Floyd-Warshall.

## 📋 Table of Contents

- **Lab 1:** Console Application Basics & Text Parsing
- **Lab 2:** Sorting 1D Arrays
- **Lab 3:** Linked Lists
- **Lab 4:** Binary Search Trees (BST)
- **Lab 5:** Shortest Paths in Weighted Directed Graphs
- **Graph Algos:** Implementation of Dijkstra's and Floyd-Warshall's algorithms (part of Lab 5).

## 🛠 Build and Run

The project uses `make` for an automated build process.

### Prerequisites
- GCC Compiler (`gcc`)
- Make utility (`make`)

### Build Instructions

1.  **Build the project:**
    ```
    make
    ```
    This generates the `all_labs` executable in the root directory. Object files are organized in the `build/` directory.

2.  **Rebuild from scratch:**
    ```
    make rebuild
    ```

3.  **Clean up build artifacts:**
    ```
    make clean
    ```

### Running the Application

Execute the program from the root directory:
./all_labs

## 🎮 Usage Guide

Upon launching, you will see an interactive menu:

1.  **Select a Lab:** Enter the number corresponding to the lab you wish to run (1-5).
2.  **Quest Description:** The program displays the task description (loaded from `quest.txt`) for the chosen lab.
3.  **Input:**
    - **Lab 1:** You will be asked to enter a filename manually.
    - **Lab 4 & 5:** These labs automatically look for default input files (`lab4/input.txt` and `lab5/graph.txt`).
4.  **Repeat:** After a lab finishes, type `1` to return to the main menu or any other key to exit.

## 📂 Required File Structure

Ensure the following file structure exists relative to the executable for correct operation:

├── all_labs # The compiled executable
├── lab1/
│ └── quest.txt # Task description for Lab 1
├── lab2/
│ └── quest.txt
├── lab3/
│ └── quest.txt
├── lab4/
│ ├── quest.txt
│ └── input.txt # Input data for BST Lab
└── lab5/
├── quest.txt
└── graph.txt # Graph definition for Shortest Path Lab


> **Warning:** If `quest.txt` or input files are missing, the program may crash or fail to execute the algorithm.

## 📄 Lab 5: Graph File Format (`graph.txt`)

For the shortest path algorithms, the input file must follow this format:

<number_of_vertices> <number_of_edges>
<from_vertex> <to_vertex> <weight>
<from_vertex> <to_vertex> <weight>
...

**Example:**
3 2
1 2 5
2 3 10
This defines a graph with 3 vertices and 2 directed edges: $1 \to 2$ (weight 5) and $2 \to 3$ (weight 10).

## 🐛 Troubleshooting

- **"n/a" Output:** This usually means an input file is missing, empty, or has an incorrect format. Check `graph.txt` or `input.txt`.
- **Segmentation Fault:** Ensure all `quest.txt` files exist in their respective folders. The current version requires them to be present.

this text is ai genereted :) 
# 🚖 Gator Taxi

> An efficient ride-sharing management system powered by advanced data structures

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Data Structures](https://img.shields.io/badge/Data_Structures-Red_Black_Tree-red?style=for-the-badge)](https://github.com)
[![Algorithm](https://img.shields.io/badge/Algorithm-Min_Heap-orange?style=for-the-badge)](https://github.com)

## 📋 Overview

**Gator Taxi** is a sophisticated ride management system that efficiently handles ride requests using a combination of Red-Black Trees and Min-Heaps. The system optimizes ride allocation by maintaining rides in sorted order while providing fast insertion, deletion, and lookup operations.

## ✨ Key Features

- 🔴⚫ **Red-Black Tree**: Maintains rides sorted by ride number with O(log n) operations
- 🔺 **Min-Heap**: Efficiently retrieves the next ride based on cost and duration priority
- 🚀 **Fast Operations**: Logarithmic time complexity for all major operations
- 🔄 **Dynamic Updates**: Real-time ride cancellation and trip duration updates
- 📊 **Range Queries**: Query rides within a specific ride number range
- 🔗 **Dual Indexing**: Simultaneous indexing in both data structures for optimal performance

## 🏗️ System Architecture

### Data Structures

#### 1. Red-Black Tree (RBT)
- **Purpose**: Primary data structure for ride storage
- **Key**: Ride Number
- **Properties**: Self-balancing BST ensuring O(log n) operations
- **Use Cases**: 
  - Fast ride lookup by ride number
  - Efficient in-order traversal for range queries
  - Ordered ride management

#### 2. Min-Heap
- **Purpose**: Priority queue for ride dispatching
- **Priority**: Ride Cost (primary), Trip Duration (secondary)
- **Properties**: Complete binary tree with min-heap property
- **Use Cases**:
  - O(1) access to minimum cost ride
  - O(log n) insertion and deletion
  - Efficient next-ride selection

### Cross-Referencing

Each node in the RBT maintains a pointer to its corresponding heap node, and vice versa, enabling:
- O(log n) removal from heap when canceling via ride number
- Synchronized updates across both structures

## 🎯 Supported Operations

| Operation | Description | Time Complexity |
|-----------|-------------|-----------------|
| `Insert(rideNumber, rideCost, tripDuration)` | Add a new ride request | O(log n) |
| `GetNextRide()` | Retrieve and remove the ride with minimum cost | O(log n) |
| `CancelRide(rideNumber)` | Cancel a specific ride | O(log n) |
| `UpdateTrip(rideNumber, newTripDuration)` | Update trip duration with smart logic | O(log n) |
| `Print(rideNumber)` | Display details of a specific ride | O(log n) |
| `Print(rideNumber1, rideNumber2)` | Display all rides in the given range | O(k + log n)* |

*where k is the number of rides in the range

## 📥 Input Format

Commands are read from an input file with the following format:

```
Insert(rideNumber, rideCost, tripDuration)
Print(rideNumber)
Print(rideNumber1, rideNumber2)
GetNextRide()
CancelRide(rideNumber)
UpdateTrip(rideNumber, new_tripDuration)
```

### Example Input

```
Insert(101, 50, 30)
Insert(102, 45, 35)
Insert(103, 55, 25)
GetNextRide()
Print(101, 103)
UpdateTrip(102, 40)
CancelRide(103)
```

## 📤 Output Format

Output is written to `output_file.txt` with the following formats:

- **Insert**: No output (unless duplicate)
- **Print**: `(rideNumber, rideCost, tripDuration)`
- **GetNextRide**: `(rideNumber, rideCost, tripDuration)`
- **CancelRide**: No output
- **UpdateTrip**: No output (unless canceled)

### Example Output

```
(102,45,35)
(101,50,30),(103,55,25)
```

## 🔄 UpdateTrip Logic

The `UpdateTrip` operation implements intelligent ride management:

1. **newTripDuration ≤ existingTripDuration**
   - Update in place
   - No additional cost

2. **existingTripDuration < newTripDuration ≤ 2 × existingTripDuration**
   - Cancel existing ride
   - Reinsert with rideCost + 10

3. **newTripDuration > 2 × existingTripDuration**
   - Cancel the ride (too long)

## 🛠️ Build & Run

### Prerequisites

- C++ compiler with C++11 support or higher
- Make (optional)

### Compilation

```bash
g++ -std=c++11 gatorTaxi.cpp -o gatorTaxi
```

### Execution

```bash
./gatorTaxi input_file.txt
```

The program will read commands from `input_file.txt` and generate `output_file.txt`.

## 📁 Project Structure

```
gator-taxi/
├── gatorTaxi.cpp          # Main program with operation handlers
├── MyHeap.h               # Min-Heap implementation
├── MyRBT.h                # Red-Black Tree implementation
├── stringUtils.h          # String parsing utilities (not provided)
├── input_file.txt         # Sample input commands
└── output_file.txt        # Generated output
```

## 🔍 Implementation Details

### Heap Operations

- **Push**: Insert at back, heapify up
- **Pop**: Remove root, replace with last element, heapify down
- **Remove**: Replace element with last, heapify down
- **Update**: Adjust priority and heapify in appropriate direction

### Red-Black Tree Operations

- **Insert**: Standard BST insert with RBT rebalancing (rotations + recoloring)
- **Delete**: BST deletion with RBT fix-up procedures
- **Search**: Standard BST search
- **Range Query**: In-order traversal between bounds

### Balancing Cases Handled

The RBT implementation handles all standard cases:
- LR, RR, LL, RL rotations
- Color flipping
- Post-deletion rebalancing (LB0-2, RB0-2, LR, RR cases)

## 📊 Performance Analysis

| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| Insert | O(log n) | O(log n) |
| Delete | O(log n) | O(log n) |
| Search | O(log n) | O(log n) |
| GetNextRide | O(log n) | O(log n) |
| Range Query | O(k + log n) | O(k + log n) |

**Space Complexity**: O(n) where n is the number of rides

## 🎓 Algorithms Used

1. **Red-Black Tree Balancing**: Ensures O(log n) height
2. **Heap Property Maintenance**: Min-heap invariant
3. **Dual-Structure Synchronization**: Cross-referencing pointers
4. **In-order Traversal**: For sorted range queries

## 🚧 Constraints

- Maximum rides: 2000 (heap array size)
- Unique ride numbers required (duplicates rejected)
- Positive integers for rideNumber, rideCost, and tripDuration

## 🐛 Error Handling

- **Duplicate RideNumber**: Returns error message
- **No Active Rides**: GetNextRide returns appropriate message
- **Invalid Update**: Handles trip duration violations
- **Insufficient Arguments**: Requires input file

## 🌟 Highlights

- ✅ Efficient dual-indexing for optimal query performance
- ✅ Smart trip update logic with automatic cancellation
- ✅ Complete RBT implementation with all rotation cases
- ✅ Heap-based priority queue for fair ride allocation
- ✅ Clean separation of concerns with header files
- ✅ Comprehensive operation coverage

## 📚 Use Cases

- **Ride-sharing platforms**: Uber, Lyft-style ride management
- **Taxi dispatch systems**: Traditional taxi fleet management
- **Delivery services**: Package delivery optimization
- **Resource allocation**: General priority-based task scheduling

## 🤝 Contributing

Contributions are welcome! Areas for enhancement:
- Dynamic heap resizing beyond 2000 rides
- Additional query operations
- Performance optimizations
- GUI interface
- Database integration

## 📝 License

This project is available for educational purposes.

## 👨‍💻 Author

<div align="center">

### **[Aniruddh Atrey](https://www.aniruddhatrey.com)**

**AI Engineer | Cybersecurity Expert | SaaS Entrepreneur**

MS Computer Science, University of Florida | Created as an advanced data structures project at UF

[![Portfolio](https://img.shields.io/badge/Portfolio-aniruddhatrey.com-00d4ff?style=for-the-badge&logo=vercel&logoColor=white)](https://www.aniruddhatrey.com)
[![Hire Me](https://img.shields.io/badge/Hire_Me-Services-9933ff?style=for-the-badge&logo=rocket&logoColor=white)](https://www.aniruddhatrey.com/services)
[![MetaMinds](https://img.shields.io/badge/MetaMinds-AI_Agency-00ff88?style=for-the-badge&logo=brain&logoColor=white)](https://metaminds.firm.in)

---

**Want to build something like this — or better?**
[**aniruddhatrey.com**](https://www.aniruddhatrey.com) | [**metaminds.firm.in**](https://metaminds.firm.in)

*Co-Founder & COO @ [F1Jobs.io](https://f1jobs.io) | Founder & CTO @ [MetaMinds](https://metaminds.firm.in)*

⭐ Star this repo if you find it helpful!

</div>

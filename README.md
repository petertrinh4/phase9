# Phase 9 Card Game

A **command-line card game** written in C, inspired by Phase 10. Players progress through 9 phases by completing sets and runs of cards. Features a leaderboard system and efficient card-shuffling algorithms.

## 🚀 Features
- **Two-player turn-based gameplay** with dynamic phase progression.
- **Durstenfeld shuffle algorithm** for unbiased card randomization.
- **Leaderboard tracking** via file I/O (`leaderboard.txt`).
- **Input validation** and error handling for robust gameplay.
- **Optimized sorting** using `qsort` for hand management.

## 🛠️ Technical Stack
- **Language:** C (ISO C11)
- **Concepts:** Structs, pointers, file I/O, dynamic memory, sorting algorithms.
- **Tools:** GCC compiler, Git.

## 📥 Installation
1. **Clone the repository**:
   ```bash
   git clone https://github.com/petertrinh4/phase9.git
   cd phase9
   
2. **Compile the game (requires GCC):**
   gcc phase9.c -o phase9
   
3. **Run the executable:**
   ./phase9

🎮 **How to Play**
Objective: Complete all 9 phases (e.g., "2 sets of 3" or "1 run of 7") before your opponent.

Commands:

1: Draw from the deck.

2: Pick up the discard.

1-11: Select a card to discard.

Winning: First player to complete Phase 9 wins!

📊 Leaderboard
Wins are saved to leaderboard.txt and displayed in-game:
---------------------------------------
           Phase 9 Leaderboard         
---------------------------------------
   Position      Player      Wins      
   --------      ------     ------      
       1          Peter       47       
       2          Alice       36       

# Chess Engine

## Overview

This is my chess engine project developed in C++. The project goals were simply to: satisfy my curiosity about how chess engines really work, serve as an educational experience in a language I was not fully familiar with, and demonstrate my programming capabilities. Frankly the engine is not nearly finished yet and I plan to continue adding features and optimize it as time progresses. As of now this version serves as a good proof of concept and adequately implements the overall structure and logic of a chess engine. 

## Features

- **Piece Movements:** Implemented movement rules for all chess pieces including pawns, knights, bishops, rooks, queens, and kings. Utilized class polymorphis for this part.
- **Castling:** Full support for castling moves, including short and long castling.
- **En Passant:** Proper handling of en passant captures.
- **Check and Checkmate Detection:** Accurate checking for king safety and detection of checkmate situations.
- **Evaluation Function:** A function to evaluate board states, considering piece values and positioning.
- **Move Generation:** Generates all possible legal moves for each piece.
- **Minimax Algorithm** Implemented the minimax algorithm to select the best move in a generated game tree.

## Shortcomings

- **Performance:** While the engine is striving to be optimized for efficiency, performance could be improved with more advanced techniques such as alpha-beta pruning and transposition tables.
- **Evaluation Function:** Currently the evaluation function is overally simplistic and has many deficits in positional understanding.
- **Suboptimal Search Methods:** Due to my inexperience with coding chess engines my legal move serach function is rather naive and hence slow, rebuilding it would make the project significantly better.

## What I Learned

- Debugging Techniques
- Data Structures and Algorithms
- Performance Optimization
- Software Engineering Practices

This project significantly enhanced my technical skills in C++ and provided hands-on experience in managing a complex project.


## Acknowledgments

- **Chessprogramming Wiki:** Great resource that helped introduce important concepts for this project (https://www.chessprogramming.org/Main_Page)
- **Sebastian Lague:** Created a fantastic youtube video that motivated this project                  (https://www.youtube.com/watch?v=U4ogK0MIzqk&ab_channel=SebastianLague)

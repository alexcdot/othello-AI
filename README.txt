# othello-AI
The git history gives a fully detailed description of who wrote which code. Alex
coded minimax and related improvements, such as alpha-beta pruning and iterative
deepening. Alden worked on the various heuristics employed by this minimax code,
from the naive disc-counting method to various ways of assigning weights to more
or less desirable squares of the board to the moves-available analysis mentioned
below.

The git history most completely describes changes made between last week and the
current submission. Iterative deepening was implemented, allowing the program to
use more of its time, and the heuristic was improved to avoid spaces adjacent to
unoccupied corners and to measure board position by number of moves available in
the early and middle game, as suggested here:
http://www.soongsky.com/en/strategy2/ch3.php

We expect these strategies to work because they defeat the provided AIs, and search at deeper depth with a more detailed heuristic  than the provided AIs.

We tried to implement opening books, but did not find opening book resources online with a compatible format.

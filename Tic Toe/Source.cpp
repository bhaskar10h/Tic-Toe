#include <iostream>
#include <string>

// Class for keeping track of the game state
// as well as the winner
class tictactoe_board {
public:
    tictactoe_board() :
        empty_spaces(9),
        winner(EMPTY)
    {
        for (int i = 0; i < 9; i++)
            values[i] = EMPTY;
    }
    ~tictactoe_board() = default;

    // Print the broad, most important thing
    void print() const;

    // The spots on the board are numbered from 1 to 9
    // i.e.,
    //
    // 1 2 3
    // 4 5 6
    // 7 8 9

    // Check if a spot is marked or not
    bool is_set(const int num) const { return values[num - 1] != EMPTY; }

    // Mark a cross at the given spot
    void set_cross(const int num) {
        values[num - 1] = CROSS;
        --empty_spaces;
    }

    // Mark a circle at the given spot
    void set_circle(const int num) {
        values[num - 1] = CIRCLE;
        --empty_spaces;
    }

    int suggest_empty_spot() const;

    // Is the game on or not?
    bool is_finished();

    // Did crosses win?
    bool is_cross_winner();

    // Did circles win?
    bool is_circle_winner();

private:
    enum cross_or_circle {
        EMPTY = 0,
        CROSS,
        CIRCLE
    };
    bool is_full() const { return empty_spaces == 0; }
    bool check_for_winner(cross_or_circle player) const;
    void debug_values() const {
        std::cout << "values: ";
        for (int i = 0; i < 9; ++i)
            std::cout << values[i] << " ";
        std::cout << "\n";
    }

    static const char* const cross_or_circle_strings[3];
    cross_or_circle values[9];
    int empty_spaces;
    cross_or_circle winner;
};

const char* const tictactoe_board::cross_or_circle_strings[3] = { "_","X","O" };

void tictactoe_board::print() const {
    int itr = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << cross_or_circle_strings[values[itr++]] << " ";
        }
        std::cout << "\n";
    }
}

int tictactoe_board::suggest_empty_spot() const {
    assert(!is_full());
    for (int i = 8; i >= 0; --i)
        if (values[i] == EMPTY)
            return i + 1;
    return -1;
}

bool tictactoe_board::check_for_winner(const cross_or_circle player) const {
    // check rows
    for (int i = 0; i < 9; i += 3)
        if (values[i] == player &&
            values[i + 1] == player &&
            values[i + 2] == player) {
            return true;
        }

    // check columns
    for (int i = 0; i < 3; ++i)
        if (values[i] == player &&
            values[i + 3] == player &&
            values[i + 6] == player) {
            return true;
        }

    // check diagonals
    if (values[0] == player &&
        values[4] == player &&
        values[8] == player)
        return true;

    if (values[2] == player &&
        values[4] == player &&
        values[6] == player)
        return true;

    return false;
}

bool tictactoe_board::is_cross_winner() {
    if (winner == CROSS)
        return true;

    if (check_for_winner(CROSS)) {
        winner = CROSS;
        return true;
    }

    return false;
}

bool tictactoe_board::is_circle_winner() {
    if (winner == CIRCLE)
        return true;

    if (check_for_winner(CIRCLE)) {
        winner = CIRCLE;
        return true;
    }

    return false;
}

bool tictactoe_board::is_finished() {
    return is_full() || is_cross_winner() || is_circle_winner();
}

static void play_tictactoe() {
    std::cout << "Welcome to Tic-Tac-Toe\nYou play crosses, the computer plays circles\n";

    tictactoe_board board;

    while (!board.is_finished()) {
        board.print();

        std::cout << "Press 1 to 9: ";
        int num;
        std::cin >> num;
        if (num > 9 || num < 1)
            std::cout << "Number is out of range, try again\n";
        else if (board.is_set(num))
            std::cout << "That spot is already taken, try something else\n";
        else {
            board.set_cross(num);
            if (!board.is_finished()) {
                // Computer's move now - strategy is simple for now
                // Get the next empty spot from the end
                // This strategy can be changed to more sophisticated
                // schemes
                board.set_circle(board.suggest_empty_spot());
            }
        }
        std::cout << "\n";
    }

    board.print();
    std::cout << "Game over\n";
    if (board.is_circle_winner())
        std::cout << "Circle won\n";
    else if (board.is_cross_winner())
        std::cout << "Cross won\n";
    else
        std::cout << "No winner\n";
}

int main() {
    play_tictactoe();
    return 0;
}

// TODO game logic client side
class Connect4 {
    int PlayerDrop() {
        int dropChoice;
        do {
            cout << activePlayer.playerName << "'s Turn ";
            cout << "Please enter a number between 1 and 7: ";
            cin >> dropChoice;

            while (board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O') {
                cout << "That row is full, please enter a new row: ";
                cin >> dropChoice;
            }

        } while (dropChoice < 1 || dropChoice > 7);

        return dropChoice;
    }
}
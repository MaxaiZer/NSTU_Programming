namespace Models
{
    public enum GameState {
        NotOver, 
        Draw,
        FirstPlayerWin,
        SecondPlayerWin
    }

    public class Game
    {
        public string FirstPlayerId { get; private set; }
        public string SecondPlayerId { get; private set; }

        public GameState CurState { get; private set; }

        public string currentTurnPlayerId;

        public event EventHandler? TurnPlayerChanged;

        public event EventHandler? GameOver;

        private CellState[,] field = new CellState[Rows, Columns];

        private const uint Columns = 3;
        private const uint Rows = 3;

        private const uint WinningSequenceLength = 3;

        private enum CellState { Empty, OccupiedByFirstPlayer, OccupiedBySecondPlayer }

        private int curTurn = 0;

        public Game(string firstPlayerId, string secondPlayerId)
        {
            currentTurnPlayerId = FirstPlayerId = firstPlayerId;
            SecondPlayerId = secondPlayerId;
        }

        public void MakeMove(int row, int column)
        {
            if (row < 0 || row >= Rows || column < 0 || column >= Columns)
                throw new ArgumentOutOfRangeException("row/column is out of range");

            if (field[row, column] != CellState.Empty)
                return;

            field[row, column] = currentTurnPlayerId == FirstPlayerId ?
                CellState.OccupiedByFirstPlayer :
                CellState.OccupiedBySecondPlayer;

            CheckWin(row, column);

            if (CurState != GameState.NotOver) return;
            ChangeCurrentTurnPlayer();
            curTurn++;
        }

        private void ChangeCurrentTurnPlayer() {
            currentTurnPlayerId = currentTurnPlayerId == FirstPlayerId ?
                SecondPlayerId :
                FirstPlayerId;

            TurnPlayerChanged?.Invoke(this, EventArgs.Empty);
        }

        private void CheckWin(int moveRow, int moveColumn) {
            CellState targetState = currentTurnPlayerId == FirstPlayerId ?
                CellState.OccupiedByFirstPlayer :
                CellState.OccupiedBySecondPlayer;

            Func<int, int, bool> findSequence = (stepRow, stepColumn) => {
                int count = 0;

                bool switchedDirection = false;
                int row = moveRow, column = moveColumn;

                while (row >= 0 && row < Rows && column >= 0 && column < Columns) {
                    
                    if (field[row, column] == targetState) { 
                        count++;
                        if (count == WinningSequenceLength) return true;
                    }
                    else if (switchedDirection) return false;
                    else {
                        switchedDirection = true;
                        row = moveRow;
                        column = moveColumn;

                        stepRow *= -1;
                        stepColumn *= -1;
                    }

                    row += stepRow;
                    column += stepColumn;
                }

                return false;
            };

            if (findSequence(0, 1) || findSequence(1, 0) || findSequence(1, 1)) {
                CurState = currentTurnPlayerId == FirstPlayerId ?
                    GameState.FirstPlayerWin :
                    GameState.SecondPlayerWin;

                GameOver?.Invoke(this, EventArgs.Empty);
                return;
            }

            if (curTurn == Rows * Columns - 1) {
                CurState = GameState.Draw;
                GameOver?.Invoke(this, EventArgs.Empty);
            }
        }

    }
}
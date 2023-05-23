namespace rgz.Models
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

        public bool MakeMove(int row, int column)
        {
            if (row < 0 || row >= Rows || column < 0 || column >= Columns)
                throw new ArgumentOutOfRangeException("row/column is out of range");

            if (field[row, column] != CellState.Empty)
                return false;

            field[row, column] = currentTurnPlayerId == FirstPlayerId ?
                CellState.OccupiedByFirstPlayer :
                CellState.OccupiedBySecondPlayer;

            CheckWin(row, column);

            if (CurState != GameState.NotOver) return true;
            ChangeCurrentTurnPlayer();
            curTurn++;
            return true;
        }

        private void ChangeCurrentTurnPlayer() {
            currentTurnPlayerId = currentTurnPlayerId == FirstPlayerId ?
                SecondPlayerId :
                FirstPlayerId;
        }

        private void CheckWin(int moveRow, int moveColumn) {
            CellState targetState = currentTurnPlayerId == FirstPlayerId ?
                CellState.OccupiedByFirstPlayer :
                CellState.OccupiedBySecondPlayer;

            Func<int, int, bool> find = (stepRow, stepColumn) => {

                int count = 0;
                int row = moveRow, column = moveColumn;

                while (row >= 0 && row < Rows && column >= 0 && column < Columns) {
                    
                    if (field[row, column] == targetState) { 
                        count++;  System.Console.WriteLine("Increase");
                        if (count == WinningSequenceLength) return true;
                    }
                    else return false;

                    row += stepRow;
                    column += stepColumn;
                }

                return false;
            };

            if (find(0,1) || find(0, -1) || find(1, 0) || find (-1, 0) || find(1, 1) || find(-1, -1)) {       
                CurState = currentTurnPlayerId == FirstPlayerId ?
                    GameState.FirstPlayerWin :
                    GameState.SecondPlayerWin;
                return;
            }

            if (curTurn == Rows * Columns - 1) {
                CurState = GameState.Draw;
            }
        }

    }
}
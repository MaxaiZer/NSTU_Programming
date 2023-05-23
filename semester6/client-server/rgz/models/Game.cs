namespace rgz.Models
{
    public enum GameState
    {
        NotOver,
        Draw,
        FirstPlayerWin,
        SecondPlayerWin
    }

    public class Game
    {
        public string FirstPlayerId { get; }
        public string SecondPlayerId { get; }

        public GameState CurState { get; private set; }

        public string currentTurnPlayerId;

        public event EventHandler? turnPlayerChanged;

        public event EventHandler? gameOver;

        private CellState[,] field = new CellState[_columns, _rows];

        private const uint _columns = 3;
        private const uint _rows = 3;

        private const uint _winningSequenceLength = 3;

        private enum CellState { Empty, OccupiedByFirstPlayer, OccupiedBySecondPlayer }

        private int _curTurn = 0;

        public Game(string firstPlayerId, string secondPlayerId)
        {
            currentTurnPlayerId = FirstPlayerId = firstPlayerId;
            SecondPlayerId = secondPlayerId;
        }

        public GameInfo GetInfo() {
            return new GameInfo(crossPlayerId: FirstPlayerId, toePlayerId: SecondPlayerId);
        }

        public bool MakeMove(int row, int column)
        {
            if (row < 0 || row >= _rows || column < 0 || column >= _columns)
                throw new ArgumentOutOfRangeException("row/column is out of range");

            if (field[row, column] != CellState.Empty)
                return false;

            field[row, column] = currentTurnPlayerId == FirstPlayerId ?
                CellState.OccupiedByFirstPlayer :
                CellState.OccupiedBySecondPlayer;

            CheckWin(row, column);

            if (CurState != GameState.NotOver) { gameOver?.Invoke(this, EventArgs.Empty); return true; }
            ChangeCurrentTurnPlayer();
            _curTurn++;
            return true;
        }

        private void ChangeCurrentTurnPlayer()
        {
            currentTurnPlayerId = currentTurnPlayerId == FirstPlayerId ?
                SecondPlayerId :
                FirstPlayerId;
            turnPlayerChanged?.Invoke(this, EventArgs.Empty);
        }

        private void CheckWin(int moveRow, int moveColumn)
        {
            CellState targetState = currentTurnPlayerId == FirstPlayerId ?
                CellState.OccupiedByFirstPlayer :
                CellState.OccupiedBySecondPlayer;

            if (hasWinningSequence(moveRow, moveColumn, 0, 1, targetState) ||
                hasWinningSequence(moveRow, moveColumn, 1, 0, targetState) ||
                hasWinningSequence(moveRow, moveColumn, 1, 1, targetState) ||
                hasWinningSequence(moveRow, moveColumn, -1, 1, targetState) 
            )
            {
                CurState = currentTurnPlayerId == FirstPlayerId ?
                    GameState.FirstPlayerWin :
                    GameState.SecondPlayerWin;
                return;
            }

            if (_curTurn == _rows * _columns - 1)
            {
                CurState = GameState.Draw;
            }
        }

        private bool hasWinningSequence(int moveRow, int moveColumn,
            int stepRow, int stepColumn, CellState targetState)
        {
            int count = 1;
            int row = moveRow + stepRow, column = moveColumn + stepColumn;

            Action setSequenceLength = () =>
            {

                while (row >= 0 && row < _rows &&
                    column >= 0 && column < _columns &&
                    count < _winningSequenceLength)
                {
                    if (field[row, column] == targetState)
                        count++;
                    else break;

                    row += stepRow;
                    column += stepColumn;
                }
            };

            setSequenceLength();
            if (count >= _winningSequenceLength) return true;

            stepRow *= -1;
            stepColumn *= -1;

            row = moveRow + stepRow;
            column = moveColumn + stepColumn;

            setSequenceLength();
            if (count >= _winningSequenceLength) return true;
            return false;
        }

    }
}
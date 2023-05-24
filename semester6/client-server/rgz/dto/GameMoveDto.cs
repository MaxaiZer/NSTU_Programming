namespace rgz.Dto
{
    public class GameMoveDto
    {

        public string gameId;
        public int row;
        public int col;

        public GameMoveDto(string gameId, int row, int col)
        {
            this.gameId = gameId;
            this.row = row;
            this.col = col;
        }
    }
}
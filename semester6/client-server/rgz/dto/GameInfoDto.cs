namespace rgz.Dto
{
    public class GameInfoDto
    {

        public string gameId;
        public string crossPlayerId;
        public string toePlayerId;

        public GameInfoDto(string gameId, string crossPlayerId, string toePlayerId)
        {
            this.gameId = gameId;
            this.crossPlayerId = crossPlayerId;
            this.toePlayerId = toePlayerId;
        }
    }
}
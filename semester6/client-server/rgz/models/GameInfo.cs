namespace rgz.Models
{
    public class GameInfo
    {

        public string crossPlayerId;
        public string toePlayerId;

        public GameInfo(string crossPlayerId, string toePlayerId)
        {
            this.crossPlayerId = crossPlayerId;
            this.toePlayerId = toePlayerId;
        }
    }
}
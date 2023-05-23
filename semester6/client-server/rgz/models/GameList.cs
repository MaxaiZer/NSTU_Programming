namespace rgz.Models
{

    public class GameList
    {
        private static GameList _instance;
        private List<Game> _games = new List<Game>();
        private object _lockObject = new object();

        private GameList() { }

        public static GameList Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new GameList();
                }
                return _instance;
            }
        }

        public void Add(Game game)
        {
            lock (_lockObject)
            {
                _games.Add(game);
            }
        }

        public void Remove(Game game)
        {
            lock (_lockObject)
            {
                _games.Remove(game);
            }
        }

        public Game? FindByPlayerId(string playerId) {
            return _games.Find(game => game.FirstPlayerId == playerId ||
                game.SecondPlayerId == playerId);
        }

    }
}
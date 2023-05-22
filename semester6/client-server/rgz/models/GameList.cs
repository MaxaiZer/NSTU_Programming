namespace Models
{

    public class GameList
    {
        private static GameList instance;
        private List<Game> games = new List<Game>();
        private object lockObject = new object();

        private GameList() { }

        public static GameList Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new GameList();
                }
                return instance;
            }
        }

        public void Add(Game game)
        {
            lock (lockObject)
            {
                games.Add(game);
            }
        }

        public void Remove(Game game)
        {
            lock (lockObject)
            {
                games.Remove(game);
            }
        }

        public Game? Find(Predicate<Game> match) => games.Find(match);

    }
}
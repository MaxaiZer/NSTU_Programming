using System.Collections.Concurrent;

namespace rgz.Models
{

    public class GameList
    {
        private static GameList _instance;

        private ConcurrentDictionary<string, Game> _games = new ConcurrentDictionary<string, Game>();

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

        public bool Add(Game game)
        {
            return _games.TryAdd(game.Id, game);
        }

        public bool Remove(string id)
        {
            Game? game;
            return _games.TryRemove(id, out game);
        }
    
        public Game? Find(string id)
        {
            Game? game = null;
            _games.TryGetValue(id, out game);
            return game;
        }

    }
}
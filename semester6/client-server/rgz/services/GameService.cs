using Microsoft.AspNetCore.SignalR;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using rgz.Hubs;
using rgz.Models;

namespace rgz.Services
{

    public class GameService : IGameService
    {
        private IHubContext<GameHub> _hubContext;

        public GameService(IHubContext<GameHub> hubContext)
        {
            _hubContext = hubContext;
        }

        public async Task CreateGame(string firstPlayerId, string secondPlayerId) {
            Random random = new Random();
            int randomNumber = random.Next(0, 2);

            Game game = randomNumber == 0 ?
                new Game(firstPlayerId, secondPlayerId) :
                new Game(secondPlayerId, firstPlayerId);

            GameList.Instance.Add(game);

            game.gameOver += this.OnGameOver;
            game.turnPlayerChanged += this.OnTurnPlayerChanged;

            var info = game.GetInfo();
            string infoJson = JsonConvert.SerializeObject(info);

            await _hubContext.Clients.Client(game.FirstPlayerId).SendAsync("GameInfo", infoJson);
            await _hubContext.Clients.Client(game.SecondPlayerId).SendAsync("GameInfo", infoJson);
            await _hubContext.Clients.Client(game.currentTurnPlayerId).SendAsync("PlayerTurn");
        }

        public async Task HandlePlayerMove(string playerId, int row, int col)
        {
            var game = GameList.Instance.FindByPlayerId(playerId);

            if (game is null) return;
            if (!game.MakeMove(row, col)) return;

            string anotherPlayer = game.FirstPlayerId == playerId ?
                game.SecondPlayerId :
                game.FirstPlayerId;

            await _hubContext.Clients.Client(anotherPlayer).SendAsync("MadeMove", row, col);
        }

        public async void OnGameOver(object sender, EventArgs args)
        {
            var game = sender as Game;
            GameList.Instance.Remove(game);

            var result = new GameResult(game.CurState, game.FirstPlayerId, game.SecondPlayerId);
            string json = JsonConvert.SerializeObject(result, new StringEnumConverter());

            await _hubContext.Clients.Client(game.FirstPlayerId).SendAsync("GameResult", json);
            await _hubContext.Clients.Client(game.SecondPlayerId).SendAsync("GameResult", json);
        }

        public async void OnTurnPlayerChanged(object sender, EventArgs args)
        {
            var game = sender as Game;
            await _hubContext.Clients.Client(game.currentTurnPlayerId).SendAsync("PlayerTurn");
        }
    }

}
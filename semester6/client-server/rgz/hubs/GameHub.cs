using System.Collections.Concurrent;
using Microsoft.AspNetCore.SignalR;
using Models;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace rgz.Hubs
{
    public class GameHub : Hub
    {

        private static ConcurrentBag<string> waitingPlayerIds = new ConcurrentBag<string>();

        public async Task WaitForGame() {

            if (waitingPlayerIds.Contains(Context.ConnectionId)) {
                await Clients.Caller.SendAsync("ErrorMessage", "You are already waiting for a game");
                return;
            }
            
            if (waitingPlayerIds.Count > 0) {
                string secondPlayerId;
                if (!waitingPlayerIds.TryTake(out secondPlayerId)) {
                    waitingPlayerIds.Add(Context.ConnectionId);
                }
                else await CreateGame(Context.ConnectionId, secondPlayerId);
            }
            else waitingPlayerIds.Add(Context.ConnectionId);  
        }

        public async Task MakeMove(int row, int col) {

            var game = GameList.Instance.Find(game => game.FirstPlayerId == Context.ConnectionId || 
                game.SecondPlayerId == Context.ConnectionId
            );

            if (game is null) return;

            game.MakeMove(row, col);

            string anotherPlayer = game.FirstPlayerId == Context.ConnectionId ? 
                game.SecondPlayerId :
                game.FirstPlayerId;

            await Clients.Client(anotherPlayer).SendAsync("MadeMove", row, col);
           // GlobalHost.ConnectionManager.GetHubContext<GameHub>();
        //   var b = Host.CreateDefaultBuilder();
         //  await Services.GetService<GameHub>().MakeMove(row, col);
          //  HubContext
        }

        public async Task SendMessage(string user, string message)
        {
            await Clients.All.SendAsync("ReceiveMessage", user, message);
        }

        private async Task CreateGame(string firstUserId, string secondUserId) {
            var game = new Game(firstUserId, secondUserId);
            game.GameOver += OnGameOver;
            game.TurnPlayerChanged += OnTurnPlayerChanged;
            GameList.Instance.Add(game);
            await Clients.Client(firstUserId).SendAsync("PlayerTurn");
        }

        private async void OnTurnPlayerChanged(object sender, EventArgs args) {
            await Clients.Client(((Game)sender).currentTurnPlayerId).SendAsync("PlayerTurn");
        }

        private async void OnGameOver(object sender, EventArgs args) {

            var game = sender as Game;
            GameList.Instance.Remove(game);

            var result = new GameResult(game.CurState, game.FirstPlayerId, game.SecondPlayerId);
            string json = JsonConvert.SerializeObject(result, new StringEnumConverter());
       
            Clients.Client(game.FirstPlayerId).SendAsync("GameResult", json);
            Clients.Client(game.SecondPlayerId).SendAsync("GameResult", json);
        }
    }
}
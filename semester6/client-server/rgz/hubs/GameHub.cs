using System.Collections.Concurrent;
using Microsoft.AspNetCore.SignalR;
using rgz.Models;
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
            if (!game.MakeMove(row, col)) return;

            string anotherPlayer = game.FirstPlayerId == Context.ConnectionId ? 
                game.SecondPlayerId :
                game.FirstPlayerId;

            await Clients.Client(anotherPlayer).SendAsync("MadeMove", row, col);

            if (game.CurState != GameState.NotOver) {
                await OnGameOver(game);
                return;
            }

            await Clients.Client(anotherPlayer).SendAsync("PlayerTurn", row, col);  
        }

        public async Task SendMessage(string user, string message)
        {
            await Clients.All.SendAsync("ReceiveMessage", user, message);
        }

        private async Task CreateGame(string firstUserId, string secondUserId) {

            Random random = new Random();
            int randomNumber = random.Next(0, 2);

            Game game = randomNumber == 0 ?
                new Game(firstUserId, secondUserId) :
                new Game(secondUserId, firstUserId);

            GameList.Instance.Add(game);

            var info = new GameInfo(crossPlayerId: game.FirstPlayerId, toePlayerId: game.SecondPlayerId);
            string infoJson = JsonConvert.SerializeObject(info);

            await Clients.Client(firstUserId).SendAsync("GameInfo", infoJson);
            await Clients.Client(secondUserId).SendAsync("GameInfo", infoJson);
            await Clients.Client(game.FirstPlayerId).SendAsync("PlayerTurn");
        }

        private async Task OnGameOver(Game game) {

            GameList.Instance.Remove(game);

            var result = new GameResult(game.CurState, game.FirstPlayerId, game.SecondPlayerId);
            string json = JsonConvert.SerializeObject(result, new StringEnumConverter());

            await Clients.Client(game.FirstPlayerId).SendAsync("GameResult", json);
            await Clients.Client(game.SecondPlayerId).SendAsync("GameResult", json);
        }
    }
}
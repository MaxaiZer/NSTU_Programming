using System.Collections.Concurrent;
using Microsoft.AspNetCore.SignalR;
using rgz.Models;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using rgz.Services;
using rgz.Dto;

namespace rgz.Hubs
{
    public class GameHub : Hub
    {

        private static ConcurrentBag<string> _waitingPlayerIds = new ConcurrentBag<string>();
        private IGameService _gameService;

        public GameHub(IGameService gameService)
        {
            _gameService = gameService;
        }

        public async Task WaitForGame()
        {

            if (_waitingPlayerIds.Contains(Context.ConnectionId))
            {
                await Clients.Caller.SendAsync("ErrorMessage", "You are already waiting for a game");
                return;
            }

            if (_waitingPlayerIds.Count > 0)
            {
                string secondPlayerId;
                if (!_waitingPlayerIds.TryTake(out secondPlayerId))
                {
                    _waitingPlayerIds.Add(Context.ConnectionId);
                }
                else await _gameService.CreateGame(Context.ConnectionId, secondPlayerId);
            }
            else _waitingPlayerIds.Add(Context.ConnectionId);
        }

        public async Task MakeMove(string gameMoveJson)
        {
            var move = JsonConvert.DeserializeObject<GameMoveDto>(gameMoveJson);
            await _gameService.HandlePlayerMove(move.gameId, Context.ConnectionId, move.row, move.col);
        }

        public override Task OnDisconnectedAsync(Exception? exception)
        {
            /*
                it is necessary to remove the player either waiting list or from the game and 
                notify the second player about it. So, game id needs to be stored in Context.Items.
                Sorry, but I don't have time.
            */
            return base.OnDisconnectedAsync(exception);
        }
    }
}
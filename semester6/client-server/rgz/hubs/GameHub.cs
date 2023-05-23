using System.Collections.Concurrent;
using Microsoft.AspNetCore.SignalR;
using rgz.Models;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using rgz.Services;

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

        public async Task MakeMove(int row, int col)
        {
            await _gameService.HandlePlayerMove(Context.ConnectionId, row, col);
        }

    }
}
using rgz.Models;

namespace rgz.Services
{

    public interface IGameService
    {
        public void OnGameOver(object sender, EventArgs args);

        public void OnTurnPlayerChanged(object sender, EventArgs args);

        public Task CreateGame(string firstPlayerId, string secondPlayerId);

        public Task HandlePlayerMove(string playerId, int row, int col);

    }

}
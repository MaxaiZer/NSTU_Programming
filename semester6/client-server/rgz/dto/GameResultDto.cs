using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using rgz.Models;

namespace rgz.Dto
{
    public class GameResultDto
    {

        [JsonConverter(typeof(StringEnumConverter))]
        public GameState state;
        public string firstPlayerId;
        public string secondPlayerId;

        public GameResultDto(GameState state, string firstPlayerId, string secondPlayerId)
        {
            this.state = state;
            this.firstPlayerId = firstPlayerId;
            this.secondPlayerId = secondPlayerId;
        }

    }
}
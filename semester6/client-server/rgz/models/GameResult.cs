using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace Models {
    public class GameResult {

        [JsonConverter(typeof(StringEnumConverter))]
        public GameState state;
        public string firstPlayerId;
        public string secondPlayerId;

        public GameResult(GameState state, string firstPlayerId, string secondPlayerId) {
            this.state = state;
            this.firstPlayerId = firstPlayerId;
            this.secondPlayerId = secondPlayerId;
        }

    }
}
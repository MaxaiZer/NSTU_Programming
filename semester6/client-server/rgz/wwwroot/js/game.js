"use strict";

var Player = {
    Cross: "Cross",
    Toe: "Toe"
}

var connection = new signalR.HubConnectionBuilder().withUrl("/gameHub").build();

var isPlayerTurn = false;
var thisPlayer = Player.Cross;

connection.start().then(function () {

    console.log("Player id: " + connection.connectionId);

    connection.invoke("WaitForGame").catch(function (err) {
        return console.error(err.toString());
    });
}).catch(function (err) {
    return console.error(err.toString());
});

connection.on("GameResult", function (result) {
    if (result.state === "Draw") {
        console.log("Draw!");
        return;
    }

    let winnerId = (result.state === "FirstPlayerWin" ? state.firstPlayerId : result.secondPlayerId);

    if (connection.connectionId == winnerId)
        console.log("Win!");
    else
        console.log("Lose!");
});

connection.on("PlayerTurn", function () {
    console.log("Player's turn!");
    isPlayerTurn = true;
});

connection.on("MadeMove", function (row, col) {
    makeMove(row, col, thisPlayer == Player.Cross ? Player.Toe : Player.Cross);
});

function drawMove(row, col, player) {
    const cell = document.querySelector(`[data-row="${row}"][data-col="${col}"]`);
    if (!cell)  return false;
    // Perform validation and update the image based on the move

    // Replace "path/to/cross.jpg" and "path/to/toe.jpg" with the actual image paths for cross and toe
    const imageSrc = player == Player.Cross ? "images/cross.jpg" : "images/toe.jpg";

    const image = cell.querySelector(".cell-image");
    image.src = imageSrc;

    return true;
}

function makeMove(row, col, player) {

    if (player == thisPlayer && !isPlayerTurn) return;
    if (!drawMove(row, col, player)) return;

    if (player == thisPlayer) {
        connection.invoke("MakeMove", row, col)
        .catch(function(error) {
            console.error(error);
        });
        
        isPlayerTurn = false;
    }
}

function createGameBoard() {
    const boardContainer = document.getElementById("game-board");
    const rows = 3;
    const columns = 3;
    boardContainer.innerHTML = ""; // Clear the board container

    for (let row = 0; row < rows; row++) {
        for (let col = 0; col < columns; col++) {
            const cell = document.createElement("div");
            cell.classList.add("cell");
            cell.dataset.row = row.toString();
            cell.dataset.col = col.toString();
            cell.addEventListener("click", () => makeMove(row, col, thisPlayer));

            const image = document.createElement("img");
            image.classList.add("cell-image");
            image.src = "images/empty.jpg"; // Replace with the path to your empty cell image

            cell.appendChild(image);
            boardContainer.appendChild(cell);
        }
    }
}

$(document).ready(function() {
    createGameBoard();
});
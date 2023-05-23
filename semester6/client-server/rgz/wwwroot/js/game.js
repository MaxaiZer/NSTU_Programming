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

    console.log("received game result: " + result);
    result = JSON.parse(result);

    if (result.state === "Draw") {
        document.getElementById("message").textContent = "Draw!";
        return;
    }

    let winnerId = (result.state === "FirstPlayerWin" ? result.firstPlayerId : result.secondPlayerId);
    let message = connection.connectionId == winnerId ? "Win!" : "Lose!";
    document.getElementById("message").textContent = message;
});

connection.on("PlayerTurn", function () {

    console.log("received player turn");
    document.getElementById("message").textContent = "It's your turn!";
    isPlayerTurn = true;
});

connection.on("MadeMove", function (row, col) {

    console.log("received made move");
    makeMove(row, col, thisPlayer == Player.Cross ? Player.Toe : Player.Cross);
});

connection.on("GameInfo", function (info) {

    console.log("received game info: " + info);
    info = JSON.parse(info);
    thisPlayer = connection.connectionId == info.crossPlayerId ?
        Player.Cross :
        Player.Toe;

    document.getElementById("message").textContent = "Opponent was found!";
});

function drawMove(row, col, player) {
    const cell = document.querySelector(`[data-row="${row}"][data-col="${col}"]`);
    if (!cell)  return false;
    // Perform validation and update the image based on the move

    // Replace "path/to/cross.jpg" and "path/to/toe.jpg" with the actual image paths for cross and toe
    const imageSrc = player == Player.Cross ? "images/cross.jpg" : "images/toe.jpg";

    const image = cell.querySelector(".cell-image");

    if (image.scr == imageSrc) return false;

    image.src = imageSrc;
    return true;
}

function makeMove(row, col, player) {

    if (player == thisPlayer && !isPlayerTurn) return;
    if (!drawMove(row, col, player)) return;

    if (player != thisPlayer) return;

    connection.invoke("MakeMove", row, col)
        .catch(function (error) {
            console.error(error);
        });

    isPlayerTurn = false;
    document.getElementById("message").textContent = "It's opponent turn!";
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
    document.getElementById("message").textContent = "Waiting for opponent...";
});
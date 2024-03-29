const cells = [[], [], [], [], [], [], [], []];

const COLOR = {
  Black: "Black",
  White: "White",
};

const STATE = {
  Selected: "selected",
  HighlightedFree: "highlighted-free",
  HighlightedOccupied: "highlighted-occupied",
};

function initializeBoard() {
  const chessboard = document.getElementById("chessboard");

  if (!chessboard) {
    return;
  }

  for (let i = 7; i >= 0; i--) {
    for (let j = 0; j < 8; j++) {
      chessboard.appendChild(cells[i][j]);
    }
  }
}

function highlightSelectedCell(x, y) {
  cells[x][y].classList.add(STATE.Selected);
}

function highlightCells(coordinates) {
  for (let c of coordinates) {
    const element = cells[c[0]][c[1]];
    if (element.getElementsByTagName("img").length > 0) {
      element.classList.add(STATE.HighlightedOccupied);
    } else {
      element.classList.add(STATE.HighlightedFree);
    }
  }
}

function clearCellsHighlight() {
  for (let row of cells) {
    for (let element of row) {
      element.classList.remove(STATE.HighlightedOccupied);
      element.classList.remove(STATE.HighlightedFree);
      element.classList.remove(STATE.Selected);
    }
  }
}

function putPiece(x, y, pieceName, pieceColor) {
  cells[x][y].innerHTML =
    "<img class='piece-image' " + `src='${pieceName}_${pieceColor}.svg'>`;
}

function removePiece(x, y) {
  cells[x][y].innerHTML = "";
}

function addDeadPiece(pieceName, pieceColor) {
  const element = document.createElement("img");
  element.src = `${pieceName}_${pieceColor}.svg`;
  element.classList.add("dead-piece-image");

  if (pieceColor == COLOR.White) {
    document.getElementById("whitePiecesContainer").append(element);
  } else {
    document.getElementById("blackPiecesContainer").append(element);
  }
}

function showMessage(message) {
  document.getElementById("message").innerText = message;
}

function clearMessage() {
  document.getElementById("message").innerText = "";
}

function disableButton(id) {
  const button = document.getElementById(id);
  button.disabled = true;
  button.classList.add("disabled");
}

function enableButton(id) {
  const button = document.getElementById(id);
  button.disabled = false;
  button.classList.remove("disabled");
}

function onStartGameClicked() {
  onStartGame();

  clearMessage();

  enableButton("startGameOverButton");
  disableButton("startGameButton");
  disableButton("startGameOnlineButton");
  disableButton("blackUserNameButton");
  disableButton("whiteUserNameButton");
}

function onStartGameOnlineClicked() {
  //TODO
}

function onStartGameOverClicked() {
  onStartGameOver();

  disableButton("startGameOverButton");
  enableButton("blackUserNameButton");
  enableButton("whiteUserNameButton");

  document.getElementById("whitePiecesContainer").innerHTML = "";
  document.getElementById("blackPiecesContainer").innerHTML = "";

  showMessage("Enter usernames to start the game");
}

function clearBoard() {
  for (let x = 7; x >= 0; x--) {
    for (let y = 0; y < 8; y++) {
      removePiece(x, y);
    }
  }
}

let whiteUser = "";
let blackUser = "";

function onWhiteUserNameSubmit() {
  const input = document.getElementById("whiteUserNameInput");
  const name = input.value;
  const label = document.getElementById("whiteUserName");
  const errorMessage = document.getElementById("whiteUserMessage");

  if (name.length <= 1 || name.length > 30) {
    errorMessage.innerText = "Error: username should have 2-30 characters.";
    return;
  }

  if (blackUser == name) {
    errorMessage.innerText = "Error: username already occupied.";
    return;
  }

  errorMessage.innerText = "";

  label.innerText = name;
  whiteUser = name;

  if (blackUser.length > 0) {
    enableButton("startGameButton");
  }

  onAddWhitePiecesUser(name);
}

function onBlackUserNameSubmit() {
  const input = document.getElementById("blackUserNameInput");
  const name = input.value;
  const label = document.getElementById("blackUserName");
  const errorMessage = document.getElementById("blackUserMessage");

  if (name.length <= 1 || name.length > 30) {
    errorMessage.innerText = "Error: username should have 2-30 characters.";
    return;
  }

  if (whiteUser == name) {
    errorMessage.innerText = "Error: username already occupied.";
    return;
  }

  errorMessage.innerText = "";

  label.innerText = name;
  blackUser = name;

  if (whiteUser.length > 0) {
    enableButton("startGameButton");
  }

  onAddBlackPiecesUser(name);
}

function clearUserNames() {
  whiteUser = "";
  blackUser = "";
  document.getElementById("whiteUserName").innerText = "";
  document.getElementById("blackUserName").innerText = "";
  document.getElementById("whiteUserNameInput").value = "";
  document.getElementById("blackUserNameInput").value = "";
}

let interval;

function formatSeconds(seconds) {
  if (seconds < 60) {
    return `0:${seconds < 10 ? 0 : ""}${seconds}`;
  }
  const rest = seconds % 60;

  return `${(seconds - (seconds % 60)) / 60}:${rest < 10 ? 0 : ""}${rest}`;
}

function startTimer() {
  let currentSeconds = 0;
  interval = setInterval(() => {
    currentSeconds += 1;
    document.getElementById("timer").innerText = formatSeconds(currentSeconds);
  }, 1000);
}

function resetTimer() {
  if (interval) clearInterval(interval);
  startTimer();
}

function stopTimer() {
  if (interval) clearInterval(interval);
  document.getElementById("timer").innerText = "";
}

for (let x = 7; x >= 0; x--) {
  for (let y = 0; y < 8; y++) {
    const element = document.createElement("div");

    element.addEventListener("click", () => {
      onCellClicked(x, y);
    });

    if ((x % 2 == 1 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 1)) {
      element.classList.add("white");
    } else {
      element.classList.add("black");
    }

    cells[x].push(element);
  }
}

disableButton("startGameButton");
disableButton("startGameOverButton");
disableButton("startGameOnlineButton");
showMessage("Enter usernames to start the game");
initializeBoard();

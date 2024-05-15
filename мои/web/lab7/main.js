let board = Array(9).fill(null); // Инициализация игрового поля
let currentPlayer = 'X'; // Текущий игрок (X или O)
let choise = 0; // Переменная для хранения выбора
let winner = null; // Победитель игры
let players = []; // Массив для хранения имен игроков
let stats = {}; // Объект для хранения статистики игроков
let lastNumber; // Последнее сгенерированное число

// Функция для генерации случайного числа
function random() {
  let choice;
  do {
    choice = Math.floor(Math.random() * 101);
  } while (choice === lastNumber);
  lastNumber = choice;
  return choice;
}

// Функция для проверки победителя
function checkWinner() {
  const lines = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6],
  ];
  for (let i = 0; i < lines.length; i++) {
    const [a, b, c] = lines[i];
    if (board[a] && board[a] === board[b] && board[a] === board[c]) {
      winner = currentPlayer === 'X' ? players[1] : players[0];
      stats[winner] = stats[winner] ? stats[winner] + 1 : 1;
      return;
    }
  }
  // Проверка на ничью
  if (board.every(cell => cell !== null)) {
    winner = 'Ничья';
    stats[winner] = stats[winner] ? stats[winner] + 1 : 1;
  }
}

// Функция обработки клика по клетке
function handleClick(i) {
  if (board[i] || winner) {
    return;
  }
  board[i] = currentPlayer;
  document.getElementById('log-list').innerHTML += `<li>${currentPlayer} походил на клетку ${i + 1}</li>`;
  currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
  checkWinner();
}

// Функция для отображения состояния игры
function render() {
  let blocks = document.querySelectorAll('.block');
  for (let i = 0; i < blocks.length; i++) {
    blocks[i].innerText = board[i];
    blocks[i].onclick = () => handleClick(i);
  }
  let status = document.getElementById('status');
  if (winner) {
    status.innerText = 'Победитель: ' + winner;
  } else {
    status.innerText = 'Сейчас ходит: ' + (currentPlayer === 'X' ? players[0] : players[1]);
  }
}

// Начальная загрузка игры
window.onload = function() {
  // Кнопка начала игры
  document.getElementById('play-button').onclick = function() {
    document.getElementById('start-screen').style.display = 'none';
    document.getElementById('nickname-screen').style.display = 'block';
  };
  // Кнопка статистики
  document.getElementById('stats-button').onclick = function() {
    document.getElementById('start-screen').style.display = 'none';
    document.getElementById('stats-screen').style.display = 'block';
    let statsText = '';
    for (let player in stats) {
      statsText += player + ': ' + stats[player] + '\n';
    }
    document.getElementById('stats').innerText = statsText;
  };
  // Кнопка начала новой игры
  document.getElementById('start-game-button').onclick = function() {
    players[0] = document.getElementById('player1').value;
    players[1] = document.getElementById('player2').value;
    document.getElementById('nickname-screen').style.display = 'none';
    document.getElementById('game-screen').style.display = 'block';
    document.getElementById('game-log').style.display = 'block';
    render();
  };
  // Кнопка перезапуска игры
  document.getElementById('restart-game-button').onclick = function() {
    choise = random();
    players = choise % 2 === 0 ? [players[0], players[1]] : [players[1], players[0]];
    currentPlayer = 'X'; // Всегда начинаем с крестика
    board = Array(9).fill(null);
    winner = null;
    document.getElementById('log-list').innerHTML = '';
    render();
  };
  // Кнопка возврата в начальное меню
  document.getElementById('back-button').onclick = function() {
    document.getElementById('stats-screen').style.display = 'none';
    document.getElementById('start-screen').style.display = 'block';
  };
  // Кнопка возврата на стартовый экран
  document.getElementById('back-to-start').onclick = function() {
    document.getElementById('game-screen').style.display = 'none';
    document.getElementById('start-screen').style.display = 'block';
  };
  // Кнопка сброса статистики
  document.getElementById('reset-stats').onclick = function() {
    stats = {};
    let statsText = '';
    for (let player in stats) {
      statsText += player + ': ' + stats[player] + '\n';
    }
    document.getElementById('stats').innerText = statsText;
  };
};

// Функция для обновления состояния игры каждые 500 мс
setInterval(render, 500);

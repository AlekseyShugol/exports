document.getElementById('task1').onclick = function() {
    let str1 = prompt("Введите первую строку:");
    let str2 = prompt("Введите вторую строку:");
    let sortedStr1 = str1.split('').sort().join('');//просто сортируем буквы в алфавитном порядке
    let sortedStr2 = str2.split('').sort().join('');
    console.log("Задание 1:");//местный вывод
    console.log("Строка 1: "+str1);
    console.log("Строка 2: "+str2);
    console.log("Результат: "+(sortedStr1===sortedStr2))
}

document.getElementById('task2').onclick = function() {
    console.log("Задание 2:")
    let array = [1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1,0,54,654,32,345,65,34,7]
    for (let i = 0; i < array.length; i++) {
      setTimeout(function() {
        console.log(array[i]);
      }, 3000 * i);
    }
  };
  
//задание 3
document.getElementById('task3').onclick = function() {
    document.getElementById('task3').onclick = function() {
        console.log("\n");
        console.log("Задание 3:");
        var array = [1,2,3,4,7,1,5,4,6,7,8,9,7,99,0,99];
        var uniqueValues = [];
        for(var i=0;i<array.length;i++){
            var current = array[i];
            var count = 0;
            for(var j = 0;j<array.length;j++)
            {
                if(current==array[j]){
                   count++;
                }
            }
            if(count == 1){
                uniqueValues.push(current);
            }
        }
        console.log(uniqueValues);
    }
}
    

function findUniqueValues(array){
    let uniqueValues = {};
    let result = [];
    for (let i = 0; i < array.length; i++) {
        let current = array[i];
        if (uniqueValues[current] === undefined) {
            uniqueValues[current] = 1;
            result.push(current);
        } else {
            continue; // пропустить повторяющиеся значения
        }
    }
    return uniqueValues;
}





//задание 4

document.getElementById('task4').onclick = function() {
        console.log("Задание 4");
        let array = [7, 3, 2, 9, 5, 4, 17];
        console.log("Исходный массив: ");
        console.log(array);
        mySort(array);
        console.log("Отсортированный массив(в котором отсортированы все нечетные числа по возрастанию,\n" +
           "четные числа по убыванию, но при этом сами чётные и нечетные числа остаются на своих местах: ");
           console.log(array)
}
function mySort(array){
    let buf;
    for(let i = 0; i < array.length; i++){
        for(let j = i+1; j < array.length; j++){
          if(array[i] < array[j] && array[i] % 2 === 0 && array[j] % 2 === 0){
            buf = array[i];
            array[i] = array[j];
            array[j] = buf;
          }else if(array[i] > array[j] && array[i] % 2 != 0 && array[j] % 2 != 0){
            buf = array[i];
            array[i] = array[j];
            array[j] = buf;
          }
        }
    }
    return array;
}


document.getElementById('task5').onclick = function() {
    let time = prompt("Введите время до взрыва");
    const bomb = new Bomb(time);
    bomb.start();
}
// Определяем функцию-конструктор Bomb, которая создает объекты-бомбы
function Bomb(timeInSeconds) {
    this.time = timeInSeconds; // Устанавливаем время до взрыва
}

// Добавляем метод start() в прототип объекта Bomb
Bomb.prototype.start = function() {
    console.log("Бомба запущена."); 
    const self = this; // Сохраняем ссылку на объект this, чтобы она была доступна внутри setInterval

    //замыкание
    function tick() {
        self.time--; // Уменьшаем время до взрыва на 1 секунду
        console.log("Осталось времени: " + self.time + " секунд.");

        // Если время истекло
        if (self.time <= 0) {
            clearInterval(countdown); // Останавливаем интервал
            self.explode(); // Вызываем метод explode()
        }
    }

    tick(); 
    const countdown = setInterval(tick, 1000); // Устанавливаем интервал для вызова функции tick() каждую секунду
};
// Добавляем метод explode() в прототип объекта Bomb
Bomb.prototype.explode = function() {
    console.log("Взрыв!"); // Выводим сообщение о взрыве в консоль
};


document.getElementById('task6').onclick = function() {
    const unsortedDates = ['2024-03-15', '2024-03-10', '2024-03-20', '2024-03-05','1234-03-09','2023-02-02'];
    console.log(unsortedDates);
    const sortedDates = sortDates(unsortedDates);
    console.log(sortedDates);
}
// Функция компаратора для сравнения двух дат
function compareDates(a, b) {
    const dateA = new Date(a);
    const dateB = new Date(b);
    
    if (dateA < dateB) {
        return -1; 
    } else if (dateA > dateB) {
        return 1; 
    } else {
        return 0; 
    }
}
// Функция сортировки массива дат
function sortDates(dates) {
    dates.sort(compareDates); // Используем функцию компаратора для сортировки массива дат
    return dates; 
}


document.getElementById('task7').onclick = function() {
    console.log("f(2,3): " + f(2,3));
    console.log("f(2)(3): " + f(2)(3));
};

function f(x, y) {
    if (y === undefined) {
        return function(y) {
            return x + y;
        };
    } else {
        return x + y;
    }
}

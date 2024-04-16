document.getElementById('task1').onclick = function() {
    let str1 = prompt("Введите первую строку:");
    let str2 = prompt("Введите вторую строку:");
    let sortedStr1 = str1.split('').sort().join('');
    let sortedStr2 = str2.split('').sort().join('');
    console.log("Задание 1:");
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
  

document.getElementById('task3').onclick = function() {
    console.log("\n");
    console.log("Задание 3:");
    let max = 10;
    let min = -100;
    let array = [];
    let length =  Math.floor(Math.random() * (max + 1)) ;
    console.log("Размер сгенерированного массива массива: "+length);

    for(let i = 0; i < length; i++){
        let number = getRandomNumber(-10,100);
        array.push(number);
    }
    console.log("Исходный массив(сгенерированный): "+array);
    console.log(findUniqueValues(array));
    console.log("\n");
    let myArray = [1,2,3,4,5,6,7,7,7,7,6,8,99,8,87,NaN];
    console.log("Массив,заданный вручную: "+ myArray);
    console.log(findUniqueValues(myArray));

}
function getRandomNumber(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min + Date.now() % 1000; 
}

function findUniqueValues(array){
 let uniqueValues = [];
 //проходимся по исходному массиву
    for (let i = 0; i < array.length; i++) {
        let current = array[i];
        let isUnique = true;
        //сравниваем текущее число и элементы массива
        for (let j = 0; j < uniqueValues.length; j++) {
            if (current === uniqueValues[j]) {
                //проходимся по массиву с уникальными элементами
                console.log("Элемент "+uniqueValues[j]+ " не является исключительным")
                    isUnique = false;
                    break;
                }
                //проверка на то, является ли уникальное число уникальным на самом деле
                for(let k = 0;k < uniqueValues.length;k++){
                    if(current===uniqueValues[k]){
                        console.log("Элемент "+uniqueValues[k]+ " не является исключительным")
                        isUnique = false;
                        uniqueValues.splice(k, 1);//если нет, то удаляем его
                        break;
                    }
                
            }
        }
        if (isUnique) {
            uniqueValues.push(current);
        }
    }
    return uniqueValues;
}


document.getElementById('task4').onclick = function() {
        console.log("Задание 4");
        let array = [7, 3, 4, 9, 5, 2, 17];
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

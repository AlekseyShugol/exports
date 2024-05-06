// Конструктор для создания объекта калькулятора
function Calculator() {
    this.display = document.getElementById('display'); // Получаем элемент дисплея
    this.buttons = Array.from(document.querySelectorAll('button')); // Получаем все кнопки и преобразуем их в массив
    this.memory = 0; // Инициализируем память калькулятора
    this.currentInput = '0'; // Инициализируем текущий ввод
    this.operator = null; // Инициализируем текущий оператор
    this.initialize(); // Вызываем метод инициализации калькулятора
}

// Метод для инициализации калькулятора
Calculator.prototype.initialize = function() {
    this.display.value = this.currentInput; // Устанавливаем начальное значение дисплея
    var that = this; // Сохраняем контекст this в переменной that для использования внутри функции обратного вызова
    this.buttons.forEach(function(button) { 
        button.addEventListener('click', function(event) { //обработчик события click.
            that.handleButtonClick(event); // который вызывает метод handleButtonClick при нажатии на кнопку
        });
    });

    // Добавляем обработчик событий клавиатуры
    window.addEventListener('keydown', function(event) {
        event.preventDefault(); // Предотвращаем стандартное поведение
        that.handleKeyPress(event);
    });
}

// Метод для очистки калькулятора
Calculator.prototype.clear = function() {
    this.currentInput = '0'; // Сбрасываем текущий ввод
    this.memory = '0'; // Сбрасываем память
    this.operator = null; // Сбрасываем оператор
};

// Метод для обработки нажатия кнопки
Calculator.prototype.handleButtonClick = function(event) {
    const value = event.target.innerText; // Получаем значение кнопки

    // Проверяем, является ли значение числом или точкой
    if (!isNaN(value) || value === '.') {
        this.inputDigit(value); // Если это число или точка, вызываем метод inputDigit
    } else {
        // Если это не число и не точка, то это оператор или другое действие
        let firstOperand;
        switch (value) {
            case '+':
            case '-':
            case '*':
            case '/':
                this.operator = value; // Сохраняем оператор
                this.memory = this.currentInput; // Сохраняем текущий ввод в памяти
                this.currentInput = ''; // Сбрасываем текущий ввод
                break;
            case '=':
                this.calculate(); // Вычисляем результат
                break;
            case 'C':
                this.clear(); // Очищаем калькулятор
                break;
            case 'CE':
                this.currentInput = '0';
                break;
            case '√':
                if( this.currentInput>0){
                    this.currentInput = Math.pow(this.currentInput,1/2);
                }else{
                    console.log('Ошибка: комплексные числа неподдерживается');
                    return;
                }
                break;
            case '%':
                this.currentInput = this.applyPercentage();
                break;
            case 'x²':
                this.currentInput = Math.pow(this.currentInput,2);
                break;
            case '±':
                this.currentInput -= 2*this.currentInput;
                break;
            case '←':
                this.currentInput = this.currentInput.slice(0, -1);
                if(this.currentInput.length==0)
                {
                    this.currentInput = "0";
                }
                break;
            case '1/x':
                this.currentInput = 1/this.currentInput;
                break;
            default:
                console.log(`Неизвестное действие: ${value}`); // Выводим сообщение об ошибке для неизвестных действий
        }
    }
    this.display.value = this.currentInput; // Обновляем дисплей с текущим вводом
};

// Метод для ввода чисел и точки
Calculator.prototype.inputDigit = function(digit) {
    if (this.currentInput === '0' && digit !== '.') { // Если текущий ввод - это 0 и введенная цифра не точка, заменяем его на введенную цифру
        this.currentInput = digit;
    } else {
        if (digit === '.' && this.currentInput.includes('.')) { // Если ввод уже содержит точку, не добавляем еще одну
            return;
        }
        this.currentInput += digit; // В противном случае добавляем цифру или точку к текущему вводу
    }
};

// Метод для выполнения вычислений
Calculator.prototype.calculate = function() {
    if (this.operator !== null && this.memory !== null) {
        let result;
        switch (this.operator) {
            case '+':
                result = parseFloat(this.memory) + parseFloat(this.currentInput);
                break;
            case '-':
                result = parseFloat(this.memory) - parseFloat(this.currentInput);
                break;
            case '*':
                result = parseFloat(this.memory) * parseFloat(this.currentInput);
                break;
            case '/':
                if (this.currentInput !== '0') {
                    result = parseFloat(this.memory) / parseFloat(this.currentInput);
                } else {
                    console.log('Ошибка: деление на ноль');
                    return;
                }
                break;
            default:
                console.log(`Неизвестный оператор: ${this.operator}`);
                return;
        }
        this.currentInput = String(result);
        this.memory = null;
        this.operator = null;
    }
};

// Метод для применения процентов
Calculator.prototype.applyPercentage = function() {
    if (this.operator !== null && this.memory !== null) {
        let result;
        switch (this.operator) {
            case '+':
            case '-':
                result = parseFloat(this.memory) * parseFloat(this.currentInput) / 100;
                break;
            case '*':
                result = parseFloat(this.currentInput) / 100;
                break;
            case '/':
                if (this.currentInput !== '0') {
                    result = 100 / parseFloat(this.currentInput);
                } else {
                    console.log('Ошибка: деление на ноль');
                    return;
                }
                break;
            default:
                console.log(`Неизвестный оператор: ${this.operator}`);
                return;
        }
        return String(result);
    }else{
       return String("0");
    }
};

// Метод для обработки нажатия клавиши
Calculator.prototype.handleKeyPress = function(event) {
    const key = event.key; // Получаем значение нажатой клавиши

    // Проверяем, является ли значение числом или точкой
    if (!isNaN(key) || key === '.') {
        this.inputDigit(key); // Если это число или точка, вызываем метод inputDigit
    } else {
        // Если это не число и не точка, то это оператор или другое действие
        switch (key) {
            case '+':
            case '-':
            case '*':
            case '/':
                this.operator = key; // Сохраняем оператор
                this.memory = this.currentInput; // Сохраняем текущий ввод в памяти
                this.currentInput = ''; // Сбрасываем текущий ввод
                break;
            case 'Enter': // Обрабатываем нажатие клавиши Enter как равно
                this.calculate(); // Вычисляем результат
                break;
            case 'Backspace': // Обрабатываем нажатие клавиши Backspace как удаление последнего символа
                this.currentInput = this.currentInput.slice(0, -1);
                break;
        }
    }
    this.display.value = this.currentInput; // Обновляем дисплей с текущим вводом
};

window.onload = function() {
    calculator = new Calculator(); // Создаем экземпляр калькулятора при загрузке страницы
};


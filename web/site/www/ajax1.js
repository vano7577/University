// 2. Создание переменной request
//const php = require('E:first.php');
var request = new XMLHttpRequest();
// 3. Настройка запроса
if(request.open('GET','E:/Vano/proga/sql/web/first.php',true)
){console.log("hi!")}
// 4. Подписка на событие onreadystatechange и обработка его с помощью анонимной функции
request.addEventListener('readystatechange', function() {
  // если состояния запроса 4 и статус запроса 200 (OK)
  if ((request.readyState==4) && (request.status==200)) {
    // например, выведем объект XHR в консоль браузера
    console.log(request);
    // и ответ (текст), пришедший с сервера в окне alert
    console.log(request.responseText);
    // получить элемент c id = welcome
    var welcome = document.getElementById('welcome');
    // заменить содержимое элемента ответом, пришедшим с сервера
    welcome.innerHTML = request.responseText;
  }
}); 
// 5. Отправка запроса на сервер
request.send();
<?php
// Соединяемся, выбираем базу данны
$link = mysqli_connect("127.0.0.1", "root", "0501", "shop");

if (!$link) {
    echo "Ошибка: Невозможно установить соединение с MySQL." . PHP_EOL;
    echo "Код ошибки errno: " . mysqli_connect_errno() . PHP_EOL;
    echo "Текст ошибки error: " . mysqli_connect_error() . PHP_EOL;
    exit;
}
echo "Соединение с MySQL установлено!" . PHP_EOL;
echo "Информация о сервере: " . mysqli_get_host_info($link) . PHP_EOL;

// Set the variables for the person we want to add to the database

$name = "Ebola";
$price = 55000.00;
$discount = 0.005;
$picture = 1;
    // создание строки запроса
    $query ="INSERT INTO product VALUES (NULL, '$name', '$price', '$discount', '$picture')";
     
    // выполняем запрос
    $result = mysqli_query($link, $query) or die("Ошибка " . mysqli_error($link)); 
    if($result)
    {
        echo "Данные добавлены";
    }
    // закрываем подключение
    mysqli_close($link);
?>
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

/* Select запросы возвращают результирующий набор */
if ($result = mysqli_query($link, "SELECT id, date, delivery FROM `order` WHERE user_id = 1")) {   
    while($row = mysqli_fetch_assoc($result))
        $test[] = $row; 
    print json_encode($test);
    /* очищаем результирующий набор */
    mysqli_free_result($result);
}
mysqli_close($link);
?>
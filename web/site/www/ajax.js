$.ajax({
  url:    'first.php', //url страницы (action_ajax_form.php)
  type:     "POST", //метод отправки
  //dataType: "html", //формат данных
 // data: $("#"+ajax_form).serialize(),  // Сеарилизуем объект
  success: function(response) { //Данные отправлены успешно
    result = $.parseJSON(response);
    $('#result_form').html('Имя: '+result.name+'<br>Телефон: '+result.price);
},
error: function(response) { // Данные не отправлены
      $('#result_form').html('Ошибка. Данные не отправлены.');
}
});
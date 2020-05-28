
function AJAXsend(your_php_file){
  $(document).ready(function(){
  $.ajax ({
    url: your_php_file,
    type: 'GET',
    cache: false,
    dataType: 'html',
    success: function(data_json){
     const data = JSON.parse(data_json);
    $(".cap1").html(data[0].name)
    $(".cap2").append(data[1].name)
    $(".cap3").append(data[2].name)
    $("#welcome1").append("Цена: " + data[0].price)
    $("#welcome2").html("Цена: " + data[1].price)
    $("#welcome3").html("Цена: " + data[2].price)
    }
  })})
  return false; 
}

AJAXsend('first.php');

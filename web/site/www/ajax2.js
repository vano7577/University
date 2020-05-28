 // принцип	тот же самый что и у обычного POST	запроса 
 const request = new XMLHttpRequest();
 const url = "first.php";
 const params = "id_product=" + "&qty_product=";
  
 //	Здесь нужно указать в каком формате мы будем принимать данные вот и все	отличие 
 request.responseType =	"json";
 request.open("POST", url, true);
 request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  
 request.addEventListener("readystatechange", () => {
  
     if (request.readyState === 4 && request.status === 200) {
         let obj = request.response;
        
     console.log(obj);       
     // Здесь мы можем обращаться к свойству объекта и получать	его значение  
     }
 });
  
 request.send(params);
function sendPic()
{
   var email = document.getElementById("email").value;
   if (email.indexOf("@") > -1 && email.indexOf(".") > -1)
   {
   
     var req = new XMLHttpRequest();
     req.onreadystatechange = function() {
       if (req.readyState == 4 && req.status == 200) {
         if (req.responseText == "Sent")
         {
           document.getElementById("status").innerHTML = "<span style='color: green;'>" + "Sent photo of LED" + "</span>";
         }
         else
         {
           document.getElementById("status").innerHTML = "<span style='color: red;'>" + "Failed to send photo of LED" + "</span>";
         }    
       }
     };
     req.open("GET", "sendpic?email=" + email, true);
     req.send();
     document.getElementById("status").innerHTML = "<span style='color: green;'>" + "Sending photo of LED..." + "</span>";
   }
   else
   {
     document.getElementById("status").innerHTML = "<span style='color: red;'>" + "Invalid Email address" + "</span>";
   }
}

function changeLEDStatus(command)
{
  var commandtoDisplay = {turnon: "Turned on LED", turnoff: "Turned off LED"};
  var req = new XMLHttpRequest();
  req.onreadystatechange = function() {
    if (req.readyState == 4 && req.status == 200)
    {
      console.log("HI");
      if (command != "check" && command != "toggle")
      {
        document.getElementById("status").innerHTML = "<span style='color: green;'>" + commandtoDisplay[command] + "</span>";
      }
      else
      {
        document.getElementById("status").innerHTML = "<span style='color: green;'>" + req.responseText + "</span>"; 
      }   
    }
  };
  req.open("GET", "http://220.244.56.8:8080/?command=" + command , true);
  req.send();
}

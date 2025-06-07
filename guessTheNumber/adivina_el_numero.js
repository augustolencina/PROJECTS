var intentos = 10;
var num_intentados = [];
var numero_js = Math.floor(Math.random() * 100) + 1;

function generarNumeroAleatorio() {
    var resultado_obj = document.getElementById("resultado");
    var numero = parseInt(document.getElementById("adivinarNum").value);
    var lista_intentados = document.getElementById("intentados");

    if(num_intentados.includes(numero)) {
        resultado_obj.innerHTML = "Ya ingresaste este numero. Proba con otro.";
    }

    num_intentados.push(numero);

    if(numero == numero_js) {
        resultado_obj.innerHTML = "Adivinaste el numero!";
    }
    else {
        intentos--;
        if(intentos > 0) {
            var aviso = "No adivinaste! ";
            if(numero > numero_js) {
                aviso += " El numero es menor. ";
            }
            else {
                aviso += " El numero es mayor. ";
            }
            aviso += "Te quedan " + intentos + " intentos. ";
            resultado_obj.innerHTML = aviso;
        }
        else {
            resultado_obj.innerHTML = "Te quedaste sin intentos! El numero era: " + numero_js;
        }
    }
    lista_intentados.innerHTML = num_intentados.join(", ");
}
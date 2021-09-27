
//var ws = new WebSocket('ws://'+self.location.host+'/','web-protocol');
var ws = new WebSocket('ws://127.0.0.1:9002/','web-protocol');

var nome, cognome;

//QUI RICEVE LA RISPOSTA DA CPP
ws.onmessage = function(event) {
   var risposta = event.data;
   if (document.getElementById("consegna").style.display=="block") {
        if (risposta=="consegnato") return consegnato();
        else if (risposta=="help") return help();
        else document.getElementById("transito").innerHTML = '<h3> OK,Ricevuto </h3>';
   }
   else {
        document.getElementById("titolo1").innerHTML="Hai effettuato l'accesso nella stanza: ";
        document.getElementById("stanza-log").style.display="block";
        document.getElementById("stanza-log").innerHTML = risposta;
        document.getElementById("titolo2").innerHTML="Attendi l'arrivo del robot ed inizia subito a spedire pacchi! ";
        document.getElementById("form-id").style.display="none";
        document.getElementById("main").padding="200px";
        document.getElementById("consegna").style.display="block"; 
        if (nome && cognome) {
            console.log(nome);
            console.log(cognome);
            document.getElementById("utente").style.display = "block";
            document.getElementById("utente").innerHTML = "<img src='image.png' style='height:25px;widht:25px;margin-top:10px'></img><span style='top:10px;'>&nbsp"+nome+" "+cognome+"</span>";
        }
    }
}

//QUI INVIA LA STANZA AL CPP
function sendPacket(packet) {
    ws.send(packet);
}

function Accedi() {
    nome = document.getElementById("name").value;
    cognome = document.getElementById("surname").value;
    var stanza;
    var cnt=0;
    var giusta;
    stanza = document.getElementsByName("stanza");
    for (var i=0; i<stanza.length;i++) {
        if (stanza[i].checked) {
            cnt+=1;
            if (cnt==1) {
                giusta = stanza[i];
            }
            console.log(stanza[i].value);
        }
    }
    if (cnt==0) {
        alert("Scegliere almeno una stanza in cui fare l'accesso");
        return false;
    }
    if (cnt>1) {
        alert("Scegliere solo una stanza in cui fare l'accesso");
        return false;
    }
    else {
        sendPacket(giusta.value);//+"-"+document.getElementById("stanza-log"));
    }
}

function Spedisci() {
    var stanza;
    var cnt=0;
    var giusta;
    stanza = document.getElementsByName("stanza2");
    for (var i=0; i<stanza.length;i++) {
        if (stanza[i].checked) {
            cnt+=1;
            if (cnt==1) {
                giusta = stanza[i];
            }
            console.log(stanza[i].value);
        }
    }
    if (cnt==0) {
        alert("Scegliere almeno una stanza in cui spedire il pacco");
        return false;
    }
    if (cnt>1) {
        alert("Scegliere solo una stanza in cui in cui spedire il pacco");
        return false;
    }
    else {
        sendPacket(giusta.value);
    }
}

function validaStanza2() {
    var stanza; var cnt;
    stanza = document.getElementsByName("stanza");
    for (var i=0; i<stanza.length;i++) {
        if (stanza[i].checked) {
            cnt+=1;
        }
    }
    if (cnt==0) {
        alert("Scegliere almeno una stanza in cui fare l'accesso");
        return false;
    }
    if (cnt>1) {
        alert("Scegliere solo una stanza in cui fare l'accesso");
        return false;
    }
    return true;
}

function richiamaRobot() {
    attesaRobot();
    var stanza_log = document.getElementById("stanza-log").innerHTML;
    sendPacket(stanza_log+":"+"chiamata.");
}

function attesaRobot() {
    document.getElementById("attesa").innerHTML = '<h3> Attendi che il robot arrivi o che sia disponibile... <br>Immetti il pacco sul ROBOT e seleziona la destinazione del pacco da spedire </h3>';
    setTimeout(() => {
        document.getElementById("attesa").innerHTML = '<h3> Immetti il pacco sul ROBOT e seleziona la destinazione del pacco da spedire </h3>';
      },10000);
   
}

function consegnato() {
    document.getElementById("transito").innerHTML = '<h3> Pacco ricevuto! </h3>';
}

function help() {
    document.getElementById("transito").innerHTML = '<h3> Nessuna persona è presente nella stanza indicata </h3>';
}

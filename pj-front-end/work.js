var clk = 0, maxclk = 50;
var f = 10, maxf = 50;
var on = 0;
var bar, bar2;
var line, line2;
var data = [];

//update module

function updatef() {
    var id = document.getElementById("f");
    var length = f / maxf * $(bar).width();
    if(f == 0)  f = 1;
    if(length < 0) {
        length = 0;
        f = 1;
    }
    if(length > $(bar).width()){
        $(line).width($(bar).width());
        f = maxf;
    }
    id.innerHTML = "f=" + f + "/" + maxf;
    $(line).width(length);
}

function updateclk() {
    var id = document.getElementById("clock");
    if(clk == maxclk && on == 1)
        PlayPause();
    var length = clk / maxclk * $(bar2).width();
    if(length < 0) {
        length = 0;
        clk = 0;
    }
    if(length > $(bar2).width()){
        $(line2).width($(bar2).width());
        clk = maxclk;
    }
    id.innerHTML = "CLOCK=" + clk + "/" + maxclk;
    $(line2).width(length);
    /*
    document.getElementById("z1").innerHTML = data[clk][0];
    document.getElementById("z2").innerHTML = data[clk][1];
    document.getElementById("z3").innerHTML = data[clk][2];
    document.getElementById("r1").innerHTML = data[clk][3];
    document.getElementById("r2").innerHTML = data[clk][4];
    document.getElementById("r3").innerHTML = data[clk][5];
    document.getElementById("r4").innerHTML = data[clk][6];
    document.getElementById("r5").innerHTML = data[clk][7];
    document.getElementById("r6").innerHTML = data[clk][8];
    document.getElementById("r7").innerHTML = data[clk][9];
    document.getElementById("r8").innerHTML = data[clk][10];
    document.getElementById("mi1").innerHTML = data[clk][11];
    document.getElementById("mv1").innerHTML = data[clk][12];
    document.getElementById("mi2").innerHTML = data[clk][13];
    document.getElementById("mv2").innerHTML = data[clk][14];
    document.getElementById("mi3").innerHTML = data[clk][15];
    document.getElementById("mv3").innerHTML = data[clk][16];
    document.getElementById("mi4").innerHTML = data[clk][17];
    document.getElementById("mv4").innerHTML = data[clk][18];
    document.getElementById("mi5").innerHTML = data[clk][19];
    document.getElementById("mv5").innerHTML = data[clk][20];
    document.getElementById("mi6").innerHTML = data[clk][21];
    document.getElementById("mv6").innerHTML = data[clk][22];
    document.getElementById("f1").innerHTML = data[clk][23];
    document.getElementById("f2").innerHTML = data[clk][24];
    document.getElementById("f3").innerHTML = data[clk][25];
    document.getElementById("d1").innerHTML = data[clk][26];
    document.getElementById("d2").innerHTML = data[clk][27];
    document.getElementById("d3").innerHTML = data[clk][28];
    document.getElementById("d4").innerHTML = data[clk][29];
    document.getElementById("d5").innerHTML = data[clk][30];
    document.getElementById("d6").innerHTML = data[clk][31];
    document.getElementById("e1").innerHTML = data[clk][32];
    document.getElementById("e2").innerHTML = data[clk][33];
    document.getElementById("e3").innerHTML = data[clk][34];
    document.getElementById("e4").innerHTML = data[clk][35];
    document.getElementById("e5").innerHTML = data[clk][36];
    document.getElementById("e6").innerHTML = data[clk][37];
    document.getElementById("e7").innerHTML = data[clk][38];
    document.getElementById("e8").innerHTML = data[clk][39];
    document.getElementById("e9").innerHTML = data[clk][40];
    document.getElementById("m1").innerHTML = data[clk][41];
    document.getElementById("m2").innerHTML = data[clk][42];
    document.getElementById("m3").innerHTML = data[clk][43];
    document.getElementById("m4").innerHTML = data[clk][44];
    document.getElementById("m5").innerHTML = data[clk][45];
    document.getElementById("m6").innerHTML = data[clk][46];
    document.getElementById("m7").innerHTML = data[clk][47];
    document.getElementById("w1").innerHTML = data[clk][48];
    document.getElementById("w2").innerHTML = data[clk][49];
    document.getElementById("w3").innerHTML = data[clk][50];
    document.getElementById("w4").innerHTML = data[clk][51];
    document.getElementById("w5").innerHTML = data[clk][52];
    document.getElementById("w6").innerHTML = data[clk][53];
    */
}

//button module

var timeid = 0;

function timecount() {
    if(clk < maxclk)

        clk += on;
    updateclk();
    timeid = setTimeout("timecount()", 5000 / f);
}

function timestop() {
    if(timeid != 0)
        clearTimeout(timeid);
    timeid = 0;
}

function PlayPause() {
    on = on ^ 1;
    var play = document.getElementById("play");
    var pause = document.getElementById("pause"); 
    if(on == 1) {
        play.style.display = "none";
        pause.style.display = "block";
        timecount();
    }
    else {
        play.style.display = "block";
        pause.style.display = "none";
        timestop();
    }
}

function BackWard() {
    if(on == 1)  PlayPause();
    if(clk > 0) {
        clk = clk - 1;
        updateclk();
    }
}

function ForWard() {
    if(on == 1)  PlayPause();
    if(clk < maxclk) {
        clk = clk + 1;
        updateclk();
    }
}

function getFileContent (fileInput, callback) {
    if (fileInput.files && fileInput.files.length > 0 && fileInput.files[0].size > 0) {
        var file = fileInput.files[0];
        if (window.FileReader) {
            var reader = new FileReader();
            reader.onloadend = function (evt) {
                if (evt.target.readyState == FileReader.DONE) {
                    callback(evt.target.result);
                }
            };
            reader.readAsText(file, 'utf-8');
        }
    }
}

function FileLoad() {
    var bid = document.getElementById("uploadbtn");
    var uid = document.getElementById("upload");
    bid.onclick = function () {
        uid.click();
    };
    uid.onchange = function () {
        if(on == 1)  PlayPause();
        var cid = document.getElementById("code");
        getFileContent(this, function (str) {
            cid.innerHTML = str;
            //alert(str.length);
        });
        /*
        var t1 = 0, t2 = 0;
        maxclk = 0;
        clk = 0;
        while(s[t1] != '(') t1++;
        while(s[t2] != ")") t2++;
        for(i = t1 + 1; i < t2; ++i)
            maxclk = maxclk * 10 + s[i] - '0';
        for(i = 0; i <= maxclk; ++i) {
            for(int j = 0; j < 54; ++j) {
                t1++, t2++;
                while(s[t1] != '(')  t1++;
                while(s[t2] != ')')  t2++;
                data[i][j] = s.substring(t1 + 1, t2 - 1);
            }
        }
        */
       updateclk();
    };
}

//slide module

function slide(bara,linea){
    bar = "." + bara;
    line = "." + linea;
    var statu = false;

    $(bar).mousedown(function (e) {
        ev(e);
    });

    $(document).mouseup(function () {
        statu = false;
    });

    $(bar).mousemove(function (e) {
        if (statu === true) {
            ev(e);
        }
    });

    function ev(e){
        var eleLeft = $(line).offset().left;
        var length = e.pageX - eleLeft;
        if(length > $(bar).width()){
            length = $(bar).width()
        }
        statu = true;
        f = parseInt(length / $(bar).width() * maxf);
        updatef();
    }
}


function slide2(barb,lineb){
    bar2 = "." + barb;
    line2 = "." + lineb;
    var statu2 = false;

    $(bar2).mousedown(function (e) {
        ev(e);
    });

    $(document).mouseup(function () {
        statu2 = false;
    });

    $(bar2).mousemove(function (e) {
        if (statu2 === true) {
            ev(e);
        }
    });

    function ev(e){
        if(on == 1) PlayPause();
        var eleLeft = $(line2).offset().left;
        var length = e.pageX - eleLeft;
        if(length > $(bar2).width()) {
            length = $(bar2).width();
        }
        statu2 = true;
        clk = parseInt(length / $(bar2).width() * maxclk);
        updateclk();
    }
}

input mpcolornames

prologues:=3;

def drawArrow(expr pos, len) =
    begingroup
        pair endpoint;
        endpoint := pos + 0.8(len, 0);

        pair tip;
        tip := pos + (len, 0);

        pair left;
        pair right;

        left = endpoint rotatedabout(tip, 40);
        right = endpoint rotatedabout(tip, -40);

        draw left -- tip;
        draw pos -- tip;
        draw right -- tip;
    endgroup;
enddef;

def drawTriangle(expr pos, len, angle) = 
    begingroup
        pair endpoint;
        endpoint := pos + (len, 0);
        
        pair top;
        top:= endpoint + (0, len/4);

        pair bot;
        bot:= endpoint + (0, -len/4);

        top:= top rotatedabout (pos, angle);
        bot:= bot rotatedabout (pos, angle);

        draw pos--bot--top--pos;
    endgroup;
enddef;

def drawNGon(expr pos, num, NGONLENGTH, triangSize, initialAngle) =
    begingroup
        numeric ANGLE;
        ANGLE = 360 / num;

        pair baseNgon;
        baseNgon:= pos + (0, -NGONLENGTH);
        pair p[];
        pair hlp;

        pickup pencircle scaled .9mm;
        for i=1 upto num:
            p[i]:= baseNgon rotatedabout(pos, initialAngle + ANGLE * i);
            drawTriangle(p[i], triangSize, initialAngle + ANGLE * i - 45);
        endfor;

        draw p[num]--p1;
        for i=2 upto num: draw p[i]--p[i-1]; endfor;

        pickup pencircle scaled 14pt;
        for i=1 upto num: draw p[i]; endfor;

    endgroup;
enddef;

def drawLine(expr pos, distance, len, ANGLE) = 
    begingroup
        pair START;
        START:= pos + (0, -distance);
        pair END;
        END:= pos + (0, -distance - len);

        pair p[];
        p1:= START rotatedabout(pos, ANGLE);
        p2:= END rotatedabout(pos, ANGLE);

        pickup pencircle scaled 0.9mm;
        draw p1--p2;

    endgroup;
enddef;

numeric LabelScale;
LabelScale:= 5;

u:=10mm;
d = 2u;
s = 2.5u;

beginfig(1)

pair orig;
orig:=(0,0);
drawNGon(orig, 3, 3u, 1.8u, -60);
drawLine(orig, 3u, 2u, -60);
drawLine(orig, 3u, 2u, 60);
drawLine(orig, 3u, 2u, 180);

pair base;
base = (0, -3u);

pair e[];
e1:= base rotatedabout((0,0), -60);
e2:= base rotatedabout((0,0), 180);

path p;
p:= e1..e2;

pickup pencircle scaled 2mm;
draw p;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(p)) of p;

path q;
q:= (e1+e2)/2..orig;

ahlength:= 7bp;
pickup pencircle scaled 0.9mm;
drawarrow subpath(0.2,1*length(q)) of q;

labeloffset := 15bp;
label.ulft(btex $e$ etex scaled LabelScale, (e1 + e2) / 2);
label.top(btex next etex scaled 2.5, 0.1*((e1+e2)/2 + orig)) rotatedabout ((e1+e2)/4, angle(-(e1+e2)/2));

pickup pencircle scaled .9mm;
drawArrow((6.5u, 0), 8u);

orig:= orig + (20u, 0);
drawNGon(orig, 3, 3u, 1.8u, -60);
drawLine(orig, 0, 5u, -60);
drawLine(orig, 0, 5u, 60);
drawLine(orig, 0, 5u, 180);


pickup pencircle scaled 14pt;
draw orig;

base:= base + (20u, 0);
e1:= e1 + (20u, 0);
e2:= e2 + (20u, 0);

path p;
p:= e1..e2;

pickup pencircle scaled 2mm;
draw p;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(p)) of p;

label.ulft(btex $e$ etex scaled LabelScale, (e1 + e2) / 2);

endfig;

beginfig(2)

pair orig;
orig:=(0,0);
drawNGon(orig, 4, 3u, 1.8u, -45);
drawLine(orig, 3u, 2u, 45);
drawLine(orig, 3u, 2u, 225);
drawLine(orig, -3u, 6u, -45);

pair base;
base = (0, -3u);

pair e[];
e1:= base rotatedabout((0,0), -45);
e2:= base rotatedabout((0,0), -135);

path p;
p:= e1..e2;

pickup pencircle scaled 2mm;
draw p;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(p)) of p;

pair beginArr;
beginArr:= (e1+e2)/2 + (0, 0.8u);

pair endArr;
endArr:= orig + (0, 0.8u);

path q;
q:= beginArr..endArr;

ahlength:= 7bp;
pickup pencircle scaled 0.9mm;
drawarrow subpath(0.2, 0.8*length(q)) of q;

labeloffset := 5bp;
label.ulft(btex $e$ etex scaled LabelScale, e1 + (e2 - e1) * 0.3);
label.top(btex next etex scaled 2.5, (beginArr+endArr)/2);

pair P[];
for i=1 upto 4: P[i]:= base rotatedabout(origin, -45 + 90 * i); endfor;

path t;
t:= P4..P2;

ahlength:= 16bp;
drawarrow subpath (0, 0.6 * length(t)) of t;
label.lrt(btex $e_2$ etex scaled LabelScale, P[4] + (P[2] - P[4]) * 0.5);

pickup pencircle scaled .9mm;
drawArrow((6.5u, 0), 8u);

orig:= orig + (20u, 0);
base:= base + (20u, 0);
e1:= e1 + (20u, 0);
e2:= e2 + (20u, 0);
p:= e1..e2;

drawNGon(orig, 4, 3u, 1.8u, -45);
drawLine(orig, -3u, 6u, -45);
drawLine(orig, -5u, 10u, 45);

pickup pencircle scaled 14pt;
draw orig;

pickup pencircle scaled 2mm;
draw p;

ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(p)) of p;

label.ulft(btex $e$ etex scaled LabelScale, e1 + (e2 - e1) * 0.3);

endfig;

beginfig(3)

pair orig;
orig:=(0,0);
drawNGon(orig, 5, 5u, 1.8u, -72);
drawLine(orig, 5u, 3u, 72);
drawLine(orig, 5u, 3u, -72);

pair base;
base:= orig + (0, -5u);
pair e[];
for i=1 upto 5: e[i]:= base rotatedabout(orig, -72 + 72 * i); endfor;

pickup pencircle scaled 0.9mm;
draw e3--e1--e4;

path p;
p:= e1..e5;

pickup pencircle scaled 2mm;
draw p;

ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(p)) of p;

ahlength:= 16bp;
pickup pencircle scaled .9mm;
for i=3,4:
    p:=e1..e[i];
    drawarrow subpath (0, 0.6 * length(p)) of p;
endfor;


pair beginArr;
beginArr:= (e1+e5)/2 + 0.3 * (e5 - e1);
pair endArr;
endArr:= orig + 0.3 * (e5 - e1);

path q;
q:= beginArr..endArr;

ahlength:= 7bp;
pickup pencircle scaled 0.9mm;
drawarrow subpath(0.2, 0.7*length(q)) of q;

labeloffset := 5bp;
label.llft(btex $e$ etex scaled LabelScale, e1 + (e5 - e1) * 0.3);
label.top(btex next etex scaled 2.5, (beginArr+endArr)/2) rotatedabout ((beginArr+endArr)/2, angle(endArr - beginArr));
label.rt(btex $e_2$ etex scaled LabelScale, e1 + (e4 - e1) * 0.6);
label.lrt(btex $e_3$ etex scaled LabelScale, e1 + (e3 - e1) * 0.6);

pickup pencircle scaled .9mm;
drawArrow((9u, 0), 8u);

orig:= orig + (26u, 0);

drawNGon(orig, 5, 5u, 1.8u, -72);
drawLine(orig, 5u, 3u, 72);
drawLine(orig, 5u, 3u, -72);

pickup pencircle scaled 14pt;
draw orig;

base:= orig + (0, -5u);
pickup pencircle scaled 0.9mm;
for i=1 upto 5: 
    e[i]:= base rotatedabout(orig, -72 + 72 * i);
    draw e[i]--orig;
endfor;

path p;
p:= e1..e5;

pickup pencircle scaled 2mm;
draw p;

ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(p)) of p;

pair beginArr;
beginArr:= (e1+e5)/2 + 0.3 * (e5 - e1);
pair endArr;
endArr:= orig + 0.3 * (e5 - e1);

labeloffset := 5bp;
label.llft(btex $e$ etex scaled 4, e1 + (e5 - e1) * 0.3);

endfig;

beginfig(4)

pair orig;
orig:=(0,0);
drawNGon(orig, 3, 3u, 1.8u, -60);
drawLine(orig, 3u, 2u, -60);
drawLine(orig, 3u, 2u, 60);
drawLine(orig, 3u, 2u, 180);

pair base;
base = (0, -3u);

pair e[];
for i=1 upto 3: e[i]:= base rotatedabout((0,0), -60 + 120 * i); endfor;

path p;
p:= e2..e1;

pickup pencircle scaled 2mm;
draw p;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(p)) of p;

p:= e1..e3;
draw p;
drawarrow subpath (0, 0.7 * length(p)) of p;
p:= e3..e2;
draw p;
drawarrow subpath (0, 0.7 * length(p)) of p;

labeloffset := 10bp;
label.ulft(btex $e_1$ etex scaled LabelScale, (e3 + e2) / 2);
label.urt(btex $e_2$ etex scaled LabelScale, (e2 + e1) / 2);
label.bot(btex $e_3$ etex scaled LabelScale, (e1 + e3) / 2);
endfig;

beginfig(5)

pair orig;
orig:=(0,0);
drawNGon(orig, 4, 3u, 1.8u, -45);
drawLine(orig, 3u, 2u, 45);
drawLine(orig, 3u, 2u, 225);
drawLine(orig, -3u, 6u, -45);

pair base;
base = (0, -3u);

pair e[];
for i=1 upto 4: e[i]:= base rotatedabout((0,0), -45 + 90 * i); endfor;

path p;
p:= e4..e3;

pickup pencircle scaled 2mm;
draw p;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(p)) of p;

p:=e2..e1;
pickup pencircle scaled 2mm;
draw p;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(p)) of p;

labeloffset := 5bp;
label.lft(btex $e_1$ etex scaled LabelScale, e4 + (e3 - e4) * 0.3);
label.rt(btex $e_2$ etex scaled LabelScale, e1 + (e2 - e1) * 0.7);
endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
beginfig(6)

pair orig;
orig:=(0,0);
drawNGon(orig, 3, 3u, 1.8u, -60);
drawLine(orig, 3u, 2u, -60);
drawLine(orig, 3u, 2u, 60);
drawLine(orig, 3u, 2u, 180);

pair base;
base = (0, -3u);

pair e[];
e1:= base rotatedabout((0,0), -60);
e2:= base rotatedabout((0,0), -180);
e3:= base rotatedabout((0,0), -300);

LabelScale:= 4;
label.ulft(btex $v_1$ etex scaled LabelScale, e1);
label.rt(btex $v_2$ etex scaled LabelScale, e2);
label.llft(btex $v_3$ etex scaled LabelScale, e3);

pickup pencircle scaled .9mm;
drawArrow((6.5u, 1u), 8u);

orig:= orig + (20u, 0);
drawNGon(orig, 3, 3u, 1.8u, -60);
drawLine(orig, 0, 5u, -60);
drawLine(orig, 0, 5u, 60);
drawLine(orig, 0, 5u, 180);

for i=1 upto 3: e[i]:= e[i] + (20u, 0); endfor;

pickup pencircle scaled 14pt;
draw orig;

label.ulft(btex $v_1$ etex scaled LabelScale, e1);
label.rt(btex $v_2$ etex scaled LabelScale, e2);
label.llft(btex $v_3$ etex scaled LabelScale, e3);

labeloffset:= 14bp;
label.bot(btex $v_n$ etex scaled LabelScale, orig);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
beginfig(7)

pair orig;
orig:=(0,0);
drawNGon(orig, 4, 3u, 1.8u, -45);
drawLine(orig, 3u, 2u, 45);
drawLine(orig, 3u, 2u, 225);
drawLine(orig, -3u, 6u, -45);

pair base;
base = (0, -3u);

pickup pencircle scaled 2mm;
pair P[];
for i=1 upto 4: P[i]:= base rotatedabout(origin, -45 + 90 * i); endfor;
draw P[4]--P[2];

LabelScale:= 4;
label.lft(btex $v_1$ etex scaled LabelScale, P[4]);
label.urt(btex $v_2$ etex scaled LabelScale, P[3]);
label.rt(btex $v_3$ etex scaled LabelScale, P[2]);
label.llft(btex $v_4$ etex scaled LabelScale, P[1]);

pickup pencircle scaled .9mm;
drawArrow((6.5u, 0), 8u);

orig:= orig + (20u, 0);
for i=1 upto 4: P[i]:= P[i] + (20u, 0); endfor;

drawNGon(orig, 4, 3u, 1.8u, -45);
drawLine(orig, -3u, 6u, -45);
drawLine(orig, -5u, 10u, 45);

pickup pencircle scaled 14pt;
draw orig;

label.lft(btex $v_1$ etex scaled LabelScale, P[4]);
label.urt(btex $v_2$ etex scaled LabelScale, P[3]);
label.rt(btex $v_3$ etex scaled LabelScale, P[2]);
label.llft(btex $v_4$ etex scaled LabelScale, P[1]);
labeloffset:= 20bp;
label.top(btex $v_n$ etex scaled LabelScale, orig);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
beginfig(8)

pair orig;
orig:=(0,0);
drawNGon(orig, 5, 5u, 1.8u, -72);
drawLine(orig, 5u, 3u, 72);
drawLine(orig, 5u, 3u, -72);

pair base;
base:= orig + (0, -5u);
pair e[];
for i=1 upto 5: e[i]:= base rotatedabout(orig, -72 + 72 * i); endfor;

pickup pencircle scaled 2mm;
draw e3--e1--e4;

LabelScale:= 4;
label.lft(btex $v_1$ etex scaled LabelScale, e1);
label.ulft(btex $v_2$ etex scaled LabelScale, e5);
label.urt(btex $v_3$ etex scaled LabelScale, e4);
label.rt(btex $v_4$ etex scaled LabelScale, e3);
label.bot(btex $v_5$ etex scaled LabelScale, e2);

pickup pencircle scaled .9mm;
drawArrow((9u, 0), 8u);

orig:= orig + (26u, 0);
drawNGon(orig, 5, 5u, 1.8u, -72);
drawLine(orig, 5u, 3u, 72);
drawLine(orig, 5u, 3u, -72);

for i= 1 upto 5:
    e[i]:= e[i] + (26u, 0);
    draw e[i]--orig;
endfor;

label.lft(btex $v_1$ etex scaled LabelScale, e1);
label.ulft(btex $v_2$ etex scaled LabelScale, e5);
label.urt(btex $v_3$ etex scaled LabelScale, e4);
label.rt(btex $v_4$ etex scaled LabelScale, e3);
label.bot(btex $v_5$ etex scaled LabelScale, e2);
labeloffset:= 25bp;
label.top(btex $v_n$ etex scaled LabelScale, orig);

pickup pencircle scaled 14pt;
draw orig;

endfig;

end;
end.

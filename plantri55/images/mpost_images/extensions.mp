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

numeric LabelScale;
LabelScale:= 3.2;

u:=10mm;
d = 2u;
s = 2.5u;

beginfig(1)

pair p[];
p[1]:= (0, 0);
p[2]:= p[1] + (8u, -8u);
p[3]:= p[2] + (8u, 8u);
p[4]:= p[3] + (-8u, 8u);

p[5]:= p[1] + (2.5u, 0);
p[6]:= p[2] + (0, 2.5u);
p[7]:= p[3] + (-2.5u, 0);
p[8]:= p[4] + (0, -2.5u);

pair middle;
middle = (p[1] + p[3])/2;

p[9]:= middle + (-1.2u, -1.2u);
p[10]:= middle + (1.2u, -1.2u);
p[11]:= middle + (1.2u,1.2u);
p[12]:= middle + (-1.2u,1.2u);

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11,12: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p[i+4]--p[i+8]; endfor;

draw p[12]--p[5];

pickup pencircle scaled .9mm;
for i:=6,7,8: draw p[i]--p[i+3]; endfor;

draw p[9]--p[10]--p[11]--p[12]--p[9];
draw p[12]--p[10];

draw p[5]--p[6]--p[7]--p[8]--p[5];

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;

label.llft(btex $v$ etex scaled LabelScale, p5 + (-0.1u, -0.1u));
label.ulft(btex $v_1$ etex scaled LabelScale, p12 + (-0.1, 0.1u));
label.llft(btex $v_2$ etex scaled LabelScale, p9 + (-0.1u, -0.1u));

drawArrow((19u, 0), 8u);

for i:=1,2,3,4,5,6,7,8,9,10,11,12: p[i]:= p[i] + (30u, 0); endfor;
p13:= p5 + (1.5u, 0);

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11,12,13: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=2,3,4: draw p[i]--p[i+4]--p[i+8]; endfor;

draw p1--p5--p13--p12;
draw p13--p9;
draw p8--p13--p6;

pickup pencircle scaled .9mm;
for i:=6,7,8: draw p[i]--p[i+3]; endfor;

draw p[9]--p[10]--p[11]--p[12]--p[9];
draw p[12]--p[10];

draw p[5]--p[6]--p[7]--p[8]--p[5];

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;

label.llft(btex $v$ etex scaled LabelScale, p5 + (-0.1u, -0.1u));
label.ulft(btex $v_1$ etex scaled LabelScale, p12 + (-0.1, 0.1u));
label.llft(btex $v_2$ etex scaled LabelScale, p9 + (-0.1u, -0.1u));

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%B

beginfig(2)

pair p[];
p[1]:= (0, 0);
p[2]:= p[1] + (8u, -8u);
p[3]:= p[2] + (8u, 8u);
p[4]:= p[3] + (-8u, 8u);

p[5]:= p[1] + (2.5u, 0);
p[6]:= p[2] + (0, 2.5u);
p[7]:= p[3] + (-2.5u, 0);
p[8]:= p[4] + (0, -2.5u);

p9:= (p1+p3)/2;

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p[i+4]--p[9]; endfor;

draw p[5]--p[6]--p[7]--p[8]--p[5];

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;

drawArrow((19u, 0), 8u);

for i:=1,2,3,4,5,6,7,8,9: p[i]:= p[i] + (30u, 0); endfor;

pair middle;
middle = (p[1] + p[3])/2;

p[9]:= middle + (-1.2u, -1.2u);
p[10]:= middle + (1.2u, -1.2u);
p[11]:= middle + (1.2u,1.2u);
p[12]:= middle + (-1.2u,1.2u);

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11,12: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p[i+4]--p[i+8]; endfor;

draw p[12]--p[5];

pickup pencircle scaled .9mm;
for i:=6,7,8: draw p[i]--p[i+3]; endfor;

draw p[9]--p[10]--p[11]--p[12]--p[9];
draw p[12]--p[10];

draw p[5]--p[6]--p[7]--p[8]--p[5];

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;

endfig;

beginfig(3)

pair p[];
p[1]:= (0, 0);
p[2]:= p[1] + (8u, -8u);
p[3]:= p[2] + (8u, 8u);
p[4]:= p[3] + (-8u, 8u);

p[5]:= p[1] + (2.5u, 0);
p[6]:= p[2] + (0, 2.5u);
p[7]:= p[3] + (-2.5u, 0);
p[8]:= p[4] + (0, -2.5u);

pair middle;
middle = (p[1] + p[3])/2;

p[9]:= middle + (-1.2u, -1.2u);
p[10]:= middle + (1.2u, -1.2u);
p[11]:= middle + (1.2u,1.2u);
p[12]:= middle + (-1.2u,1.2u);

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11,12: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p[i+4]--p[i+8]; endfor;

draw p[9]--p[11];

pickup pencircle scaled .9mm;
for i:=6,7,8: draw p[i]--p[i+3]; endfor;

draw p[9]--p[10]--p[11]--p[12]--p[9];
draw p[12]--p[5];
draw p9--p11;

draw p[5]--p[6]--p[7]--p[8]--p[5];

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;

label.llft(btex $v_1$ etex scaled LabelScale, p9 + (-0.1u, -0.1u));
label.urt(btex $v_2$ etex scaled LabelScale, p11 + (0.1u, 0.1u));

drawArrow((19u, 0), 8u);

for i:=1,2,3,4,5,6,7,8,9,10,11,12: p[i]:= p[i] + (30u, 0); endfor;
p13:= (p1+p3)/2;

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11,12,13: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p[i+4]--p[i+8]; endfor;

pickup pencircle scaled .9mm;
for i:=6,7,8: draw p[i]--p[i+3]; endfor;

draw p[9]--p[10]--p[11]--p[12]--p[9];
draw p[5]--p[12]--p[10];
draw p9--p11;

draw p[5]--p[6]--p[7]--p[8]--p[5];

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;

label.llft(btex $v_1$ etex scaled LabelScale, p9 + (-0.1u, -0.1u));
label.urt(btex $v_2$ etex scaled LabelScale, p11 + (0.1u, 0.1u));

endfig;

beginfig(4)

pair p[];
p1:= (0,0);
p2:= p1 + (6u,0);
p3:= p1 rotatedabout(p2, 270);

p4:= p2 rotatedabout(p1, 90);
p5:= (p1+p2+p3+p4)/4;

p6:= p3 + (2u,u);

p7:= p5 rotatedabout(p4, 90);
p8:= p4 + (-2u,u);

p9:= p1 + (-2.5u, -2.5u);
p10:= p2 + (2.5u, -2.5u);
p11:= p6 + (2.5u, 2.5u);
p12:= p7 + (0, 2.5u);
p13:= p8 + (-2.5u, 2.5u);

pickup pencircle scaled 14pt;
for i=1 upto 8: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p5; endfor;

draw p1--p2--p3--p4--p1;
draw p8--p7--p6;
draw p4--p7--p3;

for i:=1,2: draw p[i]--p[i+8]; endfor;
for i:=6,7,8: draw p[i]--p[i+5]; endfor;

draw p4--p8--p1;
draw p3--p6--p2;

drawTriangle(p[1], 2u, 280);
drawTriangle(p2, 2u, -100);
drawTriangle(p6, 2u, -20);
drawTriangle(p8, 2u, 200);
drawTriangle(p7, 2u, 50);

label.llft(btex $v_1$ etex scaled LabelScale, p4 + (-0.1u, -0.1u));
label.lrt(btex $v_2$ etex scaled LabelScale, p3 + (0.1u, -0.1u));

drawArrow((12u, 5u), 8u);

for i=1 upto 13: p[i]:= p[i] + (26u, 0); endfor;
p14:= (p3+p4)/2;

pickup pencircle scaled 14pt;
for i=1 upto 8: draw p[i]; endfor;
draw p14;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p5; endfor;

draw p1--p2--p3--p4--p1;
draw p8--p7--p6;
draw p4--p7--p3;
draw p7--p5;

for i:=1,2: draw p[i]--p[i+8]; endfor;
for i:=6,7,8: draw p[i]--p[i+5]; endfor;

draw p4--p8--p1;
draw p3--p6--p2;

drawTriangle(p[1], 2u, 280);
drawTriangle(p2, 2u, -100);
drawTriangle(p6, 2u, -20);
drawTriangle(p8, 2u, 200);
drawTriangle(p7, 2u, 50);

label.llft(btex $v_1$ etex scaled LabelScale, p4 + (-0.1u, -0.1u));
label.lrt(btex $v_2$ etex scaled LabelScale, p3 + (0.1u, -0.1u));

endfig;

beginfig(5)

pair base;
base:= (0,0);

pair baseTrian;
baseTrian:= base + (0, -2u);

pair basePent;
basePent:= base + (0, -5u);

pair p[];

for i=1 upto 3: p[i]:= baseTrian rotatedabout(base, -60 + 120 * i); endfor;
for i=1 upto 5: p[i+3]:= basePent rotatedabout(base, -36 + 72 * i); endfor;

p9:= p4 + (0, -1.8u);
p10:= p9 rotatedabout(p4, 25);

p11:= p6 + (0, 1.8u);
p12:= p7 + (-1.8u, 0);
p13:= p8 + (0,-1.8u);
p14:= p13 rotatedabout(p8, -25);

pickup pencircle scaled 14pt;
for i=1 upto 8: draw p[i]; endfor;

pickup pencircle scaled .9mm;
draw p1--p2--p3--p1;
draw p4--p5--p6--p7--p8--p4;

for i=5 upto 7: draw p[i]--p2; endfor;

draw p12--p7--p3--p8--p1--p4;
draw p1--p5;

draw p6--p11;
draw p9--p4--p10;
draw p13--p8--p14;

drawTriangle(p5, 1.4u, 0);
drawTriangle(p6, 1.4u, 40);
drawTriangle(p7, 1.4u, 115);
drawTriangle(p8, 1.4u, 310);
drawTriangle(p4, 1.4u, -130);

label.rt(btex $v_1$ etex scaled LabelScale, p1 + (0.2u, -0.1u));
label.lft(btex $v_2$ etex scaled LabelScale, p8 + (-0.2u, 0));

drawArrow((8.3u, 0u), 8u);

for i=1 upto 14: p[i]:= p[i] + (25u, 0); endfor;
p15:= (p1+p3+p4+p8)/4;

pickup pencircle scaled 14pt;
for i=1 upto 8: draw p[i]; endfor;
draw p15;

pickup pencircle scaled .9mm;
draw p1--p2--p3--p1;
draw p4--p5--p6--p7--p8--p4;

for i=5 upto 7: draw p[i]--p2; endfor;

draw p12--p7--p3--p8--p15--p1--p4;
draw p1--p5;

draw p3--p15--p4;

draw p6--p11;
draw p9--p4--p10;
draw p13--p8--p14;

drawTriangle(p5, 1.4u, 0);
drawTriangle(p6, 1.4u, 40);
drawTriangle(p7, 1.4u, 115);
drawTriangle(p8, 1.4u, 310);
drawTriangle(p4, 1.4u, -130);

label.rt(btex $v_1$ etex scaled LabelScale, p1 + (0.2u, -0.1u));
label.lft(btex $v_2$ etex scaled LabelScale, p8 + (-0.2u, 0));

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% F
beginfig(6)
pair base;
base:= (0,0);

pair basePent;
basePent:= base + (0, -5u);

pair p[];

for i=1 upto 3: p[i]:= baseTrian rotatedabout(base, -120 + 120 * i); endfor;
for i=1 upto 5: p[i+3]:= basePent rotatedabout(base, -36 + 72 * i); endfor;
p9:= p4 + (0, -1.8u);
p10:= p9 rotatedabout(p4, 25);

p11:= p6 + (0, 2u);
p12:= p7 + (-2u, 0);
p13:= p8 + (0,-2u);
p14:= p13 rotatedabout(p8, -25);
p15:= p5 + (2u, 0);
p16:= p11 rotatedabout(p6, -12.5);
p17:= p11 rotatedabout(p6, 12.5);

pickup pencircle scaled 14pt;
for i=4 upto 8: draw p[i]; endfor;
draw base;

pickup pencircle scaled .9mm;
draw p4--p5--p6--p7--p8--p4;

for i=1 upto 5: draw p[i+3]--base; endfor;

draw p12--p7;

draw p16--p6--p17;
draw p9--p4--p10;
draw p13--p8--p14;
draw p15--p5;

drawTriangle(p5, 1.4u, 65);
drawTriangle(p6, 1.4u, 35);
drawTriangle(p7, 1.4u, 115);
drawTriangle(p8, 1.4u, 310);
drawTriangle(p4, 1.4u, -130);

label.bot(btex $v$ etex scaled LabelScale, base + (0, -0.3u));
label.lft(btex $v_1$ etex scaled LabelScale, p8);
label.llft(btex $v_2$ etex scaled LabelScale, p7);
label.lft(btex $v_3$ etex scaled LabelScale, p6+ (-0.2u, 0.1u));
label.lrt(btex $v_4$ etex scaled LabelScale, p5 + (0.1u, -0.1u));
label.rt(btex $v_5$ etex scaled LabelScale, p4 + (0.1u, 0));

drawArrow((8.3u, 0u), 8u);

for i=1 upto 17: p[i]:= p[i] + (25u, 0); endfor;
pickup pencircle scaled 14pt;
for i=1 upto 8: draw p[i]; endfor;
draw base;

pickup pencircle scaled .9mm;
draw p4--p5--p6--p7--p8--p4;

draw p12--p7;
draw p1--p2--p3--p1;

draw p8--p1--p4--p2--p5;
draw p2--p6--p3;
draw p7--p3--p8;

draw p16--p6--p17;
draw p9--p4--p10;
draw p13--p8--p14;
draw p15--p5;

drawTriangle(p5, 1.4u, 65);
drawTriangle(p6, 1.4u, 35);
drawTriangle(p7, 1.4u, 115);
drawTriangle(p8, 1.4u, 310);
drawTriangle(p4, 1.4u, -130);

label.lft(btex $v_1$ etex scaled LabelScale, p8);
label.llft(btex $v_2$ etex scaled LabelScale, p7);
label.lft(btex $v_3$ etex scaled LabelScale, p6+ (-0.2u, 0.1u));
label.lrt(btex $v_4$ etex scaled LabelScale, p5 + (0.1u, -0.1u));
label.rt(btex $v_5$ etex scaled LabelScale, p4 + (0.1u, 0));

label.ulft(btex $v_6$ etex scaled LabelScale, p3 + (0,0.2u));
label.urt(btex $v_7$ etex scaled LabelScale, p2 + (0,0.2u));
label.bot(btex $v_8$ etex scaled LabelScale, p1 + (0, -0.3u));

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
beginfig(7);

pair base;
base:= (0,0);

pair baseSq;
baseSq:= (0, -4u);

pair dirc[];
dirc1 = (0, -1.8u);
dirc2 = (1.8u, 0);
dirc3 = (0, 1.8u);
dirc4 = (-1.8u, 0);

pair p[];
pair hlp;

pickup pencircle scaled .9mm;
for i=1 upto 4:
    p[i]:= baseSq rotatedabout(base, -90 + 90 * i);
    hlp:= p[i] + dirc[i];
    p[2* i + 3]:= hlp rotatedabout(p[i], -20);
    p[2* i + 4]:= hlp rotatedabout(p[i], 20);
    draw p[2 * i + 3]--p[i]--p[2 * i + 4];
    drawTriangle(p[i], 1.5u, -120 + 90 * i);

endfor;

p13:=p1+dirc1;
p14:=p3+dirc3;

draw p13--p1;
draw p14--p3;

draw p1--p2--p3--p4--p1;
draw p2--p4;

pickup pencircle scaled 14pt;
for i=1 upto 4: draw p[i]; endfor;

label.top(btex $v_1$ etex scaled LabelScale, p4 + (-0.1u, 0.3u));
label.bot(btex $v_2$ etex scaled LabelScale, p2 + (0.1u, -0.3u));

pickup pencircle scaled 0.9mm;
drawArrow((8u, 0), 8u);

base:= base + (25u, 0);
baseSq:= baseSq + (25u,0);

pickup pencircle scaled .9mm;
for i=1 upto 4:
    p[i]:= baseSq rotatedabout(base, -90 + 90 * i);
    hlp:= p[i] + dirc[i];
    p[2* i + 3]:= hlp rotatedabout(p[i], -20);
    p[2* i + 4]:= hlp rotatedabout(p[i], 20);
    draw p[2 * i + 3]--p[i]--p[2 * i + 4];
    drawTriangle(p[i], 1.5u, -120 + 90 * i);

endfor;

p13:=p1+dirc1;
p14:=p3+dirc3;

draw p13--p1;
draw p14--p3;
draw p1--p3;

draw p1--p2--p3--p4--p1;
draw p2--p4;

pickup pencircle scaled 14pt;
for i=1 upto 4: draw p[i]; endfor;
draw base;

label.top(btex $v_1$ etex scaled LabelScale, p4 + (-0.1u, 0.3u));
label.bot(btex $v_2$ etex scaled LabelScale, p2 + (0.1u, -0.3u));

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
beginfig(8);

pair base;
base:= (0,0);

pair basePent;
basePent:= (0, -5u);

pair baseExt;
baseExt:= (0, -8u);

pair p[];

pickup pencircle scaled .9mm;
for i=1 upto 5:
    p[i]:= basePent rotatedabout(base, -72 + 72 * i);
    hlp:= baseExt rotatedabout(base, -72 + 72 * i);
    p[2* i + 4]:= hlp rotatedabout(p[i], -20);
    p[2* i + 5]:= hlp rotatedabout(p[i], 20);
    draw p[2 * i + 4]--p[i]--p[2 * i + 5];
    drawTriangle(p[i], 2.3u, -105 + 72 * i);
endfor;

draw p1--p2--p3--p4--p5--p1;
draw p3--p1--p4;

pickup pencircle scaled 14pt;
for i=1 upto 5: draw p[i]; endfor;

label.llft(btex $v$ etex scaled LabelScale, p1 + (-0.2u, -0.1u));
label.urt(btex $v_1$ etex scaled LabelScale, p4 + (0,0.1u));
label.rt(btex $v_2$ etex scaled LabelScale, p3 + (0.3u,-0.2u));

pickup pencircle scaled 0.9mm;
drawArrow((10u, 0), 8u);

base:= base + (27u, 0);
basePent:= basePent + (27u, 0);
baseExt:= baseExt + (27u, 0);

pickup pencircle scaled .9mm;
for i=1 upto 5:
    p[i]:= basePent rotatedabout(base, -72 + 72 * i);
    hlp:= baseExt rotatedabout(base, -72 + 72 * i);
    p[2* i + 4]:= hlp rotatedabout(p[i], -20);
    p[2* i + 5]:= hlp rotatedabout(p[i], 20);
    draw p[2 * i + 4]--p[i]--p[2 * i + 5];
    drawTriangle(p[i], 2.3u, -105 + 72 * i);
    draw p[i]--base;
endfor;

draw p1--p2--p3--p4--p5--p1;

pickup pencircle scaled 14pt;
for i=1 upto 5: draw p[i]; endfor;
draw base;

label.llft(btex $v$ etex scaled LabelScale, p1 + (-0.2u, -0.1u));
label.urt(btex $v_1$ etex scaled LabelScale, p4 + (0,0.1u));
label.rt(btex $v_2$ etex scaled LabelScale, p3 + (0.3u,-0.2u));

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Detailed E_B
beginfig(9);

LabelScale:= 4;

pair p[];
p[1]:= (0, 0);
p[2]:= p[1] + (8u, -8u);
p[3]:= p[2] + (8u, 8u);
p[4]:= p[3] + (-8u, 8u);

p[5]:= p[1] + (2.5u, 0);
p[6]:= p[2] + (0, 2.5u);
p[7]:= p[3] + (-2.5u, 0);
p[8]:= p[4] + (0, -2.5u);

p9:= (p1+p3)/2;

path q;
q:=p9..p8;

pickup pencircle scaled 2mm;
draw q;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(q)) of q;

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p[i+4]--p[9]; endfor;

draw p[5]--p[6]--p[7]--p[8]--p[5];

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;


labeloffset:= 7bp;
label.lft(btex e etex scaled 7, (p8+p9)/2);
label.top(btex extend3$($e$->$next$->$next$)$ etex scaled LabelScale, (26u, 3u));
drawArrow((18u, 0), 18u);

for i:=1,2,3,4,5,6,7,8,9: p[i]:= p[i] + (38u, 0); endfor;
p10:= (p5+p6+p9)/3;

path q;
q:=p9..p8;

pickup pencircle scaled 2mm;
draw q;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(q)) of q;

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p[i+4]--p[9]; endfor;

draw p[5]--p[6]--p[7]--p[8]--p[5];
draw p5--p10--p6;
draw p9--p10;

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;

label.lft(btex e etex scaled 7, (p8+p9)/2);

drawArrow((2u, -17u), 12u);
label.top(btex extend4$($e$->$next$)$ etex scaled LabelScale, (7u, -14u));

for i:=1,2,3,4,5,6,7,8,9,10: p[i]:= p[i] + (-22u, -17u); endfor;
p11:=(p9+p6)/2;

path q;
q:=p9..p8;

pickup pencircle scaled 2mm;
draw q;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(q)) of q;

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p[i+4]--p[9]; endfor;

draw p[5]--p[6]--p[7]--p[8]--p[5];
draw p5--p10--p6;
draw p9--p10--p11--p7;

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;

label.lft(btex e etex scaled 7, (p8+p9)/2);

drawArrow((35u, -17u), 12u);
label.top(btex extend4$($e$)$ etex scaled LabelScale, (41u, -14u));

for i:=1,2,3,4,5,6,7,8,9: p[i]:= p[i] + (35u, 0); endfor;

pair middle;
middle = (p[1] + p[3])/2;

p[9]:= middle + (-1.2u, -1.2u);
p[10]:= middle + (1.2u, -1.2u);
p[11]:= middle + (1.2u,1.2u);
p[12]:= middle + (-1.2u,1.2u);

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11,12: draw p[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4: draw p[i]--p[i+4]--p[i+8]; endfor;

draw p[12]--p[5];

pickup pencircle scaled .9mm;
for i:=6,7,8: draw p[i]--p[i+3]; endfor;

draw p[9]--p[10]--p[11]--p[12]--p[9];
draw p[12]--p[10];

draw p[5]--p[6]--p[7]--p[8]--p[5];

for i:= 1,2,3,4: drawTriangle(p[i + 4], 2u, 45 + i*90); endfor;

q:=p12..p8;

pickup pencircle scaled 2mm;
draw q;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(q)) of q;

labeloffset:=15bp;
label.lft(btex e etex scaled 7, (p8+p9)/2);
endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Detailed E_F
beginfig(10)
LabelScale:= 2.4;
pair base;
base:= (0,0);

pair basePent;
basePent:= base + (0, -5u);

pair p[];

for i=1 upto 3: p[i]:= baseTrian rotatedabout(base, -120 + 120 * i); endfor;
for i=1 upto 5: p[i+3]:= basePent rotatedabout(base, -36 + 72 * i); endfor;
p9:= p4 + (0, -1.8u);
p10:= p9 rotatedabout(p4, 25);

p11:= p6 + (0, 2u);
p12:= p7 + (-2u, 0);
p13:= p8 + (0,-2u);
p14:= p13 rotatedabout(p8, -25);
p15:= p5 + (2u, 0);
p16:= p11 rotatedabout(p6, -12.5);
p17:= p11 rotatedabout(p6, 12.5);

pickup pencircle scaled 14pt;
for i=4 upto 8: draw p[i]; endfor;
draw base;

pickup pencircle scaled .9mm;
draw p4--p5--p6--p7--p8--p4;

for i=1 upto 5: draw p[i+3]--base; endfor;

draw p12--p7;

draw p16--p6--p17;
draw p9--p4--p10;
draw p13--p8--p14;
draw p15--p5;

drawTriangle(p5, 1.4u, 65);
drawTriangle(p6, 1.4u, 35);
drawTriangle(p7, 1.4u, 115);
drawTriangle(p8, 1.4u, 310);
drawTriangle(p4, 1.4u, -130);

path q;
q:=base..p6;

pickup pencircle scaled 2mm;
draw q;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(q)) of q;

labeloffset:=15bp;
label.lft(btex e etex scaled 7, (base + p6)/2);

pickup pencircle scaled .9mm;
drawArrow((10u, 0u), 8u);
label.top(btex extend3$($e$->$next$->$next$)$ etex scaled LabelScale, (14u, 1u));

for i=1 upto 17: p[i]:= p[i] + (28u, 0); endfor;
base:= base + (28u, 0);
pair new;
new:= (base + p4 + p8)/3;

pickup pencircle scaled 14pt;
for i=4 upto 8: draw p[i]; endfor;
draw base;
draw new;

pickup pencircle scaled .9mm;
for i=4 upto 8: draw p[i]--base; endfor;
draw p4--p5--p6--p7--p8--p4;
draw base--new--p4;
draw new--p8;

draw p12--p7;

draw p16--p6--p17;
draw p9--p4--p10;
draw p13--p8--p14;
draw p15--p5;

drawTriangle(p5, 1.4u, 65);
drawTriangle(p6, 1.4u, 35);
drawTriangle(p7, 1.4u, 115);
drawTriangle(p8, 1.4u, 310);
drawTriangle(p4, 1.4u, -130);

q:=base..p6;

pickup pencircle scaled 2mm;
draw q;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(q)) of q;

labeloffset:=15bp;
label.lft(btex e etex scaled 7, (base + p6)/2);

pickup pencircle scaled .9mm;
drawArrow((-4u, -14u), 8u);
label.top(btex extend5$($e$)$ etex scaled LabelScale, (0, -13u));

for i=1 upto 17: p[i]:= p[i] + (-14u, -13u); endfor;
pickup pencircle scaled 14pt;
for i=1 upto 8: draw p[i]; endfor;

pickup pencircle scaled .9mm;
draw p4--p5--p6--p7--p8--p4;

draw p12--p7;
draw p1--p2--p3--p1;

draw p8--p1--p4--p2--p5;
draw p2--p6--p3;
draw p7--p3--p8;

draw p16--p6--p17;
draw p9--p4--p10;
draw p13--p8--p14;
draw p15--p5;

drawTriangle(p5, 1.4u, 65);
drawTriangle(p6, 1.4u, 35);
drawTriangle(p7, 1.4u, 115);
drawTriangle(p8, 1.4u, 310);
drawTriangle(p4, 1.4u, -130);

q:=p3..p6;

pickup pencircle scaled 2mm;
draw q;
ahlength:= 16bp;
drawarrow subpath (0, 0.7 * length(q)) of q;

labeloffset:=7bp;
label.ulft(btex e etex scaled 7, p3 + 0.1*(p6 - p3));

endfig;

end;
end.

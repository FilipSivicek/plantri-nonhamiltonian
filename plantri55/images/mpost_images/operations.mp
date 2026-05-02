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

numeric LabelScale;
LabelScale:= 5;

%N_0
beginfig(1)
u:=10mm;
d = 2u;
s = 2.5u;

z1 = (0,0);
z2 = z1 + (10u, 0);
z3 = z1 + (0, 10u);
z4 = z1 + (10u, 10u);

z5 = z1 + (d,d);
z6 = z2 + (-d, d);
z7 = z3 + (d, -d);
z8 = z4 + (-d, -d);

z9 = z6 + (-s, 0);
z10 = z9 + (0, s);
z11 = z6 + (0, s);

z12 = z7 + (0, -s);
z13 = z12 + (s, 0);
z14 = z7 + (s, 0);

pickup pencircle scaled 9pt;
for i:=1,2,3,4,5,6,7,8,9,10,11,12,13,14: draw z[i]; endfor;

pickup pencircle scaled .3mm;
draw z1--z2--z4--z3--z1;
draw z5--z6--z8--z7--z5;
draw z1--z5;
draw z2--z6;
draw z3--z7;
draw z4--z8;
draw z9--z10--z11;
draw z12--z13--z14;
draw z13--z10;

endfig;

%A
beginfig(2)
u:=10mm;
d:= 2u;
s:= 2.5u;

z01 = (0,0);
z02 = z01 + (10u, 0);
z03 = z01 + (0, 10u);
z04 = z01 + (10u, 10u);

z5 = z01 + (d,d);
z6 = z02 + (-d, d);
z7 = z03 + (d, -d);
z8 = z04 + (-d, -d);

z9 = z5 + (s, 0);
z10 = z9 + (0, s);
z11 = z5 + (0, s);

z12 = z8 + (0, -s);
z13 = z12 + (-s, 0);
z14 = z13 + (0, s);

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11,12,13,14: draw z[i]; endfor;

pickup pencircle scaled .9mm;
draw z5--z6--z8--z7--z5;
draw z1--z5;
draw z2--z6;
draw z3--z7;
draw z4--z8;
draw z9--z10--z11;
draw z12--z13--z14;
draw z13--z10;

label.lft(btex $5+$ etex scaled LabelScale, (z1 + z3 + z5 + z7)/4);
label.bot(btex $5+$ etex scaled LabelScale, (z1+z2+z5+z6)/4);
label.rt(btex  $5+$ etex scaled LabelScale, (z2+z6+z8+z4)/4);
label.top(btex $5+$ etex scaled LabelScale, (z3+z4+z7+z8)/4);

drawArrow((12u, 5u), 10u);

z21 = (27u,0);
z22 = z21 + (10u, 0);
z23 = z21 + (0, 10u);
z24 = z21 + (10u, 10u);

z25 = z21 + (d,d);
z26 = z22 + (-d, d);
z27 = z23 + (d, -d);
z28 = z24 + (-d, -d);

z29 = z25 + (s, 0);
z30 = z29 + (0, s);
z31 = z25 + (0, s);

z32 = z28 + (0, -s);
z33 = z32 + (-s, 0);
z34 = z33 + (0, s);

z35 = z25 + (-s, 0);
z36 = z27 + (-s, 0);
z37 = z21 + (-s, 0);
z38 = z23 + (-s, 0);

pickup pencircle scaled 14pt;
for i:=25,26,27,28,29,30,31,32,33,34,35,36: draw z[i]; endfor;

pickup pencircle scaled .9mm;
draw z25--z26--z28--z27--z25;
draw z22--z26;
draw z24--z28;
draw z29--z30--z31;
draw z32--z33--z34;
draw z33--z30;
draw z25--z35--z36--z27;
draw z38--z36;
draw z37--z35;


label.lft(btex $4+$ etex scaled LabelScale, (z38+z37+z35+z36)/4);
label.bot(btex $6+$ etex scaled LabelScale, (z37+z22+z25+z26)/4);
label.rt(btex  $5+$ etex scaled LabelScale, (z22+z26+z28+z24)/4);
label.top(btex $6+$ etex scaled LabelScale, (z38+z24+z36+z28)/4);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%B
beginfig(3)
u:=10mm;
d:= 2u;
s:= 2.5u;

pair P[];
P[1]:= (0,0);
P[2]:= P[1] + (10u, 0);
P[3]:= P[1] + (0, 10u);
P[4]:= P[1] + (10u, 10u);

P[5]:= P[1] + (d,d);
P[6]:= P[2] + (-d, d);
P[7]:= P[3] + (d, -d);
P[8]:= P[4] + (-d, -d);

P[9]:= P[5] + (s, 0);
P[10]:= P[9] + (0, s);
P[11]:= P[5] + (0, s);

P[12]:= P[8] + (0, -s);
P[13]:= P[12] + (-s, 0);
P[14]:= P[13] + (0, s);

pickup pencircle scaled 14pt;
for i:=5,6,7,8: draw P[i]; endfor;

pickup pencircle scaled .9mm;
draw P[5]--P[6]--P[8]--P[7]--P[5];
draw P[1]--P[5];
draw P[2]--P[6];
draw P[3]--P[7];
draw P[4]--P[8];
%draw P[9]--P[10]--P[11];
%draw P[12]--P[13]--P[14];
%draw P[13]--P[10];

label.lft(btex $5+$ etex scaled LabelScale, (P[1] + P[3] + P[5] + P[7])/4);
label.bot(btex $5+$ etex scaled LabelScale, (P[1]+P[2]+P[5]+P[6])/4);
label.rt(btex  $5+$ etex scaled LabelScale, (P[2]+P[6]+P[8]+P[4])/4);
label.top(btex $5+$ etex scaled LabelScale, (P[3]+P[4]+P[7]+P[8])/4);

drawArrow((12u, 5u), 10u);

for i:=1,2,3,4,5,6,7,8,9,10,11,12,13,14: P[i]:= P[i] + (25u, 0); endfor;

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11,12,13,14: draw P[i]; endfor;

pickup pencircle scaled .9mm;
draw P[5]--P[6]--P[8]--P[7]--P[5];
draw P[1]--P[5];
draw P[2]--P[6];
draw P[3]--P[7];
draw P[4]--P[8];
draw P[9]--P[10]--P[11];
draw P[12]--P[13]--P[14];
draw P[13]--P[10];

label.lft(btex $6+$ etex scaled LabelScale, (P[1] + P[3] + P[5] + P[7])/4);
label.bot(btex $6+$ etex scaled LabelScale, (P[1]+P[2]+P[5]+P[6])/4);
label.rt(btex  $6+$ etex scaled LabelScale, (P[2]+P[6]+P[8]+P[4])/4);
label.top(btex $6+$ etex scaled LabelScale, (P[3]+P[4]+P[7]+P[8])/4);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%C
beginfig(4)
u:=10mm;
d:= 2u;
s:= 2.5u;

pair P[];
P[1]:= (0,0);
P[2]:= P[1] + (10u, 0);
P[3]:= P[1] + (0, 10u);
P[4]:= P[1] + (10u, 10u);

P[5]:= P[1] + (d,d);
P[6]:= P[2] + (-d, d);
P[7]:= P[3] + (d, -d);
P[8]:= P[4] + (-d, -d);

P[9]:= P[5] + (s, 0);
P[10]:= P[9] + (0, s);
P[11]:= P[5] + (0, s);

P[12]:= P[8] + (0, -s);
P[13]:= P[12] + (-s, 0);
P[14]:= P[13] + (0, s);

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,10,11,12,13,14: draw P[i]; endfor;

pickup pencircle scaled .9mm;
draw P[5]--P[6]--P[8]--P[7]--P[5];
draw P[1]--P[5];
draw P[2]--P[6];
draw P[3]--P[7];
draw P[4]--P[8];
draw P[9]--P[10]--P[11];
draw P[12]--P[13]--P[14];
draw P[13]--P[10];

label.lft(btex $5+$ etex scaled LabelScale, (P[1] + P[3] + P[5] + P[7])/4);
label.bot(btex $5+$ etex scaled LabelScale, (P[1]+P[2]+P[5]+P[6])/4);
label.rt(btex  $5+$ etex scaled LabelScale, (P[2]+P[6]+P[8]+P[4])/4);
label.top(btex $5+$ etex scaled LabelScale, (P[3]+P[4]+P[7]+P[8])/4);

drawArrow((12u, 5u), 10u);

for i:=1,2,3,4,5,6,7,8,9,10,11,12,13,14: P[i]:= P[i] + (25u, 0); endfor;

P[9]:= (P[5] + P[6])/2;
P[11]:= (P[5] + P[7])/2;
P[12]:= (P[6] + P[8])/2;
P[14]:= (P[7] + P[8])/2;

pair middle;
middle := (P[5] + P[6] + P[7] + P[8])/4;

pair SM[];
SM[1] = middle + (-u, 0);
SM[2] = middle + (0, u);
SM[3] = middle + (u, 0);
SM[4] = middle + (0, -u);

pickup pencircle scaled 14pt;
for i:=5,6,7,8,9,11,12,14: draw P[i]; endfor;

for i:=1,2,3,4: draw SM[i]; endfor;

pickup pencircle scaled .9mm;
draw P[5]--P[6]--P[8]--P[7]--P[5];
draw P[1]--P[5];
draw P[2]--P[6];
draw P[3]--P[7];
draw P[4]--P[8];
draw SM[1]--SM[2]--SM[3]--SM[4]--SM[1];
draw SM[1]--P[11];
draw SM[2]--P[14];
draw SM[3]--P[12];
draw SM[4]--P[9];

label.lft(btex $5+$ etex scaled LabelScale, (P[1] + P[3] + P[5] + P[7])/4);
label.bot(btex $5+$ etex scaled LabelScale, (P[1]+P[2]+P[5]+P[6])/4);
label.rt(btex  $5+$ etex scaled LabelScale, (P[2]+P[6]+P[8]+P[4])/4);
label.top(btex $5+$ etex scaled LabelScale, (P[3]+P[4]+P[7]+P[8])/4);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%D
beginfig(5)

u:=10mm;
d:= 2u;
s:= 2.5u;

pair P[];
P[1]:= (0,0);
P[2]:= P[1] + (10u, 0);
P[3]:=P[2] + (0, 6.5u);
P[4]:= P[1] + (5u, 8.5u);
P[5]:= P[1] + (0, 6.5u);

P[6]:=P[1] + (2u,2u);
P[7]:=P[2] + (-2u, 2u);
P[8]:=P[3] + (-2u,-2u);
P[9]:=P[4] + (0, -2u);
P[10]:=P[5] + (2u, -2u);

P[11]:=(P[6]+P[7])/2;
P[12]:=(P[8]+P[9])/2;
P[13]:=(P[9]+P[10])/2;
P[14]:=(P[6]+P[7]+P[8]+P[9]+P[10])/5;

pickup pencircle scaled 14pt;
for i:=6,7,8,9,10,11,12,13,14: draw P[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4,5: draw P[i]--P[i+5]; endfor;

draw P[6]--P[7]--P[8]--P[9]--P[10]--P[6];
draw P[11]--P[14]--P[13];
draw P[12]--P[14];

label(btex $5+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $4+$ etex scaled LabelScale, (P[2] + P[3])/2);
label(btex $5+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $5+$ etex scaled LabelScale, (P[4] + P[5])/2);
label(btex $4+$ etex scaled LabelScale, (P[5] + P[1])/2);

drawArrow((12u, 5u), 10u);

for i:=1,2,3,4,5,6,7,8,9,10,11,12,13,14: P[i]:= P[i] + (25u, 0); endfor;

P[12]:= P[8] - 0.4(P[8] - P[9]);
P[13]:= P[10] + 0.4(P[9] - P[10]);

P[16]:= P[6] + (P[7] - P[6])/3;
P[17]:= P[6] + 2(P[7] - P[6])/3;
P[18]:= P[17] + (0, 2u);
P[19]:= P[18] - (P[7] - P[6])/3;

pickup pencircle scaled 14pt;
for i:=6,7,8,9,10,12,13,16,17,18,19: draw P[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4,5: draw P[i]--P[i+5]; endfor;

draw P[6]--P[7]--P[8]--P[9]--P[10]--P[6];

draw P[16]--P[17]--P[18]--P[19]--P[16];
draw P[18]--P[12];
draw P[19]--P[13];

label(btex $6+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $4+$ etex scaled LabelScale, (P[2] + P[3])/2);
label(btex $5+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $5+$ etex scaled LabelScale, (P[4] + P[5])/2);
label(btex $4+$ etex scaled LabelScale, (P[5] + P[1])/2);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%E
beginfig(6)
pair P[];
P[1]:= (0,0);
P[2]:= P[1] + (4u, -2u);
P[3]:= P[2] + (4u, 2u);
P[4]:= P[3] + (0, 8u);
P[5]:= P[1] + (0, 8u);

P[6]:= P[1] + (2u, 2u);
P[7]:= P[2] + (0, 2u);
P[8]:= P[3] + (-2u, 2u);
P[9]:= P[4] + (-2u,-2u);
P[10]:= P[5] + (2u, -2u);

P[11]:= (P[8] + P[9]) / 2;
P[12]:= (P[10] + P[6]) / 2;
P[13]:= (P[6] + P[7]) / 2;
P[14]:= (P[11] + P[12]) / 2;

pickup pencircle scaled 14pt;
for i:=6,7,8,9,10,11,12,13,14: draw P[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4,5: draw P[i]--P[i+5]; endfor;

draw P[6]--P[7]--P[8]--P[9]--P[10]--P[6];
draw P[11]--P[12];
draw P[13]--P[14];

label(btex $6+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $5+$ etex scaled LabelScale, (P[2] + P[3])/2);
label(btex $4+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $4+$ etex scaled LabelScale, (P[4] + P[5])/2);
label(btex $5+$ etex scaled LabelScale, (P[5] + P[1])/2);

drawArrow((12u, 4u), 10u);

for i:=1,2,3,4,5,6,7,8,9,10,11,12,13,14: P[i]:= P[i] + (25u, 0); endfor;

P[15]:= (P[6] + P[8])/2;
P[16]:=(P[7] + P[8])/2;

pickup pencircle scaled 14pt;
for i:=6,7,8,9,10,11,12,13,14,15,16: draw P[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4,5: draw P[i]--P[i+5]; endfor;

draw P[6]--P[7]--P[8]--P[9]--P[10]--P[6];
draw P[11]--P[12];
draw P[13]--P[15]--P[14];
draw P[16]--P[15];

label(btex $6+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $6+$ etex scaled LabelScale, (P[2] + P[3])/2);
label(btex $4+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $4+$ etex scaled LabelScale, (P[4] + P[5])/2);
label(btex $5+$ etex scaled LabelScale, (P[5] + P[1])/2);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%F
beginfig(7)
pair P[];
P[1]:= (0,0);
P[2]:= P[1] + (4u, -2u);
P[3]:= P[2] + (4u, 2u);
P[4]:= P[3] + (0, 6u);
P[5]:= P[1] + (0, 6u);

P[6]:= P[1] + (2u, 2u);
P[7]:= P[2] + (0, 2u);
P[8]:= P[3] + (-2u, 2u);
P[9]:= P[4] + (-2u,-2u);
P[10]:= P[5] + (2u, -2u);

pickup pencircle scaled 14pt;
for i:=6,7,8,9,10: draw P[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4,5: draw P[i]--P[i+5]; endfor;

draw P[6]--P[7]--P[8]--P[9]--P[10]--P[6];

label(btex $5+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $5+$ etex scaled LabelScale, (P[2] + P[3])/2);
label(btex $4+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $5+$ etex scaled LabelScale, (P[4] + P[5])/2);
label(btex $4+$ etex scaled LabelScale, (P[5] + P[1])/2);

drawArrow((12u, 3u), 10u);

for i:=1,2,3,4,5,6,7,8,9,10: P[i]:= P[i] + (25u, 0); endfor;

P[11]:= (P[6] + P[7]) / 2;
P[12]:= (P[7] + P[8]) / 2;
P[13]:= (P[9] + P[10]) / 2;

P[14]:= (P[6] + P[7] + P[8] + P[9] + P[10]) / 5;

pickup pencircle scaled 14pt;
for i:=6,7,8,9,10,11,12,13,14: draw P[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4,5: draw P[i]--P[i+5]; endfor;

draw P[6]--P[7]--P[8]--P[9]--P[10]--P[6];

draw P[11]--P[14]--P[13];
draw P[12]--P[14];

label(btex $6+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $6+$ etex scaled LabelScale, (P[2] + P[3])/2);
label(btex $4+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $6+$ etex scaled LabelScale, (P[4] + P[5])/2);
label(btex $4+$ etex scaled LabelScale, (P[5] + P[1])/2);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%G
beginfig(8)

pair P[];
P[1]:= (0,0);
P[2]:= P[1] + (4u, 0);
P[3]:= P[2] + (0, 7u);
P[4]:= P[1] + (0, 7u);

P[5]:= P[1] + (2u, 2u);
P[6]:= P[5] + (0, 3u);

pickup pencircle scaled 14pt;
for i:=5,6: draw P[i]; endfor;

pickup pencircle scaled .9mm;
draw P[1]--P[5]--P[2];
draw P[3]--P[6]--P[4];
draw P[5]--P[6];

label(btex $5+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $5+$ etex scaled LabelScale, (P[2] + P[3])/2);
label(btex $5+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $5+$ etex scaled LabelScale, (P[4] + P[1])/2);

drawArrow((6.5u, 3.5u), 6u);

P[1]:= (15u,-0.5u);
P[2]:= P[1] + (8u, 0);
P[3]:= P[1] + (0, 8u);
P[4]:= P[1] + (8u, 8u);

P[5]:= P[1] + (d,d);
P[6]:= P[2] + (-d, d);
P[7]:= P[3] + (d, -d);
P[8]:= P[4] + (-d, -d);

pickup pencircle scaled 14pt;
for i:=5,6,7,8: draw P[i]; endfor;

pickup pencircle scaled .9mm;
draw P[5]--P[6]--P[8]--P[7]--P[5];
draw P[1]--P[5];
draw P[2]--P[6];
draw P[3]--P[7];
draw P[4]--P[8];

label(btex $6+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $5+$ etex scaled LabelScale, (P[1] + P[3])/2);
label(btex $6+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $5+$ etex scaled LabelScale, (P[4] + P[2])/2);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%H
beginfig(9)

pair P[];
P[1]:= (0,0);
P[2]:= P[1] + (4u, -2u);
P[3]:= P[2] + (4u, 2u);
P[4]:= P[3] + (0, 6u);
P[5]:= P[1] + (0, 6u);

P[6]:= P[1] + (2u, 2u);
P[7]:= P[2] + (0, 2u);
P[8]:= P[3] + (-2u, 2u);
P[9]:= P[4] + (-2u,-2u);
P[10]:= P[5] + (2u, -2u);

pickup pencircle scaled 14pt;
for i:=6,7,8: draw P[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3: draw P[i]--P[i+5]; endfor;

draw P[10]--P[6]--P[7]--P[8]--P[9];

label(btex $5+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $5+$ etex scaled LabelScale, (P[2] + P[3])/2);
label(btex $4+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $6+$ etex scaled LabelScale, (P[1] + P[3] + P[4] + P[5])/4);
label(btex $4+$ etex scaled LabelScale, (P[5] + P[1])/2);

drawArrow((10u, 1.5u), 7u);

for i:=1,2,3,4,5,6,7,8,9,10: P[i]:= P[i] + (20u, -1u); endfor;

pickup pencircle scaled 14pt;
for i:=6,7,8,9,10: draw P[i]; endfor;

pickup pencircle scaled .9mm;
for i:=1,2,3,4,5: draw P[i]--P[i+5]; endfor;

draw P[6]--P[7]--P[8]--P[9]--P[10]--P[6];

label(btex $5+$ etex scaled LabelScale, (P[1] + P[2])/2);
label(btex $5+$ etex scaled LabelScale, (P[2] + P[3])/2);
label(btex $5+$ etex scaled LabelScale, (P[3] + P[4])/2);
label(btex $5+$ etex scaled LabelScale, (P[4] + P[5])/2);
label(btex $5+$ etex scaled LabelScale, (P[5] + P[1])/2);

endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% N_0 labeled
beginfig(10)
u:=10mm;
d:= 2u;
s:= 2.5u;

z1 = (0,0);
z2 = z1 + (10u, 0);
z3 = z1 + (0, 10u);
z4 = z1 + (10u, 10u);

z5 = z1 + (d,d);
z6 = z2 + (-d, d);
z7 = z3 + (d, -d);
z8 = z4 + (-d, -d);

z9 = z6 + (-s, 0);
z10 = z9 + (0, s);
z11 = z6 + (0, s);

z12 = z7 + (0, -s);
z13 = z12 + (s, 0);
z14 = z7 + (s, 0);

pickup pencircle scaled 9pt;
for i:=1,2,3,4,5,6,7,8,9,10,11,12,13,14: draw z[i]; endfor;

pickup pencircle scaled .3mm;
draw z1--z2--z4--z3--z1;
draw z5--z6--z8--z7--z5;
draw z1--z5;
draw z2--z6;
draw z3--z7;
draw z4--z8;
draw z9--z10--z11;
draw z12--z13--z14;
draw z13--z10;

LabelScale:= 3;
labeloffset:= 5bp;
label.llft(btex $m$ etex scaled LabelScale, z1);
label.lrt(btex $l$ etex scaled LabelScale, z2);
label.ulft(btex $n$ etex scaled LabelScale, z3);
label.urt(btex $k$ etex scaled LabelScale, z4);
label.urt(btex $i$ etex scaled LabelScale, z5);
label.urt(btex $h$ etex scaled LabelScale, z6);
label.urt(btex $j$ etex scaled LabelScale, z7);
label.lrt(btex $g$ etex scaled LabelScale, z8);
label.ulft(btex $d$ etex scaled LabelScale, z9);
label.urt(btex $a$ etex scaled LabelScale, z10);
label.rt(btex $c$ etex scaled LabelScale, z11);
label.lft(btex $e$ etex scaled LabelScale, z12);
label.urt(btex $b$ etex scaled LabelScale, z13);
label.top(btex $f$ etex scaled LabelScale, z14);
endfig;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% O_3

beginfig(11)

u:=10mm;
d:= 2u;
s:= 2.5u;

pair orig;
orig:= (0,0);

pair base;
base:= orig + (0, -3u);

pair p[];
pickup pencircle scaled .9mm;
for i=1 upto 3: 
    p[i]:= base rotatedabout(orig, -120 + 120 * i);
    draw p[i]--orig;
endfor;

pickup pencircle scaled 1.5mm;
draw p2--orig--p3;

pickup pencircle scaled 14pt;
draw orig;

label

endfig;

end;
end.

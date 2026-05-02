input mpcolornames

prologues:=3;

u:=10mm;
beginfig(1)
z1=(2u,2u);
z2-z1=(u,0);
z3=z2 rotatedabout(z1,60);
z0=(z1+z2+z3)/3;
z10=2[z0,z1];
z20=2[z0,z2];
z30=2[z0,z3];
pickup pencircle scaled 4pt;
draw z1;
draw z2;
draw z3;
pickup pencircle scaled .7mm;
draw z10--z1--z3--z2--z20;
pickup pencircle scaled .3mm;
draw z3--z30;
draw z1--z2;
endfig;

beginfig(59)
u:=7mm;

z1 = (0,0);
z2 = z1 + (4u,0);
z3 = z1 + (0,4u);
z4 = z2 + (0,4u);

z11 = z1 - (u,0);
z21 = z2 + (u,0);
z31 = z3 + (0,u);

pickup pencircle scaled 4pt;
for i:=1,2,3,4: draw z[i]; endfor;

pickup pencircle scaled .3mm;
draw z1--z2--z4--z3--cycle;
draw z1--z11;
draw z2--z21;
draw z3--z31;

label.rt(btex $0$ etex, 1/2[z3,z31]);
label.lft(btex $\{1\}$ etex, z3);
label.lft(btex $2$ etex, 1/2[z1,z3]);
label.bot(btex $3$ etex, 1/2[z3,z4]);
label.lft(btex $1$ etex, 1/2[z2,z4]);
label.urt(btex $\{0,2\}$ etex, z4);
label.bot(btex $\{3\}$ etex, z2);
label.bot(btex $0$ etex, 1/2[z1,z2]);
label.llft(btex $2$ etex, z21);
label.bot(btex ? etex, z1);
label.lrt(btex ? etex, z11);

label.lrt(btex $a$ etex scaled 1.5, z3);
label.llft(btex $b$ etex scaled 1.5, z4);
label.urt(btex $c$ etex scaled 1.5, z1);
label.ulft(btex $d$ etex scaled 1.5, z2);

endfig;

end;
end.

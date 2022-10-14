# coff-compiler
a simple compiler written in c

for now, the compiler translates given infix to expected postfix.

## compile
compile the compiler by running <code>cc main.c</code> on your UNIX os

## running
run <code>./a.out</code> and input your desired program (or in this case infix), for example <code>(1+2)+3;</code>

## output
the compiler will output the expected postfix token by token separated by new lines

## goal syntax
<b>MAINDEF</b>(c:<b>NUM</b>, a:<b>SEQ</b>) <i># this is the program entry point</i> <br/>
&nbsp;&nbsp;&nbsp;&nbsp; <b>RET</b> name(1);<br/>
<b>MAINEND</b>

<b>FUNCDEF</b> name(a:<b>NUM</b>)<br/>
&nbsp;&nbsp;&nbsp;&nbsp; x:<b>NUM</b> = a + a;<br/>
&nbsp;&nbsp;&nbsp;&nbsp; <b>RET</b> x;<br/>
<b>FUNCEND</b>

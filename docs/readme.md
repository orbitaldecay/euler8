<!DOCTYPE html>
<html lang="en">
<body>
<div id="title">
<h1>Euler8 Documentation</h1>
</div><hr>

<div id="preface">
<h2>Preface</h2>
<p>This is the documentation for Euler8 0.1. This software was designed and developed by Bob Forder (<a href="mailto:bob@forder.cc">bob@forder.cc</a>) for the <a href="https://itch.io/jam/make-a-console-jam">Make a Console Jam</a> during September of 2022. It is free software under the zlib license. All documentation and source code was written in Notepad. The virtual machine was compiled using Emscripten and the assembler was compiled using MinGW.</p>
</div><hr>

<div id="toc">
<h2>Table of contents</h2>
<ol>
<li><a href="#what">What is this?</a></li>
<li><a href="#why">Why did you do this?</a></li>
<li><a href="#how">How does it work?</a></li>
<li><a href="#instructions">Instruction listing</a></li>
</ol>
</div><hr>

<div id="what">
<h2>What is this?</h2>
<p>Perhaps most directly, Euler8 is a fantasy console. Think of a fantasy console as an emulator for a computer that was never built. More specifically, Euler8 is a stack based fantasy console which uses an extremely compact bytecode and features complex numbers as the native internal value representation. Euler8 doesn't support branching, and as such is not properly Turing complete. It is, however, a fully fledged finite state machine. It is capable of expressing more than simple combinational logic. If you don't know what this means, don't worry. It actually turns out not to matter much. Technically speaking, you're reading this on a finite state machine.</p>
<p>There are two seperate, but interdependent programs involved in using Euler8. The Euler8 assembler is a standalone console program that is used to convert Euler8 assembly code into Euler8 cartridges. The Euler8 virtual machine loads cartridges and executes them. This version of Euler8 only supports graphics. Input, sound, and other features may or may not be added at a later time.</p>
</div><hr>

<div id="why">
<h2>Why did you do this?</h2>
<p>My goal in designing Euler8 was twofold. First, I wanted to design a fantasy console that facillitated the creation of size optimized graphical programs. Second, I wanted to explore new classes and styles of size optimized programs. Traditionally, extremely small graphical programs have a small set of arithmetic and logical operations to perform on the available data. XOR patterns, feedback effects, and tunnel animations have been done many times by many people. I wanted to create a machine that encouraged the exploration of new ideas hitherto unseen in programs under 256 bytes in size.</p>
<p>I chose complex numbers as the internal representation because, mathematically speaking, the complex plane seemed to me to be the most natural choice for representing a two dimension viewport and is typically very space consuming on traditional architectures. Additionally, many beautiful visualizations can be expressed succinctly and efficiently in terms of operations on complex numbers. I chose to make Euler8 a stack machine because stack based operations are well known for having remarkably compact code density. This shoehorns in nicely with the already compact representation of many visuals in terms of complex numbers.</p>
<p>The final design decision which may seem peculiar is why I omitted branching and looping constructs from the language. There is an implicit pixel loop around each Euler8 program. Introducing Turing completeness to the language would create the possibility that some programs may never exit. Naively, this would cause the implicit loop to hang. As most small graphical effects don't require looping aside from the pixel loop, I decided to simply omit jumps and branches all together. This also allows the language to be more compact.</p>
</div><hr>

<div id="how">
<h2>How does it work?</h2>
<p>The Euler8 virtual machine is written in C++ and compiled for Windows. It is a viewport that takes a single command line parameter which specifies the cartridge to load. The cartridge is then executed in a loop. The Euler8 assembler is a console program that takes two arguments. The first argument is the filename of the source code. The second argument is the cartridge to be written to. On the Windows command line, <b>e8asm program.asm cartridge.bin</b> where <b>program.asm</b> is your source code and <b>cartridge.bin</b> is the name of the cartridge file that will be output.</p>
<p>The Euler8 assembly language can be learned in a short amount of time. Euler8 assembly code is written in reverse Polish notation (sorry, maybe one day I'll write an infix converter). That means, rather than writting <b>add 3 2</b> or <b>3 + 2</b> to represent the sum of three and two, you'd write <b>3 2 add</b>. The operation follows the operands. The language supports five constants, integer values, and 19 operations for a total of 26 operation codes.<p>
<p>A Euler8 program is a function which is called once per pixel per frame. The function is given access to three complex parameters and returns up to three complex values (but may return two, one, or none in which case the absent values are assumed to be zero). The function is given access to the parameters <i>z</i>, <i>t</i>, and <i>s</i>.<p>
<p>The <i>z</i> parameter is a complex number representing the coordinates of the current pixel. The real part encodes the X coordinate and the imaginary part encodes the Y coordinate. X and Y range between -1 and 1. The <i>t</i> parameter (time) is a purely real value that is the number of seconds the program has been running. Finally, the <i>s</i> parameter (state) is a value that was returned by the last iteration of the program on this pixel. This allows us to store some state for various purposes. The values <i>z</i>, <i>t</i>, and <i>s</i> are not passed on the stack, but they can be pushed to the stack by using the respective instructions. The argument stack is always empty when each iteration of the program begins.</p>
<p>The return value of an Euler8 program, however, is left on the stack. The top of the stack, when the function exits, encodes the red and green intensity to be written to the current pixel in its real and imaginary parts, respectively. The second number on the stack encodes the blue intensity to be written to the current pixel in it's real part (the imaginary component of the second number on the stack is ignored). RGB values are clamped to the range [0, 1]. Finally, the third number on the stack can encode anything and can be used by the next iteration of the function on this pixel (it is accessed via the <i>s</i> parameter mentioned previously).</p>
</div><hr>

<div id="instructions">
<h2>Instruction listing</h2>
<p>What follows is a complete listing of instructions for version 0.1. The argument stack contains complex numbers and each operation manipulates the argument stack. As mentioned previously, the program is executed once per pixel, per frame. The hexidecimal bytecode encodings have the most significant nibble first. The link text below contains descriptions of each instruction with some useful information. Note that many commands are only four bits in size. Eight bit commands need not be byte aligned.</p>
<table>
<tr><td><b>Instruction</b></td><td><b>Assembly code</b></td><td><b>Bytecode</b></td><td><b>Size (bits)</b></tr>
<tr><td><a href="#nop">No operation</a></td><td>nop</td><td>$0</td><td>4</td></tr>
<tr><td><a href="#z">Z parameter</a></td><td>z</td><td>$1</td><td>4</td></tr>
<tr><td><a href="#t">T parameter</a></td><td>t</td><td>$2</td><td>4</td></tr>
<tr><td><a href="#s">S parameter</a></td><td>s</td><td>$3</td><td>4</td></tr>
<tr><td><a href="#pi">Pi</a></td><td>pi</td><td>$4</td><td>4</td></tr>
<tr><td><a href="#i">Imaginary unit</a></td><td>i</td><td>$5</td><td>4</td></tr>
<tr><td><a href="#imm">Immediate</td><td>[-8,7]</td><td>$X6</td><td>8</td></tr>
<tr><td><a href="#con">Complex conjugate</a></td><td>con</td><td>$7</td><td>4</td></tr>
<tr><td><a href="#arg">Complex argument</a></td><td>arg</td><td>$8</td><td>4</td></tr>
<tr><td><a href="#abs">Absolute value</a></td><td>abs</td><td>$9</td><td>4</td></tr>
<tr><td><a href="#add">Addition</a></td><td>add</td><td>$A</td><td>4</td></tr>
<tr><td><a href="#sub">Subtraction</a></td><td>sub</td><td>$B</td><td>4</td></tr>
<tr><td><a href="#mul">Multiplication</a></td><td>mul</td><td>$C</td><td>4</td></tr>
<tr><td><a href="#div">Division</a></td><td>div</td><td>$D</td><td>4</td></tr>
<tr><td><a href="#dup">Duplicate</a></td><td>dup</td><td>$E</td><td>4</td></tr>
<tr><td><a href="#im">Imaginary component</a></td><td>im</td><td>$0F</td><td>8</td></tr>
<tr><td><a href="#re">Real component</a></td><td>re</td><td>$1F</td><td>8</td></tr>
<tr><td><a href="#sin">Sine</a></td><td>sin</td><td>$2F</td><td>8</td></tr>
<tr><td><a href="#cos">Cosine</a></td><td>cos</td><td>$3F</td><td>8</td></tr>
<tr><td><a href="#asin">Arcsine</a></td><td>asin</td><td>$4F</td><td>8</td></tr>
<tr><td><a href="#acos">Arccosine</a></td><td>acos</td><td>$5F</td><td>8</td></tr>
<tr><td><a href="#exp">Exponentiation</a></td><td>exp</td><td>$6F</td><td>8</td></tr>
<tr><td><a href="#ln">Natural logarithm</a></td><td>ln</td><td>$7F</td><td>8</td></tr>
<tr><td><a href="#pow">Power</a></td><td>pow</td><td>$8F</td><td>8</td></tr>
<tr><td><a href="#sqrt">Square root</a></td><td>sqrt</td><td>$9F</td><td>8</td></tr>
<tr><td><a href="#cis">Cosine plus <i>i</i> times sine</a></td><td>cis</td><td>$AF</td><td>8</td></tr>
</table>
</div><hr>

<div>
<h3 id="nop">No operation</h3>
<p>Does nothing.</p>
</div><hr>

<div>
<h3 id="z">Z Parameter</h3>
<p>Push the <i>z</i> parameter onto the stack. The X and Y coordinates of the current pixel are stored in the real and imaginary parts, respectively. X and Y coordinates range from -1 to 1.</p>
</div><hr>

<div>
<h3 id="t">T Parameter</h3>
<p>Push the <i>t</i> parameter onto the stack. The <i>t</i> parameter represents the amount of time in seconds since the program started.</p>
</div><hr>

<div>
<h3 id="s">S Parameter</h3>
<p>Push the <i>s</i> parameter onto the stack. The <i>s</i> parameter is the third value left on the stack the last time the program executed on this pixel.</p>
</div><hr>

<div>
<h3 id="pi">Pi</h3>
<p>Push the mathematical constant Pi onto the stack (3.1415...).</p>
</div><hr>

<div>
<h3 id="i">Imaginary unit</h3>
<p>Push the imaginary unit onto the stack.</p>
</div><hr>

<div>
<h3 id="imm">Immediate</h3>
<p>Push the four bit immediate xxxx following this instruction onto the stack as a signed integer. It is encoded as a purely real number.</p>
</div><hr>

<div>
<h3 id="con">Complex conjugate</h3>
<p>Pop A. Push the complex conjugate of A onto the stack.</p>
</div><hr>

<div>
<h3 id="arg">Complex argument</h3>
<p>Pop A. Push the complex argument of A onto the stack.</p>
</div><hr>

<div>
<h3 id="abs">Absolute value</h3>
<p>Pop A. Push the absolute value of A onto the stack.</p>
</div><hr>

<div>
<h3 id="add">Addition</h3>
<p>Pop B. Pop A. Push A + B onto the stack.</p>
</div><hr>

<div>
<h3 id="sub">Subtraction</h3>
<p>Pop B. Pop A. Push A - B onto the stack.</p>
</div><hr>

<div>
<h3 id="mul">Multiplication</h3>
<p>Pop B. Pop A. Push A * B onto the stack.</p>
</div><hr>

<div>
<h3 id="div">Division</h3>
<p>Pop B. Pop A. Push A / B onto the stack.</p>
</div><hr>

<div>
<h3 id="dup">Duplicate</h3>
<p>Pop A. Push A. Push A.</p>
</div><hr>

<div>
<h3 id="im">Imaginary component</h3>
<p>Pop A. Push the imaginary component of A onto the stack.</p>
</div><hr>

<div>
<h3 id="re">Real component</h3>
<p>Pop A. Push the real component of A onto the stack.</p>
</div><hr>

<div>
<h3 id="sin">Sine</h3>
<p>Pop A. Push sin(A) onto the stack.</p>
</div><hr>

<div>
<h3 id="cos">Cosine</h3>
<p>Pop A. Push cos(A) onto the stack.</p>
</div><hr>

<div>
<h3 id="asin">Arcsine</h3>
<p>Pop A. Push asin(A) onto the stack.</p>
</div><hr>

<div>
<h3 id="acos">Arccosine</h3>
<p>Pop A. Push acos(A) onto the stack.</p>
</div><hr>

<div>
<h3 id="exp">Exponentiation</h3>
<p>Pop A. Push e^A onto the stack where ^ represents exponent and e is the base of the natural logarithm.</p>
</div><hr>

<div>
<h3 id="ln">Natural logarithm</h3>
<p>Pop A. Push ln(A) onto the stack.</p>
</div><hr>

<div>
<h3 id="pow">Power</h3>
<p>Pop B. Pop A. Push A^B onto the stack where ^ represents exponent.</p>
</div><hr>

<div>
<h3 id="sqrt">Square root</h3>
<p>Pop A. Push the positive square root of A onto the stack.</p>
</div><hr>

<div>
<h3 id="cis">Cosine plus <i>i</i> times sine</h3>
<p>Pop A. Push cos(A) + i*sin(A) onto the stack where i is the imaginary unit.</p>
</div><hr>
<p>Copyright Bob Forder 2022. Released under Creative Commons CC0.</p>

</body>
</html>

# FDF

Wireframe elevation map (Fil De Fer)
____

Covered concepts:
- Using a graphics library
- Handling windows and images
- Handling the user's keyboard and mouse inputs
- Line rasterization
- Creating a basic GUI
- Using matrices for rotations and other transormations!
- Creating an isometric porjection
- Working with RGB
- Banishing segfaults and memory leaks to the nether

The program takes as parameter a file like this:

0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 <br/>
0 0 3 3 0 0 3 3 0 0 0 3 3 3 3 3 0 0 0 <br/>
0 0 3 3 0 0 3 3 0 0 0 0 0 0 0 3 3 0 0 <br/>
0 0 3 3 0 0 3 3 0 0 0 0 0 0 0 3 3 0 0 <br/>
0 0 3 3 3 3 3 3 0 0 0 0 3 3 3 3 0 0 0 <br/>
0 0 0 3 3 3 3 3 0 0 0 3 3 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 3 3 0 0 0 3 3 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 3 3 0 0 0 3 3 3 3 3 3 0 0 <br/>
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 <br/>
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 <br/>

Each number represents the height coordinate of a point at the 2D position in the table. Our task was to translate this into a visual height map.
____

## Compile

	make
____

## Run

	./fdf <map> colormin-colormax (base 10 or 16)
____

## Controls

Translation:	<kbd>&nbsp;▲&nbsp;</kbd><kbd>&nbsp;▼&nbsp;</kbd><kbd>&nbsp;◄&nbsp;</kbd><kbd>&nbsp;►&nbsp;</kbd><br/>
Rotation:		<kbd>&nbsp;1&nbsp;</kbd><kbd>&nbsp;4&nbsp;</kbd>/<kbd>&nbsp;2&nbsp;</kbd><kbd>&nbsp;5&nbsp;</kbd>/<kbd>&nbsp;3&nbsp;</kbd><kbd>&nbsp;6&nbsp;</kbd><br/>
Zoom:			<kbd>&nbsp;+&nbsp;</kbd><kbd>&nbsp;-&nbsp;</kbd><br/>
____

## Screenshots

42.fdf<br/>
![Rendu 1](https://github.com/squiquem/FDF/blob/master/screenshots/42-fdf.PNG)

IGN<br/>
![Rendu 2](https://github.com/squiquem/FDF/blob/master/screenshots/IGN-fdf.PNG)

Mars
![Rendu 3](https://github.com/squiquem/FDF/blob/master/screenshots/mars-fdf.PNG)
____

If you have any questions or suggestions, feel free to send me an email at squiquem@student.42.fr

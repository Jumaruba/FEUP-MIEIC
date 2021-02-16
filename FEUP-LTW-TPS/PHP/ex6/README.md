# CSS exercises

In this document I'll show what I've learned from each point of exercises.  

# Table of contents 

1.[Exercise 1](#11)  
   1. [Childs](#1childs)
   2. [Linear Gradient](#2linear-gradient) 
   3. [Shadows](#3shadows) 
   4. [Content](#4content)
   5. [First Letter](#5first-letter)

## 1.1

The exercise 1.1 we had fixed page, which means with no interation.  

![algo](/CSS/GIF.gif)

### 1.Childs

Possible to choose the child of an element based on the position in the father node: 

```css
header:first-child h1{
  margin-bottom: 0;
}
```

```css
header:nth-child(1) h1{
  margin-bottom: 0;
}

```

Both means the first header child of the body.  
To get the last one it would be: 

```css  
header:last-child h1{
  margin-bottom: 0;
}
```
### 2.Linear gradient 

Allows us to have an a background with multiple colors. The syntax is: 

```css
background: linear-gradient(<angle>, color1 color1-stop-at, color2 color2-start-at);
```

It can have as many color as we wish:

```css
background: linear-gradient(110deg, #fdcd3b 60%, #ffed4b 60%);
```
__Useful links for this__:  
[blog.prototypr.io](https://blog.prototypr.io/css-only-multi-color-backgrounds-4d96a5569a20)  
[Css Tricks - linear gradient](https://css-tricks.com/snippets/css/css-linear-gradient/)  
[Css Tricks - gradients](https://css-tricks.com/css3-gradients/)  

### 3.Shadows 

With a very simple syntax, we can give a shadow to a text: 

1. value = The X-coordinate  
2. value = The Y-coordinate  
3. value = The blur radius  
4. value = The color of the shadow  

```css
#news header h1 a{
    color: white;
    font-size: 3.7em; 
    font-size: large;
    text-shadow: 0 0.2em 4px black
}
```


__Useful links__:  
[Css Tricks](https://css-tricks.com/almanac/properties/t/text-shadow/) 

### 4.Content 

The content allow us to write in the html file before or after the element: 

```css
.author:before{
  content: 'By';
  margin-right: 4px;  
}
```
or

.author:after{
  content: 'By';
  margin-right: 4px;  
}

The content is the text to be addded 


### 5.First letter

We can set a special design for the first letter of a text. 

```css
#news article p:first-of-type:first-letter{
  font-size: x-large; 
}
```

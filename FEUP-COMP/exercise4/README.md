# Exception classes 

There are two possible types of errors: 

```
TokeMgrError - whenever there is an error with the tokens. 
ParseException - whenever there is an error with the parser.
```

Observe that the token manager is never expected to throw an exception - you must be careful in defining your tokens.  

The javacc grammar specification includes a syntax to specify additional exceptions that may be thrown by non terminal methods using `throws ...`: 

```java
void VariableDeclaration() thrwos IOException: 
{...}
{
    ...
}
```

## Error reporting

To report an error we must modify the file `ParseException.java`. Usually we should modify the `getMessage()` methods to do our report customization. 

## Error recovery 

There're two types of error recovery: `shallow recovery` and `deep recovery`.

The `shallow` recovers if none of the current choices have succeeded in being selected, while `deep` is when a choice is selected, but then an error happens when parsing this choice. 

### Shallow error recovery

````java
void Stm():
{}
{
    IfStm()
 | 
	WhileStm() 
}
````

Let's suppose that `IfStm` starts with the reserved word `if` and `WhileStm` starts with the reserved word `while`.  Supposing that we want to recover by skipping all the way to the next semicolon when neither `IfStm` nor `WhileStm` can be matched by next input token, we can do this: 

```java
void Stm() :
{}
{
  IfStm()
|
  WhileStm()
|
  error_skipto(SEMICOLON)
}

```

`error_skipto` must be defined: 

```java
JAVACODE
void error_skipto(int kind) {
  ParseException e = generateParseException();  // generate the exception object
  System.out.println(e.toString());  // print the error message
  Token t;
  // consume tokens all the way up to a token of "kind" - use a do-while loop
  // rather than a while because the current token is the one immediately before
  // the erroneous token (in our case the token immediately before what should
  // have been "if"/"while".
  do {
    t = getNextToken();
  }
  while (t.kind != kind);
}

```

### Deep error recovery 

Using the same example of `shallow error`: 

```java
void Stm() :
{}
{
  IfStm()
|
  WhileStm()
}

```

We want to recover the same way: when there is an error, skip to another position. But more than that, we want to recover when there is an error deeper into the parse. 

__For example__, suppose the next token was `while` - therefore the choice `WhileStm` was taken. But suppose that during the parse of `WhileStm` some error is encountered - say we have `while (foo { stm; }` i.e. the closing parentheses has been missed. Shallow recovery will not work for this situation, we need deep recovery to achieve this. For  this, we offer a new syntactic entity in JavaCC - the `try-catch-finally` block. 

Refactoring the shallow code, we have: 

```java
void Stm() :
{}
{
  try {
    (
      IfStm()
    |
      WhileStm()
    )
  }
  catch (ParseException e) {
    error_skipto(SEMICOLON);
  }
}

```

__or__

```java
void Stm() :
{}
{
  try {
    (
      IfStm()
    |
      WhileStm()
    )
  }
  catch (ParseException e) {
    System.out.println(e.toString());
    Token t;
    do {
      t = getNextToken();
    } while (t.kind != SEMICOLON);
  }
}

```

It is best to avoid placing too much Java code in the `catch` and `finally` blocks since it overwhelms the grammar reader - it is best to define methods that you can then from the `catch` blocks.



Source: https://javacc.github.io/javacc/tutorials/error-handling.html 

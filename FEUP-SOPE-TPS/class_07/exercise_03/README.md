 # O que evitar e porque dá certo 
 
 
 ## Não inicialize o verify antes dos fills 
 
 Considere o seguinte verify. 
 
 ```c 
 
void *verify(void *arg)
{
    int k;
    for (k = 0; k < npos; k++){
        while(1){
            pthread_mutex_lock(&mut); 
            if (k <= pos) break; 
            pthread_mutex_unlock(&mut); 
        } 
        if (buf[k] != k)
            // detecta valores errados
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);
        pthread_mutex_unlock(&mut); 
    }

    return NULL;
}


```

Observe que se inicializado antes, o verify irá ficar inifinitamente no while(1).  
Se houvessem outras threads o sistema iria se certificar de interromper este while temporariamente e chamar outro processo, mas caso o verify se inicialize antes de qualquer outro processo, o sistema nunca o irá interromper.  
Logo, a ordem de criação seria esta: 
```c
    for (k = 0; k < nthr; k++)
    {
        // criacao das threads 'fill'
        count[k] = 0;
        pthread_create(&tidf[k], NULL, fill, &count[k]);
    }
    total = 0;
    //inits the verify 
    pthread_create(&tidv, NULL, verify, NULL);
    pthread_join(tidv, NULL);
```

## Porque dá certo 

Voltando ao código do verify: 

 
 ```c 
 
void *verify(void *arg)
{
    int k;
    for (k = 0; k < npos; k++){
    //até que a condição seja satisfeita, o verify irá ficar dentro deste loop
        while(1){
            pthread_mutex_lock(&mut); 
            if (k <= pos) break;    //uma vez dado break, o código permanece com lock
            pthread_mutex_unlock(&mut); 
        } 
        if (buf[k] != k)
            // detecta valores errados
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);
        pthread_mutex_unlock(&mut); 
    }

    return NULL;
}


```

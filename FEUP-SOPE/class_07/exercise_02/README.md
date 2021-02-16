# Analise de solução que não funciona

```c
void *thrfunc(void *arg)
{
    int total = 0; 
    while (n > 0){
        //point of stop 
        write(STDERR, arg, 1); 
        pthread_mutex_lock(&mut); 
        n--; 
        total++; 
        pthread_mutex_unlock(&mut); 
    }
    printf("\n%d---\n", total);
    return NULL;
}
```

Repare que sendo que há duas threads enquanto uma thread percorre o while loop, a outra ficará no `point of stop`. Quando o valor de n em uma thread chegar a zero, a outra thread ainda fará um ciclo uma vez que esteja no `point of stop`.   
Apenas no final no ciclo irá checar o valor de n novamente.  
